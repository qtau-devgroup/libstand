/* WorldDecimator.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
// These codes are originally in WORLD http://www.slp.is.ritsumei.ac.jp/~morise/world/
#include "WorldDecimator.h"

void WorldDecimator::FilterForDecimate(double *x, int x_length, int r, double *y) {
  double a[3], b[2];  // filter Coefficients
  switch (r) {
    case 11:  // fs : 44100 (default)
      a[0] = 2.450743295230728;
      a[1] = -2.06794904601978;
      a[2] = 0.59574774438332101;
      b[0] = 0.0026822508007163792;
      b[1] = 0.0080467524021491377;
      break;
    case 12:  // fs : 48000
      a[0] = 2.4981398605924205;
      a[1] = -2.1368928194784025;
      a[2] = 0.62187513816221485;
      b[0] = 0.0021097275904709001;
      b[1] = 0.0063291827714127002;
      break;
    case 10:
      a[0] = 2.3936475118069387;
      a[1] = -1.9873904075111861;
      a[2] = 0.5658879979027055;
      b[0] = 0.0034818622251927556;
      b[1] = 0.010445586675578267;
      break;
    case 9:
      a[0] = 2.3236003491759578;
      a[1] = -1.8921545617463598;
      a[2] = 0.53148928133729068;
      b[0] = 0.0046331164041389372;
      b[1] = 0.013899349212416812;
      break;
    case 8:  // fs : 32000
      a[0] = 2.2357462340187593;
      a[1] = -1.7780899984041358;
      a[2] = 0.49152555365968692;
      b[0] = 0.0063522763407111993;
      b[1] = 0.019056829022133598;
      break;
    case 7:
      a[0] = 2.1225239019534703;
      a[1] = -1.6395144861046302;
      a[2] = 0.44469707800587366;
      b[0] = 0.0090366882681608418;
      b[1] = 0.027110064804482525;
      break;
    case 6:  // fs : 24000 and 22050
      a[0] = 1.9715352749512141;
      a[1] = -1.4686795689225347;
      a[2] = 0.3893908434965701;
      b[0] = 0.013469181309343825;
      b[1] = 0.040407543928031475;
      break;
    case 5:
      a[0] = 1.7610939654280557;
      a[1] = -1.2554914843859768;
      a[2] = 0.3237186507788215;
      b[0] = 0.021334858522387423;
      b[1] = 0.06400457556716227;
      break;
    case 4:  // fs : 16000
      a[0] = 1.4499664446880227;
      a[1] = -0.98943497080950582;
      a[2] = 0.24578252340690215;
      b[0] = 0.036710750339322612;
      b[1] = 0.11013225101796784;
      break;
    case 3:
      a[0] = 0.95039378983237421;
      a[1] = -0.67429146741526791;
      a[2] = 0.15412211621346475;
      b[0] = 0.071221945171178636;
      b[1] = 0.21366583551353591;
      break;
    case 2:  // fs : 8000
      a[0] = 0.041156734567757189;
      a[1] = -0.42599112459189636;
      a[2] = 0.041037215479961225;
      b[0] = 0.16797464681802227;
      b[1] = 0.50392394045406674;
      break;
    default:
      a[0] = 0.0;
      a[1] = 0.0;
      a[2] = 0.0;
      b[0] = 0.0;
      b[1] = 0.0;
  }

  // Filtering on time domain.
  double w[3] = {0.0, 0.0, 0.0};
  double wt;
  for (int i = 0; i < x_length; ++i) {
    wt = x[i] + a[0] * w[0] + a[1] * w[1] + a[2] * w[2];
    y[i] = b[0] * wt + b[1] * w[0] + b[1] * w[1] + b[0] * w[2];
    w[2] = w[1];
    w[1] = w[0];
    w[0] = wt;
  }
}

void WorldDecimator::decimate(double *x, int x_length, int r, double *y, int y_length) {
  const int kNFact = 9;
  double *tmp1 = new double[x_length + kNFact * 2];
  double *tmp2 = new double[x_length + kNFact * 2];

  for (int i = 0; i < kNFact; ++i) tmp1[i] = 2 * x[0] - x[kNFact - i];
  for (int i = kNFact; i < kNFact + x_length; ++i) tmp1[i] = x[i - kNFact];
  for (int i = kNFact + x_length; i < 2 * kNFact + x_length; ++i)
    tmp1[i] = 2 * x[x_length - 1] - x[x_length - 2 - (i - (kNFact + x_length))];

  FilterForDecimate(tmp1, 2 * kNFact + x_length, r, tmp2);
  for (int i = 0; i < 2 * kNFact + x_length; ++i)
    tmp1[i] = tmp2[2 * kNFact + x_length - i - 1];
  FilterForDecimate(tmp1, 2 * kNFact + x_length, r, tmp2);
  for (int i = 0; i < 2 * kNFact + x_length; ++i)
    tmp1[i] = tmp2[2 * kNFact + x_length - i - 1];

  int nout = x_length / r + 1;
  int nbeg = r - r * nout + x_length;

  int count = 0;
  for (int i = nbeg; i < x_length + kNFact && count < y_length; i += r)
    y[count++] = tmp1[i + kNFact - 1];

  delete[] tmp1;
  delete[] tmp2;
}

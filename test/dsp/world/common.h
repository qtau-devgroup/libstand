//-----------------------------------------------------------------------------
// Copyright 2012 Masanori Morise. All Rights Reserved.
// Author: morise [at] fc.ritsumei.ac.jp (Masanori Morise)
#ifndef WORLD_COMMON_H_
#define WORLD_COMMON_H_

#include "./fft.h"

//-----------------------------------------------------------------------------
// Structs on FFT
//-----------------------------------------------------------------------------
// Forward FFT in the real sequence
typedef struct {
  int fft_size;
  double *waveform;
  fft_complex *spectrum;
  fft_plan forward_fft;
} ForwardRealFFT;

// Inverse FFT in the real sequence
typedef struct {
  int fft_size;
  double *waveform;
  fft_complex *spectrum;
  fft_plan inverse_fft;
} InverseRealFFT;

// Minimum phase analysis from logarithmic power spectrum
typedef struct {
  int fft_size;
  double *log_spectrum;
  fft_complex *minimum_phase_spectrum;
  fft_complex *cepstrum;
  fft_plan inverse_fft;
  fft_plan forward_fft;
} MinimumPhaseAnalysis;

//-----------------------------------------------------------------------------
// GetSuitableFFTSize() calculates the suitable FFT size.
// The size is defined as the minimum length whose length is longer than
// the input sample.
// Input:
//   sample     : Length of the input signal
// Output:
//   Suitable FFT size
//-----------------------------------------------------------------------------
int GetSuitableFFTSize(int sample);

//-----------------------------------------------------------------------------
// These four functions are simple max() and min() function
// for "int" and "double" type.
//-----------------------------------------------------------------------------
inline int MyMax(int x, int y) {
  return x > y ? x : y;
}
inline double MyMax(double x, double y) {
  return x > y ? x : y;
}
inline int MyMin(int x, int y) {
  return x < y ? x : y;
}
inline double MyMin(double x, double y) {
  return x < y ? x : y;
}

//-----------------------------------------------------------------------------
// These functions are used to speed up the processing.
// Forward FFT
void InitializeForwardRealFFT(int fft_size, ForwardRealFFT *forward_real_fft);
void DestroyForwardRealFFT(ForwardRealFFT *forward_real_fft);

// Inverse FFT
void InitializeInverseRealFFT(int fft_size, InverseRealFFT *inverse_real_fft);
void DestroyInverseRealFFT(InverseRealFFT *inverse_real_fft);

// Minimum phase analysis (This analysis uses FFT)
void InitializeMinimumPhaseAnalysis(int fft_size,
  MinimumPhaseAnalysis *minimum_phase);
void GetMinimumPhaseSpectrum(MinimumPhaseAnalysis *minimum_phase);
void DestroyMinimumPhaseAnalysis(MinimumPhaseAnalysis *minimum_phase);

#endif  // WORLD_COMMON_H_

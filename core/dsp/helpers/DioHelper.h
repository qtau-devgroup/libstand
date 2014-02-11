/* DioHelper.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef DIOHELPER_H
#define DIOHELPER_H

#include <float.h>
#include <QList>

static double **newMatrix(int column, int row)
{
    double **result = new double*[row];
    result[0] = new double[column * row];
    for(int i = 1; i < row; i++)
    {
        result[i] = result[0] + i * column;
    }
    return result;
}

static void deleteMatrix(double **matrix)
{
    delete[] matrix[0];
    delete[] matrix;
}

/*
 * Functions below are from WORLD library.
 * Original source codes are here; http://www.slp.is.ritsumei.ac.jp/~morise/world/
 */
static void histc(double *x, int x_length, double msFramePeriod, int frameLength, int *index)
{
    int count = 1;

    int i = 0;
    for (; i < frameLength; i++)
    {
        double edge = i * msFramePeriod / 1000.0;
        index[i] = 1;
        if (edge >= x[0])
        {
            break;
        }
    }
    for (; i < frameLength; i++)
    {
        double edge = i * msFramePeriod / 1000.0;
        if (edge < x[count])
        {
          index[i] = count;
        }
        else
        {
          index[i--] = count++;
        }
        if (count == x_length)
        {
            break;
        }
    }
    count--;
    for (i++; i < frameLength; i++)
    {
        index[i] = count;
    }
}

static void interpolate(double *dst, double *location, double *interval, int locationLength, int dstLength, double msFramePeriod)
{
    double *h = new double[locationLength - 1];
    double *p = new double[dstLength];
    double *s = new double[dstLength];
    int *k = new int[dstLength];

    for (int i = 0; i < locationLength - 1; ++i)
    {
        h[i] = location[i + 1] - location[i];
    }
    for (int i = 0; i < dstLength; ++i) {
        p[i] = i;
        k[i] = 0;
    }

    histc(location, locationLength, msFramePeriod, dstLength, k);

    for (int i = 0; i < dstLength; ++i)
    {
        double xi = msFramePeriod * i / 1000.0;
        s[i] = (xi - location[k[i] - 1]) / h[k[i] - 1];
    }

    for (int i = 0; i < dstLength; ++i)
    {
        dst[i] = interval[k[i] - 1] + s[i] * (interval[k[i]] - interval[k[i] - 1]);
    }

    delete[] k;
    delete[] s;
    delete[] p;
    delete[] h;
}

static void getEachFrequency(double *frequency, int f0Length, double msFramePeriod, double *signal, int length, double fs)
{
    int *edges = new int[length];
    int count = 0;
    for (int i = 0; i < length - 1; i++)
    {
      if (0.0 < signal[i] && signal[i + 1] <= 0.0)
      {
        edges[count++] = i + 1;
      }
    }

    if (count < 2)
    {
        delete[] edges;
        for(int i = 0; i < f0Length; i++)
        {
            frequency[i] = 0.0;
        }
        return;
    }

    double *fineEdges = new double[count];
    double *intervals = new double[count - 1];
    double *locations = new double[count - 1];
    for (int i = 0; i < count; i++)
    {
        fineEdges[i] = edges[i] - signal[edges[i] - 1] / (signal[edges[i]] - signal[edges[i] - 1]);
    }

    for (int i = 0; i < count - 1; i++)
    {
        intervals[i] = fs / (fineEdges[i + 1] - fineEdges[i]);
        locations[i] = (fineEdges[i] + fineEdges[i + 1]) / 2.0 / fs;
    }

    interpolate(frequency, locations, intervals, count, f0Length, msFramePeriod);

    delete[] intervals;
    delete[] locations;
    delete[] fineEdges;
    delete[] edges;
}

static void getF0s(double **f0s, int f0Length, double msFramePeriod, double *signal, int length, double fs)
{
    getEachFrequency(f0s[0], f0Length, msFramePeriod, signal, length, fs);
    for(int i = 0; i < length; i++)
    {
        signal[i] = -signal[i];
    }
    getEachFrequency(f0s[1], f0Length, msFramePeriod, signal, length, fs);
    for(int i = 0; i < length - 1; i++)
    {
        signal[i] = signal[i] - signal[i + 1];
    }
    getEachFrequency(f0s[2], f0Length, msFramePeriod, signal, length, fs);
    for(int i = 0; i < length; i++)
    {
        signal[i] = -signal[i];
    }
    getEachFrequency(f0s[3], f0Length, msFramePeriod, signal, length, fs);
}

static void getCandidates(
        double *candidate,
        double *stability,
        int f0Length,
        double msFramePeriod,
        double boundaryF0,
        double ceilF0,
        double floorF0,
        double *signal,
        int length,
        double fs)
{
    double **f0s = newMatrix(f0Length, 4);

    getF0s(f0s, f0Length, msFramePeriod, signal, length, fs);

    for (int i = 0; i < f0Length; i++)
    {
        candidate[i] = (f0s[0][i] + f0s[1][i] + f0s[2][i] + f0s[3][i]) / 4.0;
        if (candidate[i] > boundaryF0 || candidate[i] < boundaryF0 / 2.0 || candidate[i] > ceilF0 || candidate[i] < floorF0) {
            candidate[i] = 0.0;
            stability[i] = DBL_MAX;
        } else {
            // calculate deviation devided by candidate.
            stability[i]   = sqrt((
                (f0s[0][i] - candidate[i]) * (f0s[0][i] - candidate[i]) +
                (f0s[1][i] - candidate[i]) * (f0s[1][i] - candidate[i]) +
                (f0s[2][i] - candidate[i]) * (f0s[2][i] - candidate[i]) +
                (f0s[3][i] - candidate[i]) * (f0s[3][i] - candidate[i])) / 3.0
            ) / (candidate[i] + DBL_MIN);
        }
    }
    deleteMatrix(f0s);
}

//-----------------------------------------------------------------------------
// EliminateUnnaturalChange() is the 1st step of the postprocessing.
// This function eliminates the unnatural change of f0 based on allowed_range.
// This function is only used in GetFinalF0Contour().
//-----------------------------------------------------------------------------
static void EliminateUnnaturalChange(
        double *dst, int f0Length, int exclusionLength, double allowedRange, double *currentF0, double *working
        )
{
    // Initialization
    for (int i = 0; i < exclusionLength; i++)
    {
        dst[i] = 0.0;
    }
    for (int i = exclusionLength; i < f0Length - exclusionLength; i++)
    {
        dst[i] = currentF0[i];
    }
    for (int i = f0Length - exclusionLength; i < f0Length; i++)
    {
        dst[i] = 0.0;
    }

    // Processing to prevent the jumping of f0
    for (int i = 0; i < exclusionLength; i++)
    {
        working[i] = 0.0;
    }
    for (int i = exclusionLength; i < f0Length; i++)
    {
        working[i] = fabs((dst[i] - dst[i - 1]) / (DBL_MIN + dst[i])) < allowedRange ? dst[i] : 0.0;
    }

    for (int i = exclusionLength; i < f0Length; ++i)
    {
        for (int j = 1; j < exclusionLength; ++j)
        {
            if (working[i - j] == 0 || working[i + j] == 0)
            {
                dst[i] = 0.0;
                break;
            }
        }
    }
}

static void CountNumberOfVoicedSections(
        double *f0After, int f0Length, int *positiveIndex, int *negativeIndex, int *positiveCount, int *negativeCount
    )
{
    *positiveCount = *negativeCount = 0;
    for (int i = 1; i < f0Length; ++i)
    {
        if (f0After[i] == 0 && f0After[i - 1] != 0)
        {
            negativeIndex[(*negativeCount)++] = i - 1;
        }
        else
        {
            if (f0After[i - 1] == 0 && f0After[i] != 0)
            {
                positiveIndex[(*positiveCount)++] = i;
            }
        }
    }
}

//-----------------------------------------------------------------------------
// CorrectOneF0() corrects the f0[current_index] based on
// f0[current_index + sign].
// This function is only used in ForwardCorrection() and BackwardCorrection().
//-----------------------------------------------------------------------------
static bool CorrectOneF0(double **f0_map, int number_of_candidates,
    double allowed_range, int current_index, int sign, double *f0_after) {
  double reference_value1 = f0_after[current_index] * 2 -
    f0_after[current_index + sign];
  double reference_value2 = f0_after[current_index];
  double minimum_error = qMin(fabs(reference_value1 -
    f0_map[0][current_index + sign]),
    fabs(reference_value2 - f0_map[0][current_index + sign]));
  double error_value;
  for (int i = 1; i < number_of_candidates; ++i) {
    error_value =
      qMin(fabs(reference_value1 - f0_map[i][current_index + sign]),
          fabs(reference_value2 - f0_map[i][current_index + sign]));
    if (error_value < minimum_error) {
      minimum_error = error_value;
      f0_after[current_index + sign] = f0_map[i][current_index + sign];
    }
  }
  if (qMin(minimum_error / (reference_value1 + DBL_MIN),
      minimum_error / (reference_value2 + DBL_MIN)) >
      allowed_range) {
    f0_after[current_index + sign] = 0.0;
    return false;
  }
  return true;
}

//-----------------------------------------------------------------------------
// ForwardCorrection() is the 4th step of the postprocessing.
// This function corrects the f0 candidates from backward to forward.
// This function is only used in GetFinalF0Contour().
//-----------------------------------------------------------------------------
static void ForwardCorrection(double *f0_before, int f0_length, double **f0_map,
    int number_of_candidates, double allowed_range, int *positive_index,
    int *negative_index, int negative_count, double *f0_after) {
  for (int i = 0; i < f0_length; i++) f0_after[i] = f0_before[i];

  for (int i = 0; i < negative_count; ++i) {
    for (int j = negative_index[i]; j < f0_length - 1; ++j) {
      if (false == CorrectOneF0(f0_map, number_of_candidates, allowed_range,
        j, 1, f0_after)) break;
      if (i != negative_count && j == positive_index[i + 1] - 1) {
        negative_index[j] = j;
        break;
      }
    }
  }
}

//-----------------------------------------------------------------------------
// BackwardCorrection() is the 5th step of the postprocessing.
// This function corrects the f0 candidates from forward to backward.
// This function is only used in GetFinalF0Contour().
//-----------------------------------------------------------------------------
static void BackwardCorrection(double *f0_before, int f0_length, double **f0_map,
    int number_of_candidates, double allowed_range, int *positive_index,
    int *negative_index, int positive_count, double *f0_after) {
  for (int i = 0; i < f0_length; ++i) f0_after[i] = f0_before[i];

  for (int i = positive_count - 1; i >= 0; --i) {
    for (int j = positive_index[i] + 1; j > 1; --j) {
      if (false == CorrectOneF0(f0_map, number_of_candidates, allowed_range,
        j, -1, f0_after)) break;
      if (i != 0 && j == negative_index[i - 1] + 1) {
        positive_index[j] = j;
        break;
      }
    }
  }
}

//-----------------------------------------------------------------------------
// EliminateInvalidVoicedSection() is the final step of the postprocessing.
// This function eliminates the voiced section whose the
// duration is under 50 msec.
// This function is only used in GetFinalF0Contour().
//-----------------------------------------------------------------------------
static void EliminateInvalidVoicedSection(double *f0_before, int f0_length,
    int voice_range_minimum, double *f0_after) {
  for (int i = 0; i < f0_length; ++i) f0_after[i] = f0_before[i];

  int current_index;
  for (int i = 0; i < f0_length; ++i) {
    if (f0_before[i] == 0.0) continue;
    current_index = i;
    for (int j = current_index; j < f0_length; ++j)
      if (f0_before[j] == 0.0) {
        i = j;
        break;
      }
    if ((i - current_index) > voice_range_minimum) continue;
    for (int j = i; j >= current_index; --j) f0_after[j] = 0.0;
  }
}

static QList<float> getF0Contour(double **candidates, double **stabilities, int bandsCount, int f0Length, double msFramePeriod)
{
    double *arrayResult = new double[f0Length];
    for(int i = 0; i < f0Length; i++)
    {
        double tmp = stabilities[0][i];
        arrayResult[i] = candidates[0][i];
        for(int j = 1; j < bandsCount; j++)
        {
            if(tmp > stabilities[j][i])
            {
                tmp = stabilities[j][i];
                arrayResult[i] = candidates[j][i];
            }
        }
    }
    // memo:
    // First and lat 50 msec are not used as the voiced section.
    int exclusionLength = static_cast<int>(0.5 + 50.0 / msFramePeriod);
    // memo:
    // This is the tentative value.
    double allowedRange = 0.1 * msFramePeriod / 5.0;

    double *f0Tmp1 = new double[f0Length];
    double *f0Tmp2 = new double[f0Length];

    EliminateUnnaturalChange(f0Tmp1, f0Length, exclusionLength, allowedRange, arrayResult, f0Tmp2);

    int *positiveIndex = new int[f0Length];
    int *negativeIndex = new int[f0Length];
    int positiveCount, negativeCount;

    CountNumberOfVoicedSections(f0Tmp1, f0Length, positiveIndex, negativeIndex, &positiveCount, &negativeCount);
    ForwardCorrection(f0Tmp1, f0Length, candidates, bandsCount,
        allowedRange, positiveIndex, negativeIndex, negativeCount, f0Tmp2);
    BackwardCorrection(f0Tmp2, f0Length, candidates, bandsCount,
        allowedRange, positiveIndex, negativeIndex, positiveCount, f0Tmp1);
    EliminateInvalidVoicedSection(f0Tmp1, f0Length, exclusionLength, arrayResult);

    delete[] f0Tmp1;
    delete[] f0Tmp2;
    delete[] positiveIndex;
    delete[] negativeIndex;
    QList<float> result;
    result.reserve(f0Length);
    for(int i = 0; i < f0Length; i++)
    {
        result.append(arrayResult[i]);
    }
    delete[] arrayResult;

    return result;
}

#endif // DIOHELPER_H

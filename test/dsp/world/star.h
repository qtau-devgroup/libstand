//-----------------------------------------------------------------------------
// Copyright 2012 Masanori Morise. All Rights Reserved.
// Author: morise [at] fc.ritsumei.ac.jp (Masanori Morise)
//-----------------------------------------------------------------------------

#ifndef WORLD_STAR_H_
#define WORLD_STAR_H_

//-----------------------------------------------------------------------------
// Star() calculates the spectrogram that consists of spectral envelopes
// estimated by STAR.
// Input:
//   x            : Input signal
//   xLen         : Length of x
//   fs           : Sampling frequency
//   timeAxis     : Time axis
//   f0           : F0 contour
// Output:
//   spectrogram  : Spectrogram estimated by STAR.
//-----------------------------------------------------------------------------
void Star(double *x, int x_length, int fs, double *time_axis, double *f0,
  int f0_length, double **spectrogram);

//-----------------------------------------------------------------------------
// GetFFTSizeForStar() calculates the FFT size based on the sampling frequency
// and the lower limit of f0 (It is defined in world.h).
// Input:
//   fs      : Sampling frequency
// Output:
//   FFT size
//-----------------------------------------------------------------------------
int GetFFTSizeForStar(int fs);

#endif  // WORLD_STAR_H_

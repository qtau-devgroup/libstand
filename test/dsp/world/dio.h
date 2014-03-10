//-----------------------------------------------------------------------------
// Copyright 2012 Masanori Morise. All Rights Reserved.
// Author: morise [at] fc.ritsumei.ac.jp (Masanori Morise)
//
//-----------------------------------------------------------------------------
#ifndef WORLD_DIO_H_
#define WORLD_DIO_H_

//-----------------------------------------------------------------------------
// Struct for DIO
//-----------------------------------------------------------------------------
typedef struct {
  double f0_floor;
  double f0_ceil;
  double channels_in_octave;
  double frame_period;  // msec
  int speed;  // (1, 2, ..., 12)
} DioOption;

//-----------------------------------------------------------------------------
// DIO (version 0.1.0)
// You can only change the parameter "frame_period". If you want to change
// other parameters, you should use latest Dio().
// This version will be destroyed in the future.
// Input:
//   x              : Input signal
//   x_length       : Length of x
//   fs             : Sampling frequency
//   frame_period   :
// Output:
//   time_axis      : Temporal positions.
//   f0             : F0 contour.
//-----------------------------------------------------------------------------
void Dio(double *x, int x_length, int fs, double frame_period,
  double *time_axis, double *f0);

//-----------------------------------------------------------------------------
// DIO (vertion 0.1.1)
// Input:
//   x          : Input signal
//   x_length   : Length of x
//   fs         : Sampling frequency
//   option     : Struct to order the parameter for DIO
// Output:
//   time_axis  : Temporal positions.
//   f0         : F0 contour.
//-----------------------------------------------------------------------------
void Dio(double *x, int x_length, int fs, const DioOption option,
  double *time_axis, double *f0);

//-----------------------------------------------------------------------------
// InitializeDioOption allocates the memory to the struct and sets the
// default parameters.
// Output:
//   option   : Struct for the optional parameter.
//-----------------------------------------------------------------------------
void InitializeDioOption(DioOption *option);

//-----------------------------------------------------------------------------
// GetSamplesForDIO() calculates the number of samples required for Dio().
// Input:
//   fs             : Sampling frequency [Hz]
//   x_length       : Length of the input signal [Sample].
//   frame_period   : Frame shift [msec]
// Output:
//   The number of samples required to store the results of Dio()
//-----------------------------------------------------------------------------
int GetSamplesForDIO(int fs, int x_length, double frame_period);

#endif  // WORLD_DIO_H_

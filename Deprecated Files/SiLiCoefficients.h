#ifndef SILICOEFFICIENTS_H
#define SILICOEFFICIENTS_H

static const int nSiLiOrder = 2; //Order of calibration i.e. 1 = linear.
static const int nSiLiDets = 6; //Total number of signals from SiLi detectors
static const int nSiLiPlace = 48; //Start of SiLis in generalized array
static const double dSiLiCoefficients[nSiLiDets][nSiLiOrder+1] = {{4.33037,0.231524,4.69366e-07},
																  {9.41051,0.210806,4.37237e-07},
																  {7.65628,0.24027,7.44899e-07},
																  {5.73724,0.230731,1.93419e-07},
																  {8.55284,0.236235,6.99273e-07},
																  {3.21398,0.295073,9.24002e-07}};
#endif
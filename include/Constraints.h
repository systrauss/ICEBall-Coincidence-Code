#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#ifndef _CONSTRAINTS_CXX
#define EXTERNAL extern
#else
#define EXTERNAL
#endif

void defineConstraints(int nPeak, const double dInput[][3], double dOutput[][3], double dSigma);

#endif
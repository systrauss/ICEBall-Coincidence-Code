#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H

#ifndef _COEFFICIENTS_CXX
#define EXTERNAL extern
#else
#define EXTERNAL
#endif

void defineGeCoeff();

void defineGeCoeff(int nRunNum);

void defineSiLiCoeff();

void defineSiLiCoeff(int nRunNum);

#endif
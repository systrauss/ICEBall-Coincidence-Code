#ifndef SILICUTS_H
#define SILICUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nSiLiCutTotal = 6; //Total number of SiLi cuts to make
static const double dSiLiCuts[nSiLiCutTotal][3] = {{0,535.8,4}, //{Ge number(0-6),centroid, sigma}
												   {1,535.8,4},
												   {2,535.8,4},
												   {3,535.8,4},
												   {4,535.8,4},
												   {5,535.8,4}};

#endif
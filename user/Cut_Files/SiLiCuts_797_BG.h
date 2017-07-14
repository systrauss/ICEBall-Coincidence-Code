#ifndef SILICUTS_H
#define SILICUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nSiLiCutTotal = 6; //Total number of SiLi cuts to make
static const double dSiLiCuts[nSiLiCutTotal][3] = {{0,760,4}, //{Ge number(0-6),centroid, sigma}
												   {1,760,4},
												   {2,760,4},
												   {3,760,4},
												   {4,760,4},
												   {5,760,4}};

#endif
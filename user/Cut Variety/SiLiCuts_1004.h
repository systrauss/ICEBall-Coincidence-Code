#ifndef SILICUTS_H
#define SILICUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nSiLiCutTotal = 6; //Total number of SiLi cuts to make
static const double dSiLiCuts[nSiLiCutTotal][3] = {{0,954,4}, //{Ge number(0-6),centroid, sigma}
												   {1,954,4},
												   {2,954,4},
												   {3,954,4},
												   {4,954,4},
												   {5,954,4}};

#endif
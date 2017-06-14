#ifndef SILICUTS_H
#define SILICUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nSiLiCutTotal = 12; //Total number of SiLi cuts to make
static const double dSiLiCuts[nSiLiCutTotal][3] = {{0,507.3,4}, //{Ge number(0-6),centroid, sigma}
												   {1,507.3,4},
												   {2,507.3,4},
												   {3,507.3,4},
												   {4,507.3,4},
												   {5,507.3,4},
												   {0,549.2,4}, 
												   {1,549.2,4},
												   {2,549.2,4},
												   {3,549.2,4},
												   {4,549.2,4},
												   {5,549.2,4}};

#endif
#ifndef SILICUTS_H
#define SILICUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nSiLiCutTotal = 12; //Total number of SiLi cuts to make
static const double dSiLiCuts[nSiLiCutTotal][3] = {{0,970,4}, //{Ge number(0-6),centroid, sigma}
												   {1,970,4},
												   {2,970,4},
												   {3,970,4},
												   {4,970,4},
												   {5,970,4},
												   {0,1024,4}, 
												   {1,1024,4},
												   {2,1024,4},
												   {3,1024,4},
												   {4,1024,4},
												   {5,1024,4}};

#endif
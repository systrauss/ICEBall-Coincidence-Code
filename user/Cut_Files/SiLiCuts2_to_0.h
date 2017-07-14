#ifndef SILICUTS_H
#define SILICUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nSiLiCutTotal = 36; //Total number of SiLi cuts to make
static const double dSiLiCuts[nSiLiCutTotal][3] = {{0,80.6,4}, //{Ge number(0-6),centroid, sigma}
												   {1,80.6,4},
												   {2,80.6,4},
												   {3,80.6,4},
												   {4,80.6,4},
												   {5,80.6,4},
												   {0,126.8,4}, 
												   {1,126.8,4},
												   {2,126.8,4},
												   {3,126.8,4},
												   {4,126.8,4},
												   {5,126.8,4},
												   {0,185.9,4}, 
												   {1,185.9,4},
												   {2,185.9,4},
												   {3,185.9,4},
												   {4,185.9,4},
												   {5,185.9,4},
												   {0,193.9,4}, 
												   {1,193.9,4},
												   {2,193.9,4},
												   {3,193.9,4},
												   {4,193.9,4},
												   {5,193.9,4}};

#endif
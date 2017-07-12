#ifndef SILICUTS_H
#define SILICUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nSiLiCutTotal = 36; //Total number of SiLi cuts to make
static const double dSiLiCuts[nSiLiCutTotal][3] = {{0,630.5,4}, //{Ge number(0-6),centroid, sigma}
												   {1,630.5,4},
												   {2,630.5,4},
												   {3,630.5,4},
												   {4,630.5,4},
												   {5,630.5,4},
												   {0,672.3,4}, 
												   {1,672.3,4},
												   {2,672.3,4},
												   {3,672.3,4},
												   {4,672.3,4},
												   {5,672.3,4},
												   {0,642.2,4}, 
												   {1,642.2,4},
												   {2,642.2,4},
												   {3,642.2,4},
												   {4,642.2,4},
												   {5,642.2,4},
												   {0,684.0,4}, 
												   {1,684.0,4},
												   {2,684.0,4},
												   {3,684.0,4},
												   {4,684.0,4},
												   {5,684.0,4},
												   {0,626.4,4}, 
												   {1,626.4,4},
												   {2,626.4,4},
												   {3,626.4,4},
												   {4,626.4,4},
												   {5,626.4,4},
												   {0,668.2,4}, 
												   {1,668.2,4},
												   {2,668.2,4},
												   {3,668.2,4},
												   {4,668.2,4},
												   {5,668.2,4}};

#endif
#ifndef GECUTS_H
#define GECUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nGeCutTotal = 14; //Total number of Ge cuts to make
static const double dGeCuts[nGeCutTotal][3] = {{0,134.8,1.5}, //{Ge number(0-6),centroid, sigma}
											   {1,134.8,1.5},
											   {2,134.8,1.5},
											   {3,134.8,1.5},
											   {4,134.8,1.5},
											   {5,134.8,1.5},
											   {6,134.8,1.5},
											   {0,236.1,1.5},
											   {1,236.1,1.5},
											   {2,236.1,1.5},
											   {3,236.1,1.5},
											   {4,236.1,1.5},
											   {5,236.1,1.5},
											   {6,236.1,1.5}};

#endif
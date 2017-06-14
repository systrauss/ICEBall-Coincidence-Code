#ifndef GECUTS_H
#define GECUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nGeCutTotal = 28; //Total number of Ge cuts to make
static const double dGeCuts[nGeCutTotal][3] = {{0,236.1,1.2}, //{Ge number(0-6),centroid, sigma}
											   {1,236.1,1.2},
											   {2,236.1,1.2},
											   {3,236.1,1.2},
											   {4,236.1,1.2},
											   {5,236.1,1.2},
											   {6,236.1,1.2}, 
											   {0,216.1,1.2}, 
											   {1,216.1,1.2},
											   {2,216.1,1.2},
											   {3,216.1,1.2},
											   {4,216.1,1.2},
											   {5,216.1,1.2},
											   {6,216.1,1.2} };

#endif
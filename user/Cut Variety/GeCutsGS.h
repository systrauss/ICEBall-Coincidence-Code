#ifndef GECUTS_H
#define GECUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nGeCutTotal = 28; //Total number of Ge cuts to make
static const double dGeCuts[nGeCutTotal][3] = {{0,123,1.5}, //{Ge number(0-6),centroid, sigma}
											   {1,123,1.5},
											   {2,123,1.5},
											   {3,123,1.5},
											   {4,123,1.5},
											   {5,123,1.5},
											   {6,123,1.5},
											   {0,247.9,1.5},
											   {1,247.9,1.5},
											   {2,247.9,1.5},
											   {3,247.9,1.5},
											   {4,247.9,1.5},
											   {5,247.9,1.5},
											   {6,247.9,1.5},
											   {0,346.6,1.5},
											   {1,346.6,1.5},
											   {2,346.6,1.5},
											   {3,346.6,1.5},
											   {4,346.6,1.5},
											   {5,346.6,1.5},
											   {6,346.6,1.5},
											   {0,426.8,1.5}, 
											   {1,426.8,1.5},
											   {2,426.8,1.5},
											   {3,426.8,1.5},
											   {4,426.8,1.5},
											   {5,426.8,1.5},
											   {6,426.8,1.5}};

#endif
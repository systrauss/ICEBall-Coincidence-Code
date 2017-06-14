#ifndef GECUTS_H
#define GECUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nGeCutTotal = 14; //Total number of Ge cuts to make
static const double dGeCuts[nGeCutTotal][3] = {{0,1020,1.5}, //{Ge number(0-6),centroid, sigma}
											   {1,1020,1.5},
											   {2,1020,1.5},
											   {3,1020,1.5},
											   {4,1020,1.5},
											   {5,1020,1.5},
											   {6,1020,1.5},
											   {0,1074,1.5}, 
											   {1,1074,1.5},
											   {2,1074,1.5},
											   {3,1074,1.5},
											   {4,1074,1.5},
											   {5,1074,1.5},
											   {6,1074,1.5}};

#endif
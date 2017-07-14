#ifndef GECUTS_H
#define GECUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nGeCutTotal = 14; //Total number of Ge cuts to make
static const double dGeCuts[nGeCutTotal][3] = {{0,587.5,1.5}, //{Ge number(0-6),centroid, sigma}
											   {1,587.5,1.5},
											   {2,587.5,1.5},
											   {3,587.5,1.5},
											   {4,587.5,1.5},
											   {5,587.5,1.5},
											   {6,587.5,1.5},
											   {0,631.5,1.5},
											   {1,631.5,1.5},
											   {2,631.5,1.5},
											   {3,631.5,1.5},
											   {4,631.5,1.5},
											   {5,631.5,1.5},
											   {6,631.5,1.5}};

#endif
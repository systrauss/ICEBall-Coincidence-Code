#ifndef GECUTS_H
#define GECUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nGeCutTotal = 7; //Total number of Ge cuts to make
static const double dGeCuts[nGeCutTotal][3] = {{0,557,1.5}, //{Ge number(0-6),centroid, sigma}
											   {1,557,1.5},
											   {2,557,1.5},
											   {3,557,1.5},
											   {4,557,1.5},
											   {5,557,1.5},
											   {6,557,1.5}};

#endif
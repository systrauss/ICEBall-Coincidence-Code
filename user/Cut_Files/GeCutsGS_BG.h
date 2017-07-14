#ifndef GECUTS_H
#define GECUTS_H

//In this section, we create the set of cuts that will be used in analysis to make cuts based on the Germanium detectors

static const int nGeCutTotal = 42; //Total number of Ge cuts to make
static const double dGeCuts[nGeCutTotal][3] = {{0,130,1.5}, //{Ge number(0-6),centroid, sigma}
											   {1,130,1.5},
											   {2,130,1.5},
											   {3,130,1.5},
											   {4,130,1.5},
											   {5,130,1.5},
											   {6,130,1.5},
											   {0,254,1.5},
											   {1,254,1.5},
											   {2,254,1.5},
											   {3,254,1.5},
											   {4,254,1.5},
											   {5,254,1.5},
											   {6,254,1.5},
											   {0,400,1.5},
											   {1,400,1.5},
											   {2,400,1.5},
											   {3,400,1.5},
											   {4,400,1.5},
											   {5,400,1.5},
											   {6,400,1.5},
											   {0,460,1.5},
											   {1,460,1.5},
											   {2,460,1.5},
											   {3,460,1.5},
											   {4,460,1.5},
											   {5,460,1.5},
											   {6,460,1.5},
											   {0,850.6,1.5},
											   {1,850.6,1.5},
											   {2,850.6,1.5},
											   {3,850.6,1.5},
											   {4,850.6,1.5},
											   {5,850.6,1.5},
											   {6,850.6,1.5},
											   {0,853.6,1.5},
											   { 1,853.6,1.5 },
											   { 2,853.6,1.5 },
											   { 3,853.6,1.5 },
											   { 4,853.6,1.5 },
											   { 5,853.6,1.5 },
											   { 6,853.6,1.5 } };

#endif
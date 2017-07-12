#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#ifndef _CONSTRAINTS_CXX
#define EXTERNAL extern
#else
#define EXTERNAL
#endif

#include <vector>

int defineConstraints(char* cCuts, std::vector<std::vector<double> > &dBounds);

void defineBGO();

#endif
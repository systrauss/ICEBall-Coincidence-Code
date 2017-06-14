#include "Constraints.h"

void defineConstraints(const int nCuts, const double dInput[][3], double dOutput[][3], double dSigma)
{
	for(int i=0;i<nCuts;i++)
	{
		dOutput[i][0] = dInput[i][0]; //detector
		dOutput[i][1] = dInput[i][1]-dInput[i][2]*dSigma; //lower bound
		dOutput[i][2] = dInput[i][1]+dInput[i][2]*dSigma; //upper bound
	}
}
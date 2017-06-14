#include "Filelist.h"

//C++ libraries
#include <vector>
#include <string>

//ROOT libraries
#include <TChain.h>
#include <TString.h>
#include <TSystem.h>


//sFilepath,sRun and sFType are all in the header file Filelist.h

TChain* chain;

using namespace std;

void makeChain(int nRunNum)
{
	//Set up the chain
	chain = new TChain(sTree);
	chain->SetCacheSize(1E8);
	chain->AddBranchToCache("*");

	//Add all the chains to the file. Change the list by adding or subtracting the rootfiles using the same syntax.
	//For the May 2016 run, data taking begins at run 16
	//Skipping runs 23-26 -> high beam current affected SiLi resolution
	//NOTE: from run 63 onward, SiLi 6 was removed from the DAQ, as it became too noisy. This will have to be taken into account at some point
	//Some kind of crash. Runs 64 and 65 do not exist
	//Data runs finish at run 90.

	//Don't go through the loop for the runs marked above

	bool bRealRun = true;
	int i = 0;

	while(bRealRun)
	{
		//NOTE: needs to be adjusted at some point to include single or triple digits
		bRealRun = gSystem->IsFileInIncludePath(Form("%s%s%i-0%i%s", sFilepath, sRun, nRunNum, i, sFType));
		cout << Form("%s%s%i-0%i%s", sFilepath, sRun, nRunNum, i, sFType) << "\t" << bRealRun << endl;
		if (bRealRun)
		{
			chain->Add(Form("%s%s%i-0%i%s", sFilepath, sRun, nRunNum, i, sFType));
			i++;
		}
	}
}
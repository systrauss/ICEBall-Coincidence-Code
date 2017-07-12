#include "Filelist.h"

//C++ libraries
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

//ROOT libraries
#include <TChain.h>
#include <TString.h>
#include <TSystem.h>


//sFilepath,sRun and sFType are all in the header file Filelist.h
std::string sFilepath;
//Change sTree for the program to look at a different tree in the files.
std::string sTree;
//Formatting for the beginning and end of the rootfile name
std::string sRun;
std::string sFType;

TChain* chain;

using namespace std;

void readPaths()
{
   fstream fFile("user/Filelist.dat"); //Coefficient File
   if(!fFile.is_open())
   {
      cout << "Filelist did not open" << endl;
   }
   string buffer;
   std::getline(fFile,buffer); //Label
   std::getline(fFile,sFilepath); //Filepath
   sFilepath = sFilepath.substr(0,sFilepath.size()-1); //make a substring without a return

   std::getline(fFile,buffer); //Label
   std::getline(fFile,sTree); //Tree
   sTree = sTree.substr(0,sTree.size()-1); //make a substring without a return

   std::getline(fFile,buffer); //Label
   std::getline(fFile,sRun); //Run
   std::getline(fFile,sFType); //Type
   sRun = sRun.substr(0,sRun.size()-1); //make a substring without a return
   sFType = sFType.substr(0,sFType.find_first_of('\n')-1); //make a substring without a return

   fFile.close();
}

void makeChain(int nRunNum)
{
	//Set up the chain
	chain = new TChain(sTree.c_str());
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
		bRealRun = gSystem->IsFileInIncludePath(Form("%s%s%i-0%i%s", sFilepath.c_str(), sRun.c_str(), nRunNum, i, sFType.c_str()));
		cout << Form("%s%s%i-0%i%s", sFilepath.c_str(), sRun.c_str(), nRunNum, i, sFType.c_str()) << "\t" << bRealRun << endl;
		if (bRealRun)
		{
			//segment name formatting. -09 then -10
			if(i < 10)
			{
				chain->Add(Form("%s%s%i-0%i%s", sFilepath.c_str(), sRun.c_str(), nRunNum, i, sFType.c_str()));
			}
			else
			{
				chain->Add(Form("%s%s%i-%i%s", sFilepath.c_str(), sRun.c_str(), nRunNum, i, sFType.c_str()));
			}
			i++;
		}
	}
}
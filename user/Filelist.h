#ifndef FILELIST_H
#define FILELIST_H


//C++ libraries
#include <iostream>
#include <string>
#include <cstdio>

//ROOT libraries
#include <TROOT.h>
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TString.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TObject.h"
#include "TObjArray.h"

#ifndef _FILELIST_CXX
#define EXTERNAL extern
#else
#define EXTERNAL
#endif

void makeChain(int nRunNum);

//Output file name
static const char* sOut = "Cut_GS_Timing";

//Change sFilepath to change the location the program looks for the rootfiles
static const char* sFilepath = "/afs/crc.nd.edu/group/nsl/nuc/users/sstrauss/iceball_mar2016/rootfiles/";

//Change sTree for the program to look at a different tree in the files.
static const char* sTree = "t2";

//Formatting for the beginning and end of the rootfile name
static const char* sRun = "run00";
static const char* sFType = ".root";

#endif
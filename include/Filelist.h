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
void readPaths();

#endif
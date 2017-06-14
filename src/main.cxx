/*
Please check the README for more information about this code and it's purpose.
*/

//C++ libraries
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

//ROOT libraries
#include <TROOT.h>
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TString.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1F.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TObject.h"
#include "TObjArray.h"
#include "TMath.h"

//Object files
#include "analysis.h"
#include "Constraints.h"
#include "histograms.h"

//User input files
#include "Filelist.h"
#include "GeCoefficients.h"
#include "SiLiCoefficients.h"
#include "GeCuts.h"
#include "SiLiCuts.h"

using namespace std;

extern TChain* chain;
extern TH1F* ge_en_ge_cut[nGeDets][nGeCutTotal];
extern TH1F* sili_en_ge_cut[nSiLiDets][nGeCutTotal];
extern TH1F* ge_en_sili_cut[nGeDets][nSiLiCutTotal];
extern TH1F* sili_en_sili_cut[nSiLiDets][nSiLiCutTotal];

double dGeBounds[nGeCutTotal][3]; //bounds for cuts
double dSiLiBounds[nSiLiCutTotal][3]; //bounds for cuts

int main(int argc, char* argv[])
{
	int nRunNum;
    nRunNum = atoi(argv[1]);
	makeChain(nRunNum); //From Filelist.cxx
	defineConstraints(nGeCutTotal,dGeCuts,dGeBounds,2.0); //From constraints.cxx
	defineConstraints(nSiLiCutTotal,dSiLiCuts,dSiLiBounds,2.0);
	makeHistograms(nGeDets/nGeSegments,nGeCutTotal,nSiLiDets,nSiLiCutTotal); //from histograms.cxx
	analysis ana(chain); //analysis class. Main part of code.
	ana.Loop(Form("/scratch365/sstrauss/temp/%s_run_00%i.root",sOut,nRunNum)); //fOut is in Filelist.h
}
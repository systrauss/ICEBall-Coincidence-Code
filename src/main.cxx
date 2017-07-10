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
#include "Coefficients.h"

//User input files
#include "Filelist.h"
#include "GeCuts.h"
#include "SiLiCuts.h"

using namespace std;

extern TChain* chain;
extern std::vector<std::vector<TH1F*> > ge_en_ge_cut;
extern std::vector<std::vector<TH1F*> > sili_en_ge_cut;
extern std::vector<std::vector<TH1F*> > ge_en_sili_cut;
extern std::vector<std::vector<TH1F*> > sili_en_sili_cut;

extern int nGeOrder; //Order of calibration i.e. 1 = linear.
extern int nGeDets; //Total number of signals from Germanium detectors
extern int nGeSegments; //number of segments in a single Germanium crystal, for adding purposes
extern std::vector<std::vector<double> > dGeCoefficients; //Ge Coefficients
extern std::vector<std::vector<double> > dGeCoeffRes; // Ge Residual Coefficients

extern int nSiLiOrder; //Order of calibration i.e. 1 = linear.
extern int nSiLiDets; //Total number of signals from SiLi
extern int nSiLiPlace; //Start of SiLis in generalized array detectors
extern std::vector<std::vector<double> > dSiLiCoefficients; //Coefficients

double dGeBounds[nGeCutTotal][3]; //bounds for cuts
double dSiLiBounds[nSiLiCutTotal][3]; //bounds for cuts

int main(int argc, char* argv[])
{
	int nRunNum;
    nRunNum = atoi(argv[1]); //Run to do the cuts on
	char* sOut = argv[2]; //file title to write to
	char* sCut = argv[3]; //Cut file name indicator
	makeChain(nRunNum); //From Filelist.cxx
	defineGeCoeff(nRunNum);
	defineSiLiCoeff(nRunNum);
	defineConstraints(nGeCutTotal,dGeCuts,dGeBounds,2.0); //From constraints.cxx
	defineConstraints(nSiLiCutTotal,dSiLiCuts,dSiLiBounds,2.0);
	makeHistograms(nGeDets/nGeSegments,nGeCutTotal,nSiLiDets,nSiLiCutTotal); //from histograms.cxx
	analysis ana(chain); //analysis class. Main part of code.
	ana.Loop(Form("/scratch365/sstrauss/temp/%s_run_00%i.root",sOut,nRunNum),nRunNum); //fOut is in Filelist.h
}
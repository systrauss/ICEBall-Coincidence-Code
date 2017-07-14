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
#include "Filelist.h"

using namespace std;

//File path info
extern std::string sFilepath;
extern std::string sTree;
extern std::string sRun;
extern std::string sFType;

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
extern std::vector<std::vector<double> > dGeRunCorr; //Run Correction Coefficients

extern int nSiLiOrder; //Order of calibration i.e. 1 = linear.
extern int nSiLiDets; //Total number of signals from SiLi
extern int nSiLiPlace; //Start of SiLis in generalized array detectors
extern std::vector<std::vector<double> > dSiLiCoefficients; //Coefficients
extern std::vector<std::vector<double> > dSiLiRunCorr; //Run Correction Coefficients

std::vector<std::vector<double> > dGeBounds; //bounds for cuts
std::vector<std::vector<double> > dSiLiBounds; //bounds for cuts
int nGeConstraints;
int nSiLiConstraints;
double dTimeLow;
double dTimeHigh;

int main(int argc, char* argv[]) //Order of arguments: run #, output filename, cut filename, time low, time high
{
	char buffer[50];
	int nRunNum;
    nRunNum = atoi(argv[1]); //Run to do the cuts on
	char* sOut = argv[2]; //file title to write to
	char* sCut = argv[3]; //Cut file name indicator
	dTimeLow = atof(argv[4]); //Time Low number
	dTimeHigh = atof(argv[5]); //Time high number
	readPaths(); //From Filelist.cxx
	makeChain(nRunNum); //From Filelist.cxx
	defineGeCoeff(); //From Coefficients.cxx
	defineGeCoeff(nRunNum); //From Coefficients.cxx, correction terms
	defineSiLiCoeff(); //From Coefficients.cxx
	defineSiLiCoeff(nRunNum);  //From Coefficients.cxx
	sprintf(buffer,"GeCut_%s.dat",sCut); //File name to input
	nGeConstraints = defineConstraints(buffer,dGeBounds); //From constraints.cxx
	sprintf(buffer,"SiLiCut_%s.dat",sCut); //File name to input
	nSiLiConstraints = defineConstraints(buffer,dSiLiBounds);
	defineBGO(); //From constraints.cxx
	makeHistograms(nGeDets/nGeSegments,nGeConstraints,nSiLiDets,nSiLiConstraints); //from histograms.cxx
	analysis ana(chain); //analysis class. Main part of code.
	ana.Loop(Form("/scratch365/sstrauss/temp/%s_run_00%i.root",sOut,nRunNum),nRunNum); //fOut is in Filelist.h
}
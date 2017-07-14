#define analysis_cxx
#include "analysis.h"

//C++ libraries
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

//ROOT libraries
#include <TROOT.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <TRandom3.h>
#include <TMath.h>

//object files
#include "histograms.h"
#include "Constraints.h"

//From Coefficients.cxx
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

//From Constraints.cxx
extern std::vector<std::vector<double> > dGeBounds; //bounds for cuts
extern std::vector<std::vector<double> > dSiLiBounds; //bounds for cuts
extern int nGeConstraints;
extern int nSiLiConstraints;

extern int nBGODets; //Total number of signals from BGO detectors
extern int nBGOPlace; //Start of BGOs in generalized array
extern std::vector<double> dBGOThreshold;

//From histograms.cxx
extern std::vector<std::vector<TH1F*> > ge_en_ge_cut;
extern std::vector<std::vector<TH1F*> > sili_en_ge_cut;
extern std::vector<std::vector<TH1F*> > ge_en_sili_cut;
extern std::vector<std::vector<TH1F*> > sili_en_sili_cut;

using namespace std;

void analysis::Loop(const char* fileName, int nRunNum)
{
   if (fChain == 0) return;

   //Don't keep writing to fOut, so switch to the "user" space instead
   gROOT->cd();

   TRandom3 *randgen = new TRandom3(1); //For uniformity over bin, to remove artifacting
   std::vector<double> dGeEn;
   std::vector<double> dSiLiEn;
   std::vector<double> dBGO;

   //Times
   std::vector<double> dT_GeEnSeg;
   std::vector<double> dT_GeEn;
   std::vector<double> dT_SiLiEn;

   //Ge vector
   for(int i=0; i<nGeDets/nGeSegments;i++)
   {
       dGeEn.push_back(0);
       dT_GeEn.push_back(0);
   }
   for(int i=0; i<nGeDets;i++)
   {
       dT_GeEnSeg.push_back(0);
   }
   for(int i=0; i<nSiLiDets;i++)
   {
       dSiLiEn.push_back(0);
       dT_SiLiEn.push_back(0);
   }
   for(int i=0; i<nBGODets;i++)
   {
       dBGO.push_back(0);
   }

   Long64_t nentries = fChain->GetEntriesFast();

   //main loop through the data
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      if (jentry % 1000000==0) cout << "." << flush;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //Germanium calibration
      for(int i=0 ; i < nGeDets ; i++)
      {
         if(i % nGeSegments == 0)
         {
            dGeEn[i/nGeSegments] = 0; //Reset the total clover energy
            dT_GeEnSeg[i] = 0; //Reset segment time
            dT_GeEn[i/nGeSegments] = 0; //Reset total time
         } 
         double eneC = 0, dADC = 0;
         dADC = ene[i] + 0.5*(1 - 2*randgen->Rndm());
         dT_GeEnSeg[i] = timefull[i];
         for(int j=0 ; j<nGeOrder+1 ; j++)
         {
            eneC = eneC + dGeCoefficients[i][j]*pow(dADC,j);
         }
         /*//Linear Correction
         if(eneC > dGeCorrection[i][2]) eneC = eneC - dGeCorrection[i][0]+eneC*dGeCorrection[i][1];*/
          //This is the residual sawtooth function.
         eneC = eneC+dGeCoeffRes[i][0]*dADC+dGeCoeffRes[i][1]*TMath::Erfc((dADC-dGeCoeffRes[i][2])/dGeCoeffRes[i][6])+dGeCoeffRes[i][3]*TMath::Erf((dADC-dGeCoeffRes[i][2])/dGeCoeffRes[i][6])*TMath::Erfc((dADC-dGeCoeffRes[i][4])/dGeCoeffRes[i][6])+dGeCoeffRes[i][5]*TMath::Erf((dADC-dGeCoeffRes[i][4])/dGeCoeffRes[i][6]);
         eneC = dGeRunCorr[i][0]+dGeRunCorr[i][1]*eneC; //Run correction factor
         if(i%nGeSegments!=0 && i!=14 && i!=15) 
         {
            dGeEn[i/nGeSegments] = dGeEn[i/nGeSegments]+eneC; //Add energies
            if(dT_GeEn[i/nGeSegments] == 0) dT_GeEn[i/nGeSegments] = dT_GeEnSeg[i]; //Timing
         }
      }
      //SiLi Calibration
      for(int i=0 ; i < nSiLiDets ; i++)
      {
         dSiLiEn[i]=0;
         dT_SiLiEn[i] = 0;
         double dADC = 0;
         dADC = ene[i+nSiLiPlace] + 0.5*(1 - 2*randgen->Rndm());
         dT_SiLiEn[i] = timefull[i+nSiLiPlace];
         for(int j=0 ; j<nSiLiOrder+1 ; j++)
         {
            dSiLiEn[i] = dSiLiEn[i] + dSiLiCoefficients[i][j]*pow(dADC,j);
         }
         dSiLiEn[i] = dSiLiRunCorr[i][0]+dSiLiRunCorr[i][1]*dSiLiEn[i]; //Run-by-run correction
      }
      for(int i=0 ; i < nBGODets ; i++)
      {
         dBGO[i] = ene[i+nBGOPlace];
      }

      //Run the constraints subroutine. At this time, it does use timing gates
      fillHistograms(nGeConstraints, dGeBounds, dGeEn, dGeEn, dSiLiEn, dBGO, dT_GeEn, dT_SiLiEn,true);
      fillHistograms(nSiLiConstraints, dSiLiBounds, dSiLiEn, dGeEn, dSiLiEn, dBGO, dT_GeEn, dT_SiLiEn, false);
      if (Cut(ientry) < 0) continue;
   }

   //File to write out to
   TFile* fOut = new TFile(fileName,"RECREATE");

   //write to file
   fOut->cd();
   writeHistToFile(fOut);
   fOut->Close();
}

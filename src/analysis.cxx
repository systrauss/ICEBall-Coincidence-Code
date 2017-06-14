#define analysis_cxx
#include "analysis.h"

//C++ libraries
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

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

//user input
#include "GeCoefficients.h"
#include "SiLiCoefficients.h"
#include "GeCuts.h"
#include "SiLiCuts.h"
#include "BGO.h"

extern double dGeBounds[nGeCutTotal][3]; //bounds for cuts
extern double dSiLiBounds[nSiLiCutTotal][3]; //bounds for cuts
extern TH1F* ge_en_ge_cut[nGeDets][nGeCutTotal];
extern TH1F* sili_en_ge_cut[nSiLiDets][nGeCutTotal];
extern TH1F* ge_en_sili_cut[nGeDets][nSiLiCutTotal];
extern TH1F* sili_en_sili_cut[nSiLiDets][nSiLiCutTotal];

using namespace std;

void analysis::Loop(const char* fileName)
{
//   In a ROOT session, you can do:
//      Root > .L analysis.C
//      Root > analysis t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   if (fChain == 0) return;

   //File to write out to
   TFile* fOut = new TFile(fileName,"RECREATE");

   //Don't keep writing to fOut, so switch to the "user" space instead
   gROOT->cd();

   TRandom3 *randgen = new TRandom3(1); //For uniformity over bin, to remove artifacting
   double dGeEn[nGeDets/nGeSegments] = {0};
   double dSiLiEn[nSiLiDets] = {0};
   double dBGO[nBGODets] = {0};

   //Times
   double dT_GeEnSeg[nGeDets] = {0};
   double dT_GeEn[nGeDets/nGeSegments] = {0};
   double dT_SiLiEn[nSiLiDets] = {0};


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
      }
      //BGOs
      for(int i=0 ; i < nBGODets ; i++)
      {
         dBGO[i] = ene[i+nBGOPlace];
      }

      //Run the constraints subroutine. At this time, it does not use timing gates
      fillHistograms(nGeCutTotal, dGeBounds, dGeEn, dGeEn, dSiLiEn, dBGO, dT_GeEn, dT_SiLiEn,true);
      fillHistograms(nSiLiCutTotal, dSiLiBounds, dSiLiEn, dGeEn, dSiLiEn, dBGO, dT_GeEn, dT_SiLiEn, false);
      // if (Cut(ientry) < 0) continue;
   }

   //write to file
   fOut->cd();
   writeHistToFile(fOut);
   fOut->Close();
}

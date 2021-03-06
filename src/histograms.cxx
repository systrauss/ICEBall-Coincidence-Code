//This file is for the creation of the arrays of histograms to be used with the cuts code. It also contains the fill histograms command.

#include <histograms.h>

//C++ libraries

//ROOT libraries
#include <TH1F.h>
#include <TString.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TObject.h>

//User inputs
#include <GeCuts.h>
#include <SiLiCuts.h>
#include <GeCoefficients.h>
#include <SiLiCoefficients.h>
#include <BGO.h>

TH1F* ge_en_ge_cut[nGeDets][nGeCutTotal];
TH1F* sili_en_ge_cut[nSiLiDets][nGeCutTotal];
TH1F* ge_en_sili_cut[nGeDets][nSiLiCutTotal];
TH1F* sili_en_sili_cut[nSiLiDets][nSiLiCutTotal];

void makeHistograms(int nGeDets, int nGeCuts, int nSiLiDets, int nSiLiCuts)
{
	//Loop through and construct them all.
	for(int i=0 ; i < nGeCuts ; i++)
	{
		for(int j=0 ; j < nGeDets ; j++)
		{
			ge_en_ge_cut[j][i] = new TH1F(Form("ge_en_ge_cut[%i][%i]",j,i),Form("Clover_%i",j),4000,0.5,4000.5);
		}
		for(int j=0 ; j < nSiLiDets ; j++)
		{
			sili_en_ge_cut[j][i] = new TH1F(Form("sili_en_ge_cut[%i][%i]",j,i),Form("SiLi_%i",j+1),4000,0.5,4000.5);
		}
	}
	for(int i=0 ; i < nSiLiCuts ; i++)
	{
		for(int j=0 ; j < nGeDets ; j++)
		{
			ge_en_sili_cut[j][i] = new TH1F(Form("ge_en_sili_cut[%i][%i]",j,i),Form("Clover_%i",j),4000,0.5,4000.5);
		}
		for(int j=0 ; j < nSiLiDets ; j++)
		{
			sili_en_sili_cut[j][i] = new TH1F(Form("sili_en_sili_cut[%i][%i]",j,i),Form("SiLi_%i",j+1),4000,0.5,4000.5);
		}
	}
}


void fillHistograms(int nConstraints, double dConstraints[][3], double dEnCut[], double dGeDetectors[], double dSiLiDetectors[], double dBGO[], double dGeT[], double dSiLiT[], bool GeorSiLi/*true  = ge gate, false = sili gate*/)
{
	for(int i=0; i<nConstraints ; i++)
	{
		if((dEnCut[(int)dConstraints[i][0]] > dConstraints[i][1] && //gate detector lower limit
			dEnCut[(int)dConstraints[i][0]] < dConstraints[i][2] && //gate detector upper limit
			GeorSiLi                                             && //is germanium
			dBGO[(int)dConstraints[i][0]] < dBGOThreshold[(int)dConstraints[i][0]]) //BGO Threshold met
			|| //OR (above is Ge constraint, below is SiLi)
		   (dEnCut[(int)dConstraints[i][0]] > dConstraints[i][1] && //gate detector lower limit
		   	dEnCut[(int)dConstraints[i][0]] < dConstraints[i][2] && //gate detector upper limit
		   	!GeorSiLi)) //is SiLi
		{
			//Fill Germanium histograms, includes BGO thresholds and timing
			for(int j = 0 ; j < nGeDets/nGeSegments ; j++)
			{
				if(GeorSiLi && dConstraints[i][0] != j && dBGO[j] < dBGOThreshold[j]) // if Ge gate AND gate detector is not this detector AND BGO is under threshold)
				{
					if( dGeDetectors[j] > 5 && (dGeT[(int)dConstraints[i][0]]-dGeT[j]) >= -0.3 && (dGeT[(int)dConstraints[i][0]]-dGeT[j]) <= 0.3) ge_en_ge_cut[j][i]->Fill(dGeDetectors[j]); //If detector energy > 5 keV AND timing between this detector and gate detector is +/- 0.3, fill this detector-gate combo
				}
				else if (!GeorSiLi && dBGO[j] < dBGOThreshold[j])
				{
					if( dGeDetectors[j] > 5 && (dSiLiT[(int)dConstraints[i][0]]-dGeT[j]) >= -0.3 && (dSiLiT[(int)dConstraints[i][0]]-dGeT[j]) <= 0.3) ge_en_sili_cut[j][i]->Fill(dGeDetectors[j]);
				}
			}
			//Fill SiLi histograms, includes timing
			for(int j = 0 ; j < nSiLiDets ; j++)
			{
				if(GeorSiLi)
				{
					if(dSiLiDetectors[j] > 10 && (dGeT[(int)dConstraints[i][0]]-dSiLiT[j]) >= -0.3 && (dGeT[(int)dConstraints[i][0]]-dSiLiT[j]) <= 0.3) sili_en_ge_cut[j][i]->Fill(dSiLiDetectors[j]);
				}
				else if (!GeorSiLi && dConstraints[i][0] != j)
				{
					if(dSiLiDetectors[j] > 10 && (dSiLiT[(int)dConstraints[i][0]]-dSiLiT[j]) >= -0.3 && (dSiLiT[(int)dConstraints[i][0]]-dSiLiT[j]) <= 0.3) sili_en_sili_cut[j][i]->Fill(dSiLiDetectors[j]);
				}
			}
		}
	}
}

void writeHistToFile(TFile* fOut)
{
	for(int i=0; i<nGeCutTotal ; i++)
	{
		fOut->cd();
		gDirectory->mkdir(Form("Ge Cut Detector %i, Peak %f",(int)dGeCuts[i][0],dGeCuts[i][1]));
		fOut->cd(Form("Ge Cut Detector %i, Peak %f",(int)dGeCuts[i][0],dGeCuts[i][1]));
		for(int j=0; j<nGeDets/nGeSegments ; j++)
		{
			ge_en_ge_cut[j][i]->Write(Form("Clover_%i",j),TObject::kOverwrite,1E8);
		}
		for(int j=0; j<nSiLiDets ; j++)
		{
			sili_en_ge_cut[j][i]->Write(Form("SiLi_%i",j+1),TObject::kOverwrite,1E8);
		}
	}
	for(int i=0; i<nSiLiCutTotal ; i++)
	{
		fOut->cd();
		gDirectory->mkdir(Form("SiLi Cut Detector %i, Peak %f",(int)dSiLiCuts[i][0]+1,dSiLiCuts[i][1]));
		fOut->cd(Form("SiLi Cut Detector %i, Peak %f",(int)dSiLiCuts[i][0]+1,dSiLiCuts[i][1]));
		for(int j=0; j<nGeDets/nGeSegments ; j++)
		{
			ge_en_sili_cut[j][i]->Write(Form("Clover_%i",j),TObject::kOverwrite,1E8);
		}
		for(int j=0; j<nSiLiDets ; j++)
		{
			sili_en_sili_cut[j][i]->Write(Form("SiLi_%i",j+1),TObject::kOverwrite,1E8);
		}
	}
	fOut->Write();

}
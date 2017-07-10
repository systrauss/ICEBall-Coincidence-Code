#ifndef HISTOGRAMS_H
#define HISTOGRAMS_H

#ifndef _HISTOGRAMS_CXX
#define EXTERNAL extern
#else
#define EXTERNAL
#endif

//ROOT libraries
#include <TH1F.h>
#include <TString.h>
#include <TFile.h>

//User inputs
#include <GeCuts.h>
#include <SiLiCuts.h>
#include <BGO.h>

void makeHistograms(int nGeDets, int nGeCuts, int nSiLiDets, int nSiLiCuts);
void fillHistograms(int nConstraints, double dConstraints[][3], double dEnCut[], double dGeDetectors[], double dSiLiDetectors[], double dBGO[], double dGeT[], double dSiLiT[], bool GeorSiLi);
void writeHistToFile(TFile* fOut);

#endif
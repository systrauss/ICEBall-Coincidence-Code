#ifndef HISTOGRAMS_H
#define HISTOGRAMS_H

#ifndef _HISTOGRAMS_CXX
#define EXTERNAL extern
#else
#define EXTERNAL
#endif

//C++ libraries
#include <vector>

//ROOT libraries
#include <TH1F.h>
#include <TString.h>
#include <TFile.h>

void makeHistograms(int nGeDets, int nGeCuts, int nSiLiDets, int nSiLiCuts);
void fillHistograms(int nConstraints, std::vector<std::vector<double> >dConstraints, std::vector<double> dEnCut, std::vector<double> dGeDetectors, std::vector<double> dSiLiDetectors, std::vector<double> dBGO, std::vector<double> dGeT, std::vector<double> dSiLiT, bool GeorSiLi);
void writeHistToFile(TFile* fOut);

#endif
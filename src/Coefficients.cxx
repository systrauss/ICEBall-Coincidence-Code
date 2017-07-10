#include "Constraints.h"

//C++ libraries
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>

//ROOT libraries
#include <TString.h>

using namespace std;

int nGeOrder; //Order of calibration i.e. 1 = linear.
int nGeDets; //Total number of signals from Germanium detectors
int nGeSegments; //number of segments in a single Germanium crystal, for adding purposes
std::vector<std::vector<double> > dGeCoefficients; //Coefficients
std::vector<std::vector<double> > dGeCoeffRes; //Residual Coefficients

int nSiLiOrder; //Order of calibration i.e. 1 = linear.
int nSiLiDets; //Total number of signals from SiLi
int nSiLiPlace; //Start of SiLis in generalized array detectors
std::vector<std::vector<double> > dSiLiCoefficients; //Coefficients


void defineGeCoeff(int nRunNum)
{
   //First thing: read in the coefficients for this run.
   fstream fCoeff(Form("user/GeCoefficients_r%i.dat",nRunNum)); //Coefficient File
   if(!fCoeff.is_open())
   {
      cout << "Ge file did not open" << endl;
      return;
   }
   string buffer;
   std::getline(fCoeff,buffer);
   nGeOrder = std::atoi(buffer.substr(0,buffer.find_first_of(' ',0)).c_str()); //So this clusterfuck is due to gcc being a pain. it basically converts a substring of the string into a char to convert into an int because apparently it won't just go string to int
   getline (fCoeff,buffer);
   nGeDets = std::atoi(buffer.substr(0,buffer.find_first_of(' ',0)).c_str());
   getline (fCoeff,buffer);
   nGeSegments = std::atoi(buffer.substr(0,buffer.find_first_of(' ',0)).c_str());
   getline (fCoeff,buffer); //Label Line
   std::vector<double> row; //Row for adding a level in.
   //Okay, here, we get into the nitty gritty
   for(int i=0; i<nGeDets;i++) //Loop through all the detectors
   {
      getline (fCoeff,buffer); //Line with coefficients on it.
      dGeCoefficients.push_back(row); //Put a new row in for the detector
      for(int j=0; j<= nGeOrder; j++) //Loop through the coefficients
      {
         dGeCoefficients[i].push_back(std::atof(buffer.substr(0,buffer.find_first_of(',',0)).c_str())); //read in jth coefficient
         buffer = buffer.substr(buffer.find_first_of(',',0)+1,buffer.find_first_of('\n',0)); //make a substring of the rest of the coefficients
      }
   }
   getline (fCoeff,buffer); //Line with label on it
   for(int i=0; i<nGeDets;i++) //Loop through all the detectors
   {
      getline (fCoeff,buffer); //Line with coefficients on it.
      dGeCoeffRes.push_back(row); //Put a new row in for the detector
      for(int j=0; j< 7; j++) //Loop through the residual coefficients. Currently hardcoded in.
      {
         dGeCoeffRes[i].push_back(std::atof(buffer.substr(0,buffer.find_first_of(',',0)).c_str())); //read in jth coefficient
         buffer = buffer.substr(buffer.find_first_of(',',0)+1,buffer.find_first_of('\n',0)); //make a substring of the rest of the coefficients
      }
   }
   fCoeff.close(); //Close the coefficients file
}

void defineSiLiCoeff(int nRunNum)
{
   //First thing: read in the coefficients for this run.
   fstream fCoeff(Form("user/SiLiCoefficients_r%i.dat",nRunNum)); //Coefficient File
   if(!fCoeff.is_open())
   {
      cout << "SiLi file did not open" << endl;
      return;
   }
   string buffer;
   std::getline(fCoeff,buffer);
   nSiLiOrder = std::atoi(buffer.substr(0,buffer.find_first_of(' ',0)).c_str()); //So this clusterfuck is due to gcc being a pain. it basically converts a substring of the string into a char to convert into an int because apparently it won't just go string to int
   getline (fCoeff,buffer);
   nSiLiDets = std::atoi(buffer.substr(0,buffer.find_first_of(' ',0)).c_str());
   getline (fCoeff,buffer);
   nSiLiPlace = std::atoi(buffer.substr(0,buffer.find_first_of(' ',0)).c_str());
   getline (fCoeff,buffer); //Label Line
   std::vector<double> row; //Row for adding a level in.
   //Okay, here, we get into the nitty gritty
   for(int i=0; i<nSiLiDets;i++) //Loop through all the detectors
   {
      getline (fCoeff,buffer); //Line with coefficients on it.
      dSiLiCoefficients.push_back(row); //Put a new row in for the detector
      for(int j=0; j<= nSiLiOrder; j++) //Loop through the coefficients
      {
         dSiLiCoefficients[i].push_back(std::atof(buffer.substr(0,buffer.find_first_of(',',0)).c_str())); //read in jth coefficient
         buffer = buffer.substr(buffer.find_first_of(',',0)+1,buffer.find_first_of('\n',0)); //make a substring of the rest of the coefficients
      }
   }
}
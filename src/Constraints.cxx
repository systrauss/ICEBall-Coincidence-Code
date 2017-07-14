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

int nBGODets; //Total number of signals from BGO detectors
int nBGOPlace; //Start of BGOs in generalized array
std::vector<double> dBGOThreshold;

int defineConstraints(char* cCuts, std::vector<std::vector<double> > &dBounds)
{
   //First thing: read in the cuts for this run.
   fstream fCuts(Form("user/Cut_Files/%s",cCuts)); //Coefficient File
   if(!fCuts.is_open())
   {
      cout << "Cuts file did not open" << endl;
   }
   string buffer;
   std::getline(fCuts,buffer);
   int nConstraints = std::atoi(buffer.substr(0,buffer.find_first_of(' ',0)).c_str()); //So this clusterfuck is due to gcc being a pain. it basically converts a substring of the string into a char to convert into an int because apparently it won't just go string to int
   getline (fCuts,buffer); //Label Line
   std::vector<double> row; //Row for adding a level in.
   //Okay, here, we get into the nitty gritty
   for(int i=0; i<nConstraints;i++) //Loop through all the constraints
   {
      getline (fCuts,buffer); //Line with cuts on it.
      dBounds.push_back(row); //Put a new row of constraints
      for(int j=0; j< 3; j++) //Loop through the parts of the constraints
      {
         dBounds[i].push_back(std::atof(buffer.substr(0,buffer.find_first_of(',',0)).c_str())); //read in jth coefficient
         buffer = buffer.substr(buffer.find_first_of(',',0)+1,buffer.find_first_of('\n',0)); //make a substring of the rest of the coefficients
      }
	  //Make low and high bounds
	  dBounds[i][1]=dBounds[i][1]-dBounds[i][2];
	  dBounds[i][2]=dBounds[i][1]+2*dBounds[i][2];
   }
   fCuts.close();
   return nConstraints;
}

void defineBGO()
{
    //First thing: read in the cuts for this run.
   fstream fBGO("user/BGO.dat"); //Coefficient File
   if(!fBGO.is_open())
   {
      cout << "BGO file did not open" << endl;
   }
   string buffer;
   std::getline(fBGO,buffer);
   nBGODets = std::atoi(buffer.substr(0,buffer.find_first_of(' ',0)).c_str()); //So this clusterfuck is due to gcc being a pain. it basically converts a substring of the string into a char to convert into an int because apparently it won't just go string to int
   std::getline(fBGO,buffer);
   nBGOPlace = std::atoi(buffer.substr(0,buffer.find_first_of(' ',0)).c_str()); 
   std::getline(fBGO,buffer); //Label Line
   //Okay, here, we get into the nitty gritty
   for(int i=0; i<nBGODets;i++) //Loop through all the constraints
   {
    std::getline(fBGO,buffer); //Line with cuts on it.
    dBGOThreshold.push_back(std::atof(buffer.c_str())); //read in ith detector threshold
   }
   fBGO.close();
}
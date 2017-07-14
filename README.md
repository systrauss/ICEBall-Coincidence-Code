# ICEBall-Coincidence-Code

This code is going to be changing a lot. Currently this is a log of upload changes. there will be a comprehensive readme and explanation when the code is complete

Almost everything in the user folder will get shifted to work without needing to recompile the script every time. 

Branches for these shifts will be named accordingly.

### 7/7/2017
Everything is broken right now. Major reorganization needs to happen, and almost all arrays need to be switched to vectors.

### 7/10/2017
Finished the coefficient section. It now reads in the coefficients from text files successfully. Still need to give it a "universal" option in the case of not needing a run-by-run calibration. This may need to be an input flag for Ge and SiLi. Had to make adjustments for the fillhistograms function (in terms of double array vs double vector)

Also need to add a similar function for the BGOs, even though those are pretty useless right now. 

After these two things, this should be ready to merge with the main branch before adding in timing flags and a similar system for cuts.

### 7/11/2017
Added the cuts section. A good note is that vectors need to be passed in as an address in the case that i need to get vector results back. Made the Filepaths etc. a *.dat file, for quick adjustment.

Still to do:
1. BGO.h to BGO.dat
2. Timing flags

### 7/12/2017
~~Totally lists the peaks wrong now (as lower bound). -_-~~ fixed

Also, maybe don't declare variables twice, Sabrina. Huh?

Still to do:
1. ~~Timing flags~~ Done, current bounds: regular is -0.3 to 0.3, background is 0.3 to 0.9

~~Also need to adjust Ge coefficients. Wanted a correction term in the files on top of the calibration. So, maybe a general calibration read in for the Ge, then the correction?~~Currently set up with 0,1 as coefficients (so y=x)
Actually, we need to get those coefficients...will use run 18 as a test case.

*Should add a redundancy check to make sure y=x is default if run file doesn't open/exist*

### 7/13/2017

Adding in the redundancy check now.

Also found an error in the use of the run correction. Now fixed.
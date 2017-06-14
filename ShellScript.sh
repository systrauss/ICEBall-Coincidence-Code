#!/bin/tcsh

#$ -M sstrauss@nd.edu
#$ -m ae
#$ -q long
#$ -N iceballsTOF
#$ -o logs/
#$ -j y

module load /afs/crc.nd.edu/user/n/nsl/nuclear/startup/nsl
module load root
cd /afs/crc.nd.edu/group/nsl/nuc/user/sstrauss/iceball_may2016/Code/Coincidence_Cuts
make clean
echo "Rebuilding..."
make
echo "Done rebuild"
echo "Running..."
./main
make clean

exit $?

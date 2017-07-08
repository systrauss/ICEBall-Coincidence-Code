#!/bin/tcsh

#$ -M sstrauss@nd.edu
#$ -m a
#$ -q long
#$ -N ICE_GS
#$ -o logs/
#$ -t 18-77
#$ -j y

module load /afs/crc.nd.edu/user/n/nsl/nuclear/startup/nsl
module load root/6.02
root-config --version
cd /afs/crc.nd.edu/group/nsl/nuc/users/sstrauss/GitHub/ICEBall-Coincidence-Code
echo "start task ${SGE_TASK_ID}"
date
./main $SGE_TASK_ID
echo "ended task ${SGE_TASK_ID}"
date

exit $?

module load /afs/crc.nd.edu/user/n/nsl/nuclear/startup/nsl
module load root
module swap root/6.02
cd /afs/crc.nd.edu/group/nsl/nuc/users/sstrauss/iceball_mar2016/Code/Cuts-Saw-Parallel
make clean
echo "Rebuilding..."
make
echo "Done rebuild"
echo "Running..."
qsub QueueScript.sh

exit $?

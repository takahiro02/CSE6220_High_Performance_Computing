
# clean temporary files
make clean

make int_calc			# make a binary again

echo "["

FIRST_ITER="yes"
for proc_num in "1" "2" "4" "8" "16" "32"; do # CoC-ICE seems to test only up to 48 processors
    if [ "$FIRST_ITER" = "yes" ]
    then
	FIRST_ITER="no"
    else
	echo ","
    fi
    mpirun -np $proc_num ./int_calc 1000000
    # change processor number for the same n = 10^6
done

echo "]"

When submitting the PBS script, it runs a shell script file run.sh, which runs int_calc for different numbers of processors (in powers of 2) with the fixed n = 10^6.

int_calc is made from main.cpp, which splits n elements of addition into p (= total number of processors) processors, let each processor calculate their portion of addition, and add all these local sums with MPI_Reduce().

To get the result, we used CoC-ICE.

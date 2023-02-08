
# refrence: https://opensource.com/article/18/8/what-how-makefile

int_calc: main.cpp
	mpicxx main.cpp -o int_calc -lm
# compile command is from getting_started_mpi.pdf from the course file
# -lm flag is for linking math library

clean:
	rm *.o int_calc		#remove any object files and the executable (int_calc)

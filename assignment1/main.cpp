

#include <mpi.h>
#include <iostream>		// for cout, cerr, etc
#include <cstdlib>		// for atoi()
#include <cmath>		// for ceil()

using namespace std;

int main(int argc, char *argv[]) {
  if(argc != 2){
    cerr << "Error, you need to add a command line argument n\n";
    return 1;
  }
  
  int n = atoi(argv[1]);
  // convert a command line argument to int
  // https://stackoverflow.com/questions/2797813/how-to-convert-a-command-line-argument-to-int
  
  // set up MPI
  MPI_Init(&argc, &argv);
  // get communicator size and my rank
  MPI_Comm comm = MPI_COMM_WORLD;
  // MPI_COMM_WORLD groups all available processors in the group
  // https://www.codingame.com/playgrounds/349/introduction-to-mpi/mpi_comm_world-size-and-ranks
  
  int p, rank;
  MPI_Comm_size(comm, &p);	// get the community size (# of processors)
  MPI_Comm_rank(comm, &rank);	// get the rank (kind of ID # in this community) of the current processor


  //MPI_Bcast(&n, 1, MPI_INT, 0, comm);
  // data buffer address, element count, data type, root rank, MPI communicator
  // https://www.open-mpi.org/doc/current/man3/MPI_Bcast.3.php
  // only the processor with root rank sends the data to all processors including itself, and all processors
  // receive it inside &n
  // So, MPI_Bcast() does both send and receive
  // https://stackoverflow.com/questions/2367300/corresponding-receive-routine-of-mpi-bcast
  // But in this assignment, since n is entered as a command line argument, all processors have it. So we don't need
  // to use MPI_Bcast() (from a TA's comment from Piazza).

  // calculate the local sum serially
  double starttime, endtime;
  if(rank == 0)			// time only at processor 0
    starttime = MPI_Wtime();
      
  double h = 1.0/n;
  // processor i takes charge of i*ceil(n/p)+1, i*ceil(n/p)+2, ..., (i+1)*ceil(n/p)
  // where p is the number of all processors in this communicator
  // Since the last processor may have fewer elements, change the end element's index for the last processor
  int begin_i{1+rank*static_cast<int>(ceil(double(n)/p))}; // index starts from 1, not 0, so add 1.
  int end_i{(rank+1)*static_cast<int>(ceil(double(n)/p))};
  if(end_i > n)
    end_i = n;

  double local_sum{0};
  for(int i=begin_i; i<=end_i; ++i) // remember to include end_i
    local_sum += 4 / (1+pow(h*(i-0.5),2));

  local_sum /= n;

  // do reduction (aggregate the local sums to 1 root processor)
  double global_sum{0};
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, comm);
  // doc: https://www.open-mpi.org/doc/current/man3/MPI_Reduce.3.php

  if(rank == 0)
    endtime = MPI_Wtime();
  
  //cout << "At processor " << rank << " / " << p << ", local_sum = " << local_sum << ", global_sum = " << global_sum << endl;
  if(rank == 0){
    //cout << "The elapsed run time at processor 0 is " << endtime - starttime << " seconds" << endl;

    // output in JSON format
    cout << "{\n";
    cout << "\"Number of processors\": " << p << ",\n";
    cout << "\"Runtime (seconds)\": " << endtime - starttime << ",\n";
    cout << "}\n";
  }
  
  // finalize MPI
  MPI_Finalize();
  return 0;
}

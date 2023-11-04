/*
 * Example program to calculate of integral
 * f(x)=tanh(c * x)^2 
 */

#include <stdio.h>
#include <math.h>
#include "mpi.h"


/* Prototype the function that we'll use below. */
static double f(double, double);
static double fi(double, double);

int
main(int argc, char *argv[])
{
  double a, b, c, Eps;
  int done = 0;
  char buf[40];
  int pos, i, n, rank, size, Ierr, namelen;
  double Sum, Gsum, Isum, time1, time2,a1, b1, x, F;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  MPI_Status  stats;

  /* Normal MPI startup */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name, &namelen);

  printf("Process %d of %d on %s\n", rank, size, processor_name);
  
  Eps = 1.0;
  while (!done)
  {
    if (rank == 0)  
    {
      printf("Enter Eps ( > 0.1 - quit) \n"); fflush(stdout);
      scanf("%lf",&Eps); printf("%10.9lf\n",Eps);

      printf("Enter a b c\n"); fflush(stdout);
      scanf("%lf %lf %lf", &a, &b, &c);
      
      time1 = MPI_Wtime();

      pos = 0;
      MPI_Pack(&a, 1, MPI_DOUBLE, &buf, 40, &pos, MPI_COMM_WORLD);
      MPI_Pack(&b, 1, MPI_DOUBLE, &buf, 40, &pos, MPI_COMM_WORLD);
      MPI_Pack(&c, 1, MPI_DOUBLE, &buf, 40, &pos, MPI_COMM_WORLD);
      MPI_Pack(&Eps, 1, MPI_DOUBLE, &buf, 40, &pos, MPI_COMM_WORLD);

    }

    /* Sending Eps to all nodes */
    MPI_Bcast(  &buf,               /* buffer               */
                40,                  /* one data             */
                MPI_PACKED,         /* type                 */
                0,                  /* to which node        */
                MPI_COMM_WORLD      /* common communicator  */
              );

    if (rank != 0)
    {
      pos = 0;
      MPI_Unpack(&buf, 40, &pos, &a, 1, MPI_DOUBLE, MPI_COMM_WORLD);
      MPI_Unpack(&buf, 40, &pos, &b, 1, MPI_DOUBLE, MPI_COMM_WORLD);
      MPI_Unpack(&buf, 40, &pos, &c, 1, MPI_DOUBLE, MPI_COMM_WORLD);
      MPI_Unpack(&buf, 40, &pos, &Eps, 1, MPI_DOUBLE, MPI_COMM_WORLD);
    }

    if(Eps > 0.1) done = 1;
    else
    {
      /* Each process define his integration limit 
      and a number of intervals */
      a1 = a+(b-a)*rank/size;
      b1 = a1+(b-a)/size;

      // n = 0.35/(Eps*size);
      n = 1.0/(Eps*size);

      /* Calculating of a local sum by each process */
      Sum = 0.0;
      for (i=1; i<=n; i++)
      {
        x = a1 + (b1 - a1) * (i - 0.5) / n;
        Sum += f(c, x);  
      }
      printf("Process %d SUMM  %.16f \n", rank, Sum/(n*size)*(b-a));    

      /* Sending the local sum to node 0 */
      Gsum = 0;

      MPI_Reduce( &Sum,             /* buffer input         */
                  &Gsum,            /* buffer output        */
                  1,                /* one data             */
                  MPI_DOUBLE,       /* type                 */
                  MPI_SUM,          /* operation with data  */
                  0,                /* to which node        */
                  MPI_COMM_WORLD    /* common communicator  */
                );

      if (rank == 0) 
      {
        Gsum = Gsum/(n*size)*(b-a);
    	   	     
        printf("\nIntegral of function tanh(c * x)^2 from %5.2f to %5.2f.\n",
                a, b);  
        printf("%d point. Integral = %18.16f, error = %18.16f.\n\n",
                n*size, Gsum, fi(c, b) - fi(c, a) - Gsum);
                
        time2 = MPI_Wtime();
        printf("Time calculation = %f seconds.\n", time2 - time1);
        fflush(stdout);
      }
    }
  }
  /* All done */

  MPI_Finalize();
  return 0;
}

/* Define function  */
static double f(double c, double  x)
{
  return (tanh(c * x)*tanh(c * x));
}

static double fi(double c, double  x)
{
  return (x - (tanh(c * x)/c));
}
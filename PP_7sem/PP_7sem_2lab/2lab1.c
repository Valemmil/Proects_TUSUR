/* extvec.c -- parallel program for calculate
 *               max, min (with indexes) and  average of array
 * Input      -- Input array is formed in program
 *                from random numbers
 * Author     -- Fefelov N.P., TUSUR, kafedra ASU
 * Last modification  -- 24.10.15
*/

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define m 19947  //20000
#define dp 100.0f


/* Function for init input vector  */
void initvec(int m1, double *arr1)
{ 
    int i;
    for(i=0; i<m1; i++)
        arr1[i] = (double)rand()/RAND_MAX * dp *2.0f - dp;
}


int main(int argc, char **argv)
{
    int rank,size;
    int nach,count,i,scol,ost;
    double  va[m], *vb;
    double  ta[m], *tb;
    double  x, *result_local, result[m];
    double time1,time2;
    int *displs, *rcounts;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    count=m / size;  ost=m % size;

    if (rank==0)    /* Process 0 - master  */
    {

        printf("Numbers of proccesses %d. \nElements in vector %d.\n",size, m);

        /* Init vector vA  */
        initvec(m, va);
        initvec(m, ta);

        time1=MPI_Wtime();  //Time begining calculating of programm

        /* Creation auxiliary arrays for data communication */
        displs  = (int *)malloc(size * sizeof(int));
        rcounts = (int *)malloc(size * sizeof(int));
        x = (double)rand()/RAND_MAX * dp *2.0f - dp;

        for(i=0;i < size;i++)
        {
            scol = i < ost ? count+1 : count;
            rcounts[i] = scol;
            nach = i*scol + (i >= ost ? ost : 0);
            displs[i] = nach;
        }

        for (i=0; i<size; i++) printf("%8d",rcounts[i]); printf(" rcounts \n");
        for (i=0; i<size; i++) printf("%8d", displs[i]); printf(" displs \n");

    }   /* End of work process 0  */

    /* Calculating parts of vector vA for rank */
    scol = rank < ost ? count+1 : count;
    /* Offset (in strings) part for rank in vector vA */
    nach = rank*scol + (rank >= ost ? ost : 0);

    /* Storage for part of array in rank */
    vb  = (double *)calloc(scol, sizeof(double));
    tb  = (double *)calloc(scol, sizeof(double));
    result_local  = (double *)calloc(scol, sizeof(double));

    /* Sending the parts of the vector vA and tA to processes */
    MPI_Scatterv(&va, rcounts, displs,MPI_DOUBLE, vb,
                 scol, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatterv(&ta, rcounts, displs, MPI_DOUBLE, tb,
                 scol, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    printf("Process %d Scol %d\n", rank, scol);

    /* Sending constant x */
    MPI_Bcast(&x, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (i = 0; i < scol; i++){
        result_local[i] = vb[i] * x + tb[i];
    }

    MPI_Gatherv(result_local, scol, MPI_DOUBLE, 
                result, rcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank==0)  /* Only master-process  */
    { //1
        time2=MPI_Wtime();  //Time ending programm
        printf("\nTime parallel calculation = %f s.\n",time2-time1);
        printf("\n1) %f * %f + %f = %f\n...", va[0], x, ta[0], result[0]);
        printf("\n%d) %f * %f + %f = %f\n", m, va[m-1], x, ta[m-1], result[m-1]);

        free(displs); free(rcounts);
    } //1 End work of master-process

	/* Delete storage array VB of process */
    free(vb);
    free(tb);
    free(result_local);

    MPI_Finalize();
    return 0;
}

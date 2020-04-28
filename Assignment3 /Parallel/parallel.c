#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#define m 500                /* number of rows in matrix A */
#define n 500               /* number of columns in matrix A */
#define q 500               /* number of columns in matrix B */
double wtime;

int main (int argc, char *argv[])
{
int    tid, nthreads, i, j, k, chunk;
double    a[m][n],           /* matrix A to be multiplied */
    b[n][q],           /* matrix B to be multiplied */
    c[m][q];           /* result matrix C */

chunk = 4;                    /* set loop iteration chunk size */
wtime = omp_get_wtime ( );
/*** Spawn a parallel region explicitly scoping all variables ***/
omp_set_dynamic(0);
omp_set_num_threads(64);
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)

  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Starting matrix multiple with %d threads\n",nthreads);
    printf("Initializing matrices...\n");
    }
  /*** Initialize matrices ***/
  #pragma omp for schedule (static, chunk)
  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      a[i][j]= i+j;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<n ; i++)
    for (j=0; j<q; j++)
      b[i][j]= i*j;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<m; i++)
    for (j=0; j<q; j++)
      c[i][j]= 0;

  /*** Do matrix multiply sharing iterations on outer loop ***/
  /*** Display who does which iterations for demonstration purposes ***/
  printf("Thread %d starting matrix multiply...\n",tid);
  #pragma omp for schedule (static, chunk)
  for (i=0; i<m; i++)
    {
    printf("Thread=%d did row=%d\n",tid,i);
    for(j=0; j<q; j++)
      for (k=0; k<n; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }   /*** End of parallel region ***/

/*** Print results ***/
printf("******************************************************\n");
printf("Result Matrix:\n");
for (i=0; i<m; i++)
  {
  for (j=0; j<q; j++)
    printf("%6.2f   ", c[i][j]);
  printf("\n");
  }
printf("******************************************************\n");

wtime = omp_get_wtime ( ) - wtime;
  printf ( "  Elapsed seconds = %g\n", wtime );

  printf("This system has %d processors configured and "
        "%d processors available.\n",
        get_nprocs_conf(), get_nprocs());
  printf ("Done.\n");
  return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define n 500
#define q 500
#define m 500

int main(void)
{
  clock_t startTime = clock();
  int i, j, k;

  double a[m][n], b[n][q], c[m] [q];

  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      a[i][j] = i + j;
  for (i = 0; i < n; i++)
    for (j = 0; j < q; j++)
      b[i][j] = i * j;
  for (i = 0; i < m; i++)
    for (j = 0; j < q; j++)
      c[i][j] = 0;

  for (i = 0; i < m; i++)
  {
    for (j = 0; j < q; j++)
      for (k = 0; k < n; k++)
        c[i][j] += (a[i][k] * b[k][j]);
  }

  printf("Final Matrix: \n");
  for (i = 0; i < m; i++)
  {
    for (j = 0; j < q; j++)
      printf("%5f  ", c[i][j]);
    printf("\n");
  }

  clock_t endTime = clock();

  printf("finish \n"); /* take this out */
  printf("Serial Execution time = %f seconds. \n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
}
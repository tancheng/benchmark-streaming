/* 32-tap FIR filter processing 1 point */
/* Modified to use arrays - SMP */

//#include "traps.h"

#include<iostream>

using namespace std;

#define SIZE 10000

void kernel(double **A, int *P, int N, double **IA);

int main()
{

  int N = 2;
  double **A = new double*[N];
  int *P = new int[N+1];
  double *x = new double[N];
  double *b = new double[N];
  double **IA = new double*[N];

  for(int i=0; i<N; ++i) {
    A[i] = new double[N];
    IA[i] = new double[N];
  }

  A[0][0] = 4;
  A[0][1] = 3;
  A[1][0] = 6;
  A[1][1] = 3;

  b[0] = 10;
  b[1] = 12;

  kernel(A, P, N, IA);

  return 0;
}

void kernel(double **A, int *P, int N, double **IA) {

  int bound = N*N*N;
//  #pragma clang loop unroll_count(4)
  for(int index=0; index<bound; index+=4) {
    int j = index / N / N;
    int i0 = index / N % N;
    int i1 = N-1-i0;
    int k = index % N;
    if(P[i0] == j) {
      IA[i0][j] = 1;
    } else {
      IA[i0][j] = 0;
    }
    if(k<i0) {
      IA[i0][j] -= A[i0][k] * IA[k][j];
    }
    if(k>=i1+1) {
      IA[i1][j] -= A[i1][k] * IA[k][j];
    }
    if(k==N-1){
      IA[i1][j] /= A[i1][i1];
    }

//    index++;
//    j = index / N / N;
//    i0 = index / N % N;
//    i1 = N-1-i0;
//    k = index % N;
//    if(P[i0] == j) {
//      IA[i0][j] = 1;
//    } else {
//      IA[i0][j] = 0;
//    }
//    if(k<i0) {
//      IA[i0][j] -= A[i0][k] * IA[k][j];
//    }
//    if(k>=i1+1) {
//      IA[i1][j] -= A[i1][k] * IA[k][j];
//    }
//    if(k==N-1){
//      IA[i1][j] /= A[i1][i1];
//    }
//
//    index++;
//    j = index / N / N;
//    i0 = index / N % N;
//    i1 = N-1-i0;
//    k = index % N;
//    if(P[i0] == j) {
//      IA[i0][j] = 1;
//    } else {
//      IA[i0][j] = 0;
//    }
//    if(k<i0) {
//      IA[i0][j] -= A[i0][k] * IA[k][j];
//    }
//    if(k>=i1+1) {
//      IA[i1][j] -= A[i1][k] * IA[k][j];
//    }
//    if(k==N-1){
//      IA[i1][j] /= A[i1][i1];
//    }
//
//    index++;
//    j = index / N / N;
//    i0 = index / N % N;
//    i1 = N-1-i0;
//    k = index % N;
//    if(P[i0] == j) {
//      IA[i0][j] = 1;
//    } else {
//      IA[i0][j] = 0;
//    }
//    if(k<i0) {
//      IA[i0][j] -= A[i0][k] * IA[k][j];
//    }
//    if(k>=i1+1) {
//      IA[i1][j] -= A[i1][k] * IA[k][j];
//    }
//    if(k==N-1){
//      IA[i1][j] /= A[i1][i1];
//    }

  }

//  for(int index=0; index<bound; ++index) {
//    int j = index / N / N;
//    int i0 = index / N % N;
//    int i1 = N-1-i0;
//    int k = index % N;
//    if(P[i0] == j) {
//      IA[i0][j] = 1;
//    } else {
//      IA[i0][j] = 0;
//    }
//    if(k<i0) {
//      IA[i0][j] -= A[i0][k] * IA[k][j];
//    }
//    if(k>=i1+1) {
//      IA[i1][j] -= A[i1][k] * IA[k][j];
//    }
//    if(k==N-1){
//      IA[i1][j] /= A[i1][i1];
//    }
//  }


/*
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N; i++) {
      IA[i][j] = P[i] == j ? 1.0 : 0.0;

      for (int k = 0; k < i; k++)
        IA[i][j] -= A[i][k] * IA[k][j];
    }

    for (int i = N - 1; i >= 0; i--) {
      for (int k = i + 1; k < N; k++)
        IA[i][j] -= A[i][k] * IA[k][j];

      IA[i][j] /= A[i][i];
    }
  }
*/

}


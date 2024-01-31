#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <sys/time.h>

void print_matrix(double *A,int N,int n){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){printf(" %f ,",A[i*n+j]);}
        printf("\n");
    }
    printf("\n");
}

long gettime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

double* GE(double* A,int n){
    double* coeff = (double*)calloc(n,sizeof(double));
    double A_inv;
    double max_,d_buff1;
    int i,j,k,max_index;
    for(i=0;i<n;i++){
        max_ = A[i*n+i]>0?A[i*n+i]:-A[i*n+i];
        max_index = i;
        for(j=i+1;j<n;j++){
            
            d_buff1 = (A[i*n+j]>0?A[i*n+j]:-A[i*n+j]);
            if(max_<d_buff1){
                max_ = d_buff1;
                max_index = j;
            }
        }
        if(i!=max_index){
            for(j=0;j<n;j++){
                d_buff1 = A[j*n+i];
                A[j*n+i] = A[j*n+max_index];
                A[j*n+max_index] = d_buff1;
            }
        }

        A_inv = 1/A[i*n+i];
        for(j=i+1;j<n;j++){coeff[j] = A[i*n+j]*A_inv;}
        for(j=i+1;j<n;j++){A[i*n+j]=0;}
        for(j=i+1;j<n;j++){
            for(k=i+1;k<n;k++){            
                A[j*n+k] -= coeff[k]*A[j*n+i];
            }
        }
    }
    return A;
}

int main(){
    unsigned long t2;
    unsigned long t1;
    int n=1000; int k = 6;
    int N=n;
    if(n>k){N=k;}
    double* A = (double*)calloc(n*n,sizeof(double));
    for(int i=0;i<n*n;i++){A[i]=(double)rand()/RAND_MAX;}
    //double K[9] = {1,5,7,2,9,5,3,1,8};for(int i=0;i<n*n;i++){A[i]=K[i];}
    print_matrix(A,N,n);
    t1 = gettime();
    A=GE(A,n);
    t2 = gettime();
    printf("time taken %f s\n",((double)t2-t1)/1000000);
    printf("\n");
    print_matrix(A,N,n);
    return 0;
}
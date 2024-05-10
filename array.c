#include<stdio.h>
#include<stdlib.h>
#include"array.h"
int main(){

    int n , i;
    int m , mi,sot,x,src ;
    int *A;
    float avg;
    
    printf("Enter the length of array\n");
    scanf("%d",&n);
    A = (int*)malloc(n* sizeof(int));
    printf("Enter the elements of Array\n");
    for(i=0;i<n;i++)
    scanf("%d",&A[i]);

    m=max(A,n);
    printf("The max value of an array is %d\n",m);

    mi=min(A,n);
    printf("The Min value of an aray is %d\n",mi);

    sot = sort(A,n);
    printf("The ascending order of array is:");
    for(i=0;i<n;i++)
    printf("%d \t",A[i]);
    printf("\n");

    avg = average(A,n);
    printf("The average of an array is %.2f\n",avg);

    printf("Enter the Number to be counted \n");
    scanf("%d",&x);
    src = count(A,n,x);
    printf("The number of times the %d is repearting : %d times \n",x, src);
    free(A);
}

int max(int A[], int k){
  int t,i;
	t=A[0];
	for(i=1;i<k;i++)
        {
		if(A[i]>t)
			t=A[i];
    }
    return t ;
}


int min(int A[] , int k){
    int t,i;
    t=A[0];
	for(i=1;i<k;i++)
        {
		if(A[i]<t)
			t=A[i];
    }
    return t ;
}


int sort(int A[],int k){
 int i, j, temp;
 for(i=0;i< k-1;i++)
 {
  for(j=i+1;j< k;j++)
  {
   if(A[i]>A[j])
   {
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
   }
  }
 }
}

float average(int A[],int k){
 int i;
 float avg , sum = 0.0;
 for(i=0;i< k;i++)
  sum = sum + A[i];
  avg = sum/k;
 return avg;
}

int count(int A[] , int k , int key){
    int count = 0;
    int i;
    for(i = 0; i < k; i++)  
    {  
        if(A[i] == key)  
        {   
          count++;  
        }  
    } 
    return count;
}
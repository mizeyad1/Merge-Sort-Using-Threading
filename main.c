#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void * mergesort(void *a);
int N;
int *vector;
int main()
{
    FILE* fp;
    int i;
    fp=fopen("input.txt","r");
    fscanf(fp,"%d",&N);
    printf("Number of elements is %d\n",N);
     vector=(int*)malloc(N*sizeof(int));
    fgetc(fp);
    for(i=0;i<N;i++)
    {
    fscanf(fp,"%d ",&vector[i]);
    }
    printf("Array before sort:\n");
    for(i=0;i<N;i++)
    {
        printf("%d ",vector[i]);
    }
    printf("\n");
        int m[2];
        m[0]=0;
        m[1]=N-1;
        pthread_t mrgthread;


        pthread_create(&mrgthread, NULL, mergesort, &m);


        pthread_join(mrgthread, NULL);
        printf("Array after sort:\n");
        for(i=0;i<N;i++)
    {
        printf("%d ",vector[i]);
    }



    return 0;
}
void merge(int i,int j)
{

        int a1 = i;
        int middle = (i+j)/2;
        int b1 = middle+1;
        int newa1=0;
        int x=j-i+1;
        int newarray[x];


        while(a1 <= middle && b1 <= j) {
                if (vector[a1] > vector[b1])
                        newarray[newa1++] = vector[b1++];
                else
                        newarray[newa1++] = vector[a1++];
        }

        while(a1 <= middle) {
                newarray[newa1++] = vector[a1++];
        }

        while(b1 <= j) {
                newarray[newa1++] = vector[b1++];
        }

        for (a1 = 0; a1 < x ; a1++)
                vector[i+a1] = newarray[a1];
}
void * mergesort(void *a)
{
        int *p = (int *)a;
        int n1 [2];
        int n2[2];
        int mid = (p[0]+p[1])/2;
        pthread_t id1, id2;

        n1[0] = p[0];
        n1[1] = mid;

        n2[0] = mid+1;
        n2[1] = p[1];

        if (p[0] >= p[1]) return;

          pthread_create(&id1, NULL, mergesort, &n1);



          pthread_create(&id2, NULL, mergesort, &n2);


        pthread_join(id1, NULL);
        pthread_join(id2, NULL);

        merge(p[0], p[1]);
        pthread_exit(NULL);
}

#include <stdio.h>

int maxSubArray(int *A, int n)
{
    int sum=0;
    int maxsum=0x80000000;
    int maxsum2=0x80000000;

    if(n-1>0)
        maxsum2=maxSubArray(A+1,n-1);

    for(int i=0; i<n; i++) {
        sum+=A[i];
        if(sum>maxsum)
            maxsum=sum;
    }

    if(maxsum>maxsum2)
        return maxsum;
    else
        return maxsum2;
}

int *init_array(int *n)
{
    int cnt=0,tmp,i=0;
    int *res;
    char strtmp[16];
    FILE *fp=fopen("testdata","r");

    while(fscanf(fp,"%s",&strtmp)==1)
        cnt++;

    fclose(fp);
    res=calloc(cnt,sizeof(int));
    fp=fopen("testdata","r");

    while(fscanf(fp,"%s",&strtmp)==1) {
        tmp=atoi(strtmp);
        res[i]=tmp;
        i++;
    }
    *n=cnt;
    return res;
}

void print_arr(int *a,int n)
{
    for(int i=0; i<n; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    int *arr=init_array(&n);
    print_arr(arr,n);

    printf("maxSum = %d\n",maxSubArray(arr,n));
    return 0;
}

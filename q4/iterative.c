#include <stdio.h>

int maxSubArray(int A[], int n)
{
    int sum=0;
    int maxsum=0x80000000;

    for(int range=1,i; range<=n; range++) {
        sum=0;
        for(i=0; i<range; i++) {
            sum+=A[i];
        }
        while(i<n) {
            if(sum>maxsum)
                maxsum=sum;

            sum+=A[i];
            sum-=A[i-range];
            i++;
        }
    }

    return maxsum;
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

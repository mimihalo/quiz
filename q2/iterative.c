#include <stdio.h>

char smallest_character(char str[], char c)
{
    int i=0;
    while(str[i]!='\0') {
        if(str[i]>c)
            return str[i];
        i++;
    }
    return str[0];
}

int main(int argc, char* argv[])
{
    char str[128];
    char c;
    char res;
    FILE *fp=fopen(argv[1],"r");
    fgets(str,128,fp);
    fscanf(fp,"%c",&c);
    fflush(stdin);

    res=smallest_character(str, c);
    printf("%c\n",res);

    return 0;
}

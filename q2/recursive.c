#include <stdio.h>

char smallest_character(char str[], char c)
{
    char tmp;
    if(str[0]!='\0') {
        if(str[0]>c)
            return str[0];
        else {
            tmp=smallest_character(str+1,c);
            if(tmp<=c)
                return str[0];
            else
                return tmp;
        }
    }
    return 0;
}

int main()
{
    char str[128];
    char c;
    char res;
    printf("str: ");
    gets(str);
    printf("c: ");
    scanf("%c",&c);
    fflush(stdin);

    res=smallest_character(str, c);
    printf("%c\n",res);

    return 0;
}
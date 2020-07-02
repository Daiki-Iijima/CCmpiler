#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    int val;
    if(scanf("%d", &val) == EOF)
    {
        perror("scanf");
        exit(1);
    }

    printf("\t.text\n"
         "\t.global cmain\n"
         "cmain:\n"
         "\tmov $%d, %%eax\n"
         "\tret\n", val);
    return 0;
}
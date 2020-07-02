#include <stdio.h>

extern int cmain(void);

int main(int argc,char **argv)
{
    int val = cmain();
    printf("%d\n",val);

    return 0;
}
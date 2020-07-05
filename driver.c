#include <stdio.h>

// 8ccでglobalで作成したcmainラベルの関数を定義
extern int cmain(void);

int main(int argc,char **argv)
{
    int val = cmain();
    printf("%d\n",val);

    return 0;
}
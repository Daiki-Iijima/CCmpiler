#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    int val;
    if(scanf("%d", &val) == EOF)    //  入力を受け取って、何も入力されていなければ終了
    {
        perror("scanf");
        exit(1);
    }

    //  AT&T構文では、レジスタを参照する場合には、レジスタ名の前に「%」をプレフィクスとして付けなくてはいけない。 
    //  同様に定数の場合には、AT&T構文ではプレフィクスとして「$」が必要となる。

    printf("\t.text\n"              //  .text : メモリ中の何処にデータやテキストを配置するかを制御するためのアセンブラ指令
         "\t.global cmain\n"        //  .global : 後に続くラベルや変数(この場合はcmain)を外部で使用できるようにする
         "cmain:\n"                 //  ラベル宣言
         "\tmov $%d, %%eax\n"       //  mov : AT&T構文になっているので、第二オペランドに第一オペランドを代入
         "\tret\n", val);           //  ret : return 直前で扱かったeaxないの値を返す
         
    return 0;
}
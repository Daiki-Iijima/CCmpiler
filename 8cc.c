#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  //  文字の種類の判定や文字の変換を行うための関数が宣言されている
#include <stdarg.h> //  可変長引数 (variable arguments) を処理するためのマクロが定義されている

#define BUFLEN 256

//  char *fmt,...でprintfみたいな使い方ができるようになる
//  error("test%c",t);
void error(char *fmt, ...)
{
    va_list args;                //  可変長配列を作成
    va_start(args, fmt);         //  初期化(fmtに何個の引数が来ているかわからない)
    vfprintf(stderr, fmt, args); //  printfのストリーム指定、可変長配列対応版
                                 //  stderr: 標準エラー出力
    fprintf(stderr, "\n");       //  第1引数のストリームに第2引数の文字列を出力
    va_end(args);                //  可変長配列を解放
    exit(1);                     //  異常終了
}

//  数字をコンパイル
void compile_number(int n)
{
    int c;
    while ((c = getc(stdin)) != EOF)
    {
        if (isspace(c)) //isspace : 空白文字かどうか判別
            break;
        if (!isdigit(c)) //isdigit S: 文字が数字であるかどうかを判別
            error("この文字は数字ではありません : '%c'", c);

        n = n * 10 + (c - '0');
    }

    printf(".text\n\t"
           ".global intfn\n"
           "intfn:\n\t"
           "mov $%d, %%rax\n\t" //  rax : アキュムレータの「A」です。歴史的に演算専用のレジスタ
           "ret\n",
           n);
}

void compile_string(void)
{
    char buf[BUFLEN];
    int i = 0;
    for (;;)
    {
        int c = getc(stdin);
        if (c == EOF)
            error("文字列で終了しました");
        if (c == '"')
            break;
        if (c == '\\')
        {
            c = getc(stdin);
            if (c == EOF)
                error("\\で終了しました");
        }
        buf[i++] = c;
        if (i == BUFLEN - 1)
            error("文字列が長すぎます");
    }
    buf[i] = '\0';

    printf("\t.data\n"                  //  .data : データセグメントにデータを配置する
           ".mydata:\n\t"
           ".string \"%s\"\n\t"
           ".text\n\t"
           ".global stringfn\n"
           "stringfn:\n\t"
           "lea .mydata(%%rip),%%rax\n\t" //  lea : 第1引数オペランドのアドレスを計算し、そのアドレスを第2引数オペランドにロード
           "ret\n",
           buf);
}

void compile(void)
{
    int c = getc(stdin);
    if (isdigit(c))
        return compile_number(c - '0');
    if (c == '"')
        return compile_string();

    error("%cの文字列は処理できません '%c'", c);
}

int main(int argc, char **argv)
{
    compile();
    return 0;
}
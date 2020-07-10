#!/bin/bash

function compile
{
    echo "$1" | ./8cc > tmp.s
    if [ $? -ne 0 ]; then       # 正常終了したか
        echo "コンパイル失敗"
        exit
    fi
    gcc -o tmp.out driver.c tmp.s
    if [ $? -ne 0 ]; then       # 正常終了したか
        echo "GCC失敗"
        exit
    fi
}

function test
{
    # 入力を受け取る
    expected="$1"
    expr="$2"
    compile "$expr"
    result="`./tmp.out`"

    # 正常に指定したファイル名でコンパイルできたかチェック
    if [ "$result" != "$expected" ]; then
        echo "Test failed: $expected expected but got $result"
        exit
    fi
}

function testfail
{
    expr = "$1"

    # 2>&1 : 標準エラー出力の結果を標準出力にマージする
    # > /dev/null : 標準出力を捨てる
    echo "$expr" | ./8cc > /dev/null 2>&1

    if [ $? -ne 0 ]; then       # 正常終了したか
        echo "コンパイルに失敗しましたが、テストは成功しました: $expr"
        exit
    fi
}

# -s : コマンドを実行する際に、コマンドの表示を行わない
make -s 8cc

test 0 0
test abc '"abc"'

testfail '"abc'
testfail '0abc'

echo "All tests passed"
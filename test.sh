#!/bin/bash

function test
{
    # 入力を受け取る
    expected="$1"
    expr="$2"

    # 8ccをコンパイルして、出力をtmp.sに保存
    echo "$expr" | ./8cc > tmp.s

    # 正常に実行できたかチェック
    # $? : 直前に実行したコマンドの終了ステータス
    # ! : コマンドが失敗した場合に真
    if [ ! $? ]; then
        echo "Failed to compile $expr"
        exit
    fi

    # -o filename: filenameに指定した名前でファイルを出力
    gcc -o tmp.out driver.c tmp.s || exit
    result="`./tmp.out`"

    # 正常に指定したファイル名でコンパイルできたかチェック
    if [ "$result" != "$expected" ]; then
        echo "Test failed: $expected expected but got $result"
        exit
    fi
}

# -s : コマンドを実行する際に、コマンドの表示を行わない
make -s 8cc

# 上で定義したtest関数に引数を2つ渡してテスト
test 0 0
test 42 42

rm -f tmp.out tmp.s
echo "All tests passed"
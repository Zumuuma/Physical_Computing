#!/usr/bin/python
# -*- coding: utf-8 -*-

def convert_from_10_to_2():
    x = 5  # １０進数から２進数に変換したい整数（１０進数を入力）
    i = 0  # iの初期化 兼 forの初期値
    data = []  # 空の配列data
    for i in range(3):  # ３回繰り返す
        tmp = x % 2  # まずは剰余（余り）を求める
        x = x//2  # 入力した１０進数を割る
        data.append(tmp)  # tmpに代入した剰余（余り）を配列dataにアペンド（追加）
        i = i+1  # iの値をインクリメント（i++みたいな感じ）
    data.reverse()  # forの繰り返し処理が終わってから配列dataの中身を逆にする
    datastr = map(str, data)  # 配列dataの中身を文字列（string）に変換
    result = ''.join(datastr)  # 文字列（string）を結合
    return result  # 文字列が結合された中身をリターン


if __name__ == '__main__':
    print(convert_from_10_to_2())

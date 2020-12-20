#!/usr/bin/python
# -*- coding: utf-8 -*-

def list_to_str(data):
    data_new = map(str, data)  # 配列dataの中身を文字列（string）に変換
    result = ''.join(data_new)  # 文字列（string）を結合
    return result  # 文字列が結合された中身をリターン


if __name__ == '__main__':
    data = ['abc', [1, 2, 3], 4, 'g']
    print(list_to_str(data))  # 配列dataを引数に与えて関数を呼び出して表示

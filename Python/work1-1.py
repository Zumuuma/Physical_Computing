data = ['a', 'abcde', 'sdf', 'jh']


def find_longest_string(data_list):
    longest = data[0]
    for i in data_list:
        if len(i) > len(longest):
            longest = i
    return longest


print(find_longest_string(data))

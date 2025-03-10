import random

def counting_sort_str(arr, max_len, sym):
    cnt_arr = [0] * 27
    res = [0] * len(arr)

    for s in arr:
        order = ord(s[sym]) - ord('a') + 1 if sym < len(s) else 0
        cnt_arr[order] += 1

    for i in range(1, 27):
        cnt_arr[i] += cnt_arr[i - 1]

    for s in arr[::-1]:
        order = ord(s[sym]) - ord('a') + 1 if sym < len(s) else 0
        paste_ind = cnt_arr[order] - 1
        res[paste_ind] = s
        cnt_arr[order] -= 1

    return res


def my_radix_sort(arr: list):
    max_len = len(max(arr, key=len))

    for sym in range(max_len -1, -1, -1):
        arr = counting_sort_str(arr, max_len, sym)
        print(arr)
    return arr

d1 = ['gag', 'vkbsj', 'adfaf', 'tqwtt', 'varkbhv']
print(d1)
my_radix_sort(d1)

'''
d2 = """In my younger and more vulnerable years my father gave me some advice
    that I ve been turning over in my mind ever since   Whenever you feel like
    criticizing anyone   he told me   just remember that all the people in this
    world haven t had the advantages that you ve had"""
d2 = d2.lower().split()
d3 = """Tell mr  O Muse  of that ingenious hero who travelled far and wide after
he had sacked the famous town of Troy  Many cities did he visit  and many were
the nations with whose manners and customs he was acquainted  moreover he
    suffered much by sea while trying to save his own life and bring his men
        safely home  but do what he might he could not save his men  for they
        perished through their own sheer folly in eating the cattle of the Sun
        god Hyperion  so the god prevented them from ever reaching home  Tell
        me  too  about all these things  oh daughter of Jove  from whatsoever
        source you may know them  """
d3 = d3.lower().split()

assert my_radix_sort(d1) == sorted(d1)
assert my_radix_sort(d2) == sorted(d2)
assert my_radix_sort(d3) == sorted(d3)
'''

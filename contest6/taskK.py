import sys


def BinSearch(arr, x):
    left, right = 0, len(arr)
    while left < right:
        mid = (left + right) // 2
        if arr[mid] >= x:
            left = mid + 1
        else:
            right = mid
    return left


input_data = sys.stdin.read().split()
if not input_data:
    exit()
n = int(input_data[0])
a = list(map(int, input_data[1:n + 1]))
tails = []
tails_idx = []
P = [-1] * n
for i, x in enumerate(a):
    idx = BinSearch(tails, x)
    if idx < len(tails):
        tails[idx] = x
        tails_idx[idx] = i
    else:
        tails.append(x)
        tails_idx.append(i)
    if idx > 0:
        P[i] = tails_idx[idx - 1]
length = len(tails)
print(length)
res = []
curr = tails_idx[-1]
while curr != -1:
    res.append(curr + 1)
    curr = P[curr]
print(' '.join(map(str, res[::-1])))

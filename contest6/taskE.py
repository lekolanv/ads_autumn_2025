n, m = [int(x) for x in input().split()]
used = []
j = m
w = [int(x) for x in input().split()]
c = [int(x) for x in input().split()]
dp = [[0] * (m + 1) for _ in range(n + 1)]
for i in range(1, n + 1):
    for j in range(m + 1):
        dp[i][j] = dp[i-1][j]
        if j >= w[i-1] and dp[i-1][j-w[i-1]] + c[i-1] > dp[i][j]:
            dp[i][j] = dp[i-1][j-w[i-1]] + c[i-1]
for i in range(n, 0, -1):
    if dp[i][j] != dp[i-1][j]:
        used.append(i)
        j -= w[i-1]
for idx in reversed(used):
    print(idx)

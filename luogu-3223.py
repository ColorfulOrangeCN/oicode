N, M = map(int, input().split())
def fac(n):
    x = 1
    for i in range(2, n + 1):
        x = x * i
    return x
print(fac(N) * (N + 1) * fac(N + 2) * (N * N + 3 * N + 2 * M) // fac(N - M + 3))

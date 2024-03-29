import sys


def read_ints():
    return map(int, sys.stdin.readline().split())


def read_int():
    return int(sys.stdin.readline())


def main():
    n = read_int()
    l, r = 0, n + 1
    while r - l > 1:
        m = (l + r) // 2
        if m * (m + 1) * (m + 5) // 6 <= n + 1:
            l = m
        else:
            r = m
    print(l)


main()

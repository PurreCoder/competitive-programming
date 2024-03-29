import sys


def read_ints():
    return list(map(int, sys.stdin.readline().split()))


def read_int():
    return int(sys.stdin.readline())


def main():
    n, m = read_ints()
    a = read_ints()
    pref = [0] * (len(a) + 1)
    for i in range(1, len(a) + 1):
        pref[i] = pref[i - 1] + a[i - 1]

    for _ in range(m):
        squads, orcs = read_ints()
        l, r = -1, n - squads + 1
        while r - l > 1:
            m = (l + r) // 2
            if pref[m + squads] - pref[m] <= orcs:
                l = m
            else:
                r = m
        print(l + 1 if l != -1 and pref[l + squads] - pref[l] == orcs else -1)


main()

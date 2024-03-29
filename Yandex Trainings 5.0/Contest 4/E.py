import sys


def read_int() -> int:
    return int(sys.stdin.readline())


def main():
    n = read_int()
    # finding sum of numerator and denominator of i-th fraction
    l, r = 0, int(2e9)
    while r - l > 1:
        m = (l + r) // 2
        if m * (m + 1) / 2 >= n:
            r = m
        else:
            l = m

    frac_sum = r + 1
    n -= r * (r - 1) // 2
    if r % 2 == 0:
        n = frac_sum - n
    print(f'{n}/{frac_sum - n}')


main()

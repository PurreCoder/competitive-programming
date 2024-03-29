import sys


def read_ints() -> list[int]:
    return list(map(int, sys.stdin.readline().split()))


def read_int() -> int:
    return int(sys.stdin.readline())


def get_page_height(a: list[int], width: int) -> int:
    row, col = 1, 1
    for num in a:
        if col + num - 1 <= width:
            col += num + 1
        else:
            row += 1
            col = num + 2
    return row


def is_possible_to_fit(a: list[int], b: list[int], w: int, h: int) -> bool:
    # bounds for page partition
    l, r = max(a) - 1, w - max(b)

    if get_page_height(a, r) > h:
        return False

    while r - l > 1:
        m = (l + r) // 2
        if get_page_height(a, m) > h:
            l = m
        else:
            r = m

    return get_page_height(b, w - r) <= h


def main():
    w, n, m = read_ints()
    a = read_ints()
    b = read_ints()

    l, r = 0, max(n, m)
    while r - l > 1:
        m = (l + r) // 2
        if is_possible_to_fit(a, b, w, m):
            r = m
        else:
            l = m
    print(r)


main()

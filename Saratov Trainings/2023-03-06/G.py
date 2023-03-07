x, y, l, r = map(int, input().split())

lst = list()
a = 0
while x ** a + 1 <= r:
    b = 0
    while x ** a + y ** b <= r:
        if x ** a + y ** b >= l:
            lst.append(x ** a + y ** b)
        b += 1
    a += 1
lst.sort()

ans = 0
if lst:
    ans = max(ans, max(lst[0] - l, r - lst[-1]))
    for i in range(1, len(lst)):
        ans = max(ans, lst[i] - lst[i - 1] - 1)
else:
    ans = r - l + 1
print(ans)

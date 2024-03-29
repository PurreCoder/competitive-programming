#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <stack>
#include <iomanip>
#include "inttypes.h"

using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define mp(x, y) make_pair(x, y)

using ld = long double;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;

template <typename T>
istream& operator>>(istream& in, vector <T>& arr)
{
    for (T& i : arr) in >> i;
    return in;
}

bool check(int a, int b, int c, int d, int type)
{
    if (a + c > b + d)
    {
        return true;
    }
    if (a + c == b + d && (type == 1 && c > b || type == 2 && a > d))
    {
        return true;
    }
    return false;
}

void solve()
{
    int a, b;
    int c, d;
    scanf("%d:%d", &a, &b);
    scanf("%d:%d", &c, &d);
    int type;
    scanf("%d", &type);


    int l = -1, r = 100;
    while (r - l > 1)
    {
        int m = (l + r) / 2;
        if (check(a, b, c + m, d, type))
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }
    cout << r;
}

int main()
{
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
        //cout << '\n';
    }
    return 0;
}

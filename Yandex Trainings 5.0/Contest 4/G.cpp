#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string>
#include <stack>
#include <iomanip>
#include "inttypes.h"
#include <sstream>
#include <climits>

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
istream& operator>>(istream& in, vector<T>& arr)
{
    for (T& i : arr) in >> i;
    return in;
}

// TLE?

vvi build_dp(vector<string>& field)
{
    int rows = field.size();
    int cols = field[0].size();
    vvi hor(rows, vi(cols));
    for (int i = 0; i < rows; ++i)
    {
        hor[i][0] = (field[i][0] == '#');
    }
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 1; j < cols; ++j)
        {
            hor[i][j] = (field[i][j] == '#' ? hor[i][j - 1] + 1 : 0);
        }
    }

    vvi dp(rows, vi(cols));
    for (int i = 0; i < cols; ++i)
    {
        dp[0][i] = (field[0][i] == '#');
    }
    for (int i = 1; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            dp[i][j] = (field[i][j] == '#' ? dp[i - 1][j] + 1 : 0);
        }
    }

    for (int i = 0; i < rows; ++i)
    {
        dp[i][0] = (field[i][0] == '#');
    }
    for (int i = 1; i < rows; ++i)
    {
        for (int j = 1; j < cols; ++j)
        {
            dp[i][j] = min(dp[i - 1][j - 1] + 1, min(hor[i][j], dp[i][j]));
        }
    }
    return dp;
}

bool check(vvi& dp, int square)
{
    int rows = dp.size();
    int cols = dp[0].size();

    vii shifts = {
        mp(square - 1, 2 * square - 1), mp(2 * square - 1, square),
        mp(2 * square - 1, 2 * square - 1),
        mp(2 * square - 1, 3 * square - 1), mp(3 * square - 1, 2 * square - 1)
    };

    for (int i = 0; i <= rows - 3 * square; ++i)
    {
        for (int j = 0; j <= cols - 3 * square; ++j)
        {
            bool fits = true;
            for (auto [dx, dy]: shifts)
            {
                if (dp[i + dx][j + dy] < square)
                {
                    fits = false;
                    break;
                }
            }
            if (fits) return true;
        }
    }
    return false;
}

void solve()
{   
    int rows, cols;
    cin >> rows >> cols;
    vector<string> field(rows);
    for (auto& st : field) cin >> st;
    vvi dp = build_dp(field);

    int max_square = 1;
    for (int i = 1; i < rows; ++i)
    {
        for (int j = 1; j < cols; ++j)
        {
            max_square = max(max_square, dp[i][j]);
        }
    }

    int l = max(1, max_square / 3);
    int r = min(min(rows, cols) / 3, max_square) + 1;
    while (r - l > 1)
    {
        int m = (l + r) / 2;
        if (check(dp, m))
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }
    cout << l;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
        //cout << '\n';
    }
    return 0;
}

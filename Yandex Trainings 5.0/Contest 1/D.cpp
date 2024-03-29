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

void solve()
{
    vector<string> board(8);
    cin >> board;
    vector<vector<char>> beaten(8, vector<char>(8, 0));

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] == '*') continue;

            beaten[i][j] = true;

            if (board[i][j] == 'R')
            {
                for (int u = 1; u < 8; ++u)
                {
                    if (i + u < 8 && board[i + u][j] == '*')
                        beaten[i + u][j] = true;
                    else break;
                }
                for (int u = 1; u < 8; ++u)
                {
                    if (i - u >= 0 && board[i - u][j] == '*')
                        beaten[i - u][j] = true;
                    else break;
                }
                for (int u = 1; u < 8; ++u)
                {
                    if (j + u < 8 && board[i][j + u] == '*')
                        beaten[i][j + u] = true;
                    else break;
                }
                for (int u = 1; u < 8; ++u)
                {
                    if (j - u >= 0 && board[i][j - u] == '*')
                        beaten[i][j - u] = true;
                    else break;
                }
            }
            else
            {
                if (board[i][j] == 'B')
                {
                    for (int x = 1; x < 8; ++x)
                    {
                        if (i - x >= 0 && j - x >= 0 && board[i - x][j - x] == '*')
                        {
                            beaten[i - x][j - x] = true;
                        }
                        else break;
                    }
                    for (int x = 1; x < 8; ++x)
                    {
                        if (i + x < 8 && j - x >= 0 && board[i + x][j - x] == '*')
                        {
                            beaten[i + x][j - x] = true;
                        }
                        else break;
                    }
                    for (int x = 1; x < 8; ++x)
                    {
                        if (i - x >= 0 && j + x < 8 && board[i - x][j + x] == '*')
                        {
                            beaten[i - x][j + x] = true;
                        }
                        else break;
                    }
                    for (int x = 1; x < 8; ++x)
                    {
                        if (i + x < 8 && j + x < 8 && board[i + x][j + x] == '*')
                        {
                            beaten[i + x][j + x] = true;
                        }
                        else break;
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            ans += (beaten[i][j] == 0);
        }
    }
    cout << ans;
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

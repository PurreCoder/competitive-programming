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

void mark_horizontally(vector<string>& pic, int x, int y, char c)
{
    int len = 0;
    while (y + len < pic[x].size() && pic[x][y + len] == '#')
    {
        pic[x][y + len] = c;
        ++len;
    }

    for (int j = x + 1; j < pic.size(); ++j)
    {
        if (pic[j][y] != '#') return;

        int row_len = 1;
        while (y + row_len < pic[j].size() && pic[j][y + row_len] == '#') ++row_len;

        if (row_len != len) return;

        for (int i = y; i - y < row_len; ++i) pic[j][i] = c;
    }
}

void mark_vertically(vector<string>& pic, int x, int y, char c)
{
    int len = 0;
    while (x + len < pic.size() && pic[x + len][y] == '#') 
    {
        pic[x + len][y] = c;
        ++len;
    }

    for (int j = y + 1; j < pic[x].size(); ++j)
    {
        if (pic[x][j] != '#') return;
        
        int row_len = 1;
        while (x + row_len < pic.size() && pic[x + row_len][j] == '#') ++row_len;

        if (row_len != len) return;

        for (int i = x; i - x < row_len; ++i) pic[i][j] = c;
    }
}

bool detach(vector<string>& pic, int x, int y)
{
    // vertical line
    if (y + 1 == pic[x].size() || pic[x][y + 1] == '.')
    {
        pic[x][y] = 'b';
        return x + 1 < pic.size() && pic[x + 1][y] == 'a';
    }

    for (int i = x; i < pic.size() && pic[i][y] == 'a'; ++i)
    {
        pic[i][y] = 'b';
    }
    return true;
}

bool solve_vertically(vector<string> pic)
{
    int m = pic.size();
    int n = pic[0].size();

    int cnt = 0;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (pic[i][j] == '#')
            {
                ++cnt;
                if (cnt > 2) return false;
                mark_vertically(pic, i, j, 'a' + cnt - 1);
            }
        }
    }

    if (cnt != 1 && cnt != 2) return false;

    if (cnt == 2)
    {
        cout << "YES\n";
        for (string s : pic)
        {
            cout << s << '\n';
        }
        return true;
    }

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (pic[i][j] != '.')
            {
                if (detach(pic, i, j))
                {
                    cout << "YES\n";
                    for (string s : pic)
                    {
                        cout << s << '\n';
                    }
                    return true;
                }
                return false;
            }
        }
    }
}

bool solve_horizontally(vector<string> pic)
{
    int m = pic.size();
    int n = pic[0].size();

    int cnt = 0;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (pic[i][j] == '#')
            {
                ++cnt;
                if (cnt > 2) return false;
                mark_horizontally(pic, i, j, 'a' + cnt - 1);
            }
        }
    }

    if (cnt != 1 && cnt != 2) return false;

    if (cnt == 2)
    {
        cout << "YES\n";
        for (string s : pic)
        {
            cout << s << '\n';
        }
        return true;
    }

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (pic[i][j] != '.')
            {
                if (detach(pic, i, j))
                {
                    cout << "YES\n";
                    for (string s : pic)
                    {
                        cout << s << '\n';
                    }
                    return true;
                }
                return false;
            }
        }
    }
}

void solve()
{
    int m, n;
    cin >> m >> n;
    vector<string> pic(m);
    cin >> pic;

    if (solve_vertically(pic)) return;
    if (solve_horizontally(pic)) return;

    cout << "NO";
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

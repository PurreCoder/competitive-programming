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

int p;

int destroy_barrack(int x, int y, int pcur)
{
    if (pcur >= 2 * x) return -1;

    int steps = 0;
    int y_prev = -1, pcur_prev = -1;
    while (x > 0 && (y > 0 || pcur > 0))
    {
        if (y > 0)
        {
            int shot = x;
            int mn = std::min(shot, y);
            y -= mn;
            shot -= mn;
            pcur = std::max(pcur - shot, 0);

            x = std::max(x - pcur, 0);

            if (y > 0) pcur += p;
        }
        else
        {
            pcur = std::max(pcur - x, 0);
            x = std::max(x - pcur, 0);
        }
        ++steps;

        if (y == y_prev && pcur == pcur_prev) return -1;
        y_prev = y;
        pcur_prev = pcur;
    }

    return (x > 0 ? steps : -1);
}

int count_rounds(int x, int y, int pcur)
{
    if (pcur >= 2 * x) return -1;

    int best_ans = -1;
    int steps = 0;
    int y_prev = -1, pcur_prev = -1;
    while (x > 0 && (y > 0 || pcur > 0))
    {
        int obliterate = destroy_barrack(x, y, pcur);
        if (obliterate != -1)
        {
            if (best_ans == -1 || steps + obliterate < best_ans)
            {
                best_ans = steps + obliterate;
            }
        }

        int shot = x;
        if (pcur > 0) {
            int mn = std::min(pcur, shot);
            pcur -= mn;
            shot -= mn;
        }
        y = std::max(y - shot, 0);

        x = std::max(x - pcur, 0);

        if (y > 0) pcur += p;
        ++steps;

        if (y == y_prev && pcur == pcur_prev) return best_ans;
        y_prev = y;
        pcur_prev = pcur;
    }

    if (x <= 0 && best_ans == -1) return -1;
    if (x > 0 && best_ans != -1) return std::min(steps, best_ans);
    if (x > 0) return steps;
    return best_ans;
}

void solve()
{
    int x, y;
    std::cin >> x >> y >> p;
    std::cout << count_rounds(x, y, 0);
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

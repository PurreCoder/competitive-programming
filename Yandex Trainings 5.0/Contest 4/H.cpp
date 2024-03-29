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

bool check(vii& parties, vll& suff_sum, vi& sorted_votes, int money)
{
    int n = parties.size();
    for (auto [votes, pay] : parties)
    {
        if (pay == -1) continue;

        int new_votes = votes + money - pay;

        int l = -1, r = n;
        while (r - l > 1)
        {
            int m = (l + r) / 2;
            if (sorted_votes[m] >= new_votes)
            {
                r = m;
            }
            else
            {
                l = m;
            }
        }

        r += (money == pay);
        if (suff_sum[r] - ll(n - r) * new_votes + n - r <= money - pay) return true;
    }
    return false;
}

void find_ans(vii& parties, vll& suff_sum, vi& sorted_votes, int money)
{
    int n = parties.size();
    for (int candidate_num = 0; candidate_num < n; ++candidate_num)
    {
        auto [votes, pay] = parties[candidate_num];
        if (pay == -1) continue;

        int new_votes = votes + money - pay;

        int l = -1, r = n;
        while (r - l > 1)
        {
            int m = (l + r) / 2;
            if (sorted_votes[m] >= new_votes)
            {
                r = m;
            }
            else
            {
                l = m;
            }
        }

        r += (money == pay);
        if (suff_sum[r] - ll(n - r) * new_votes + n - r <= money - pay)
        {
            cout << candidate_num + 1 << '\n';

            vi ans(n);
            ans[candidate_num] = new_votes;
            int spent = 0;
            for (int j = 0; j < n; ++j)
            {
                if (j != candidate_num)
                {
                    int prev_votes = parties[j].first;
                    ans[j] = min(prev_votes, new_votes - 1);
                    spent += prev_votes - ans[j];
                }
            }

            int rest = (money - pay) - spent;
            for (int i = 0; i < n && rest > 0; ++i)
            {
                if (i != candidate_num)
                {
                    int delta = min(rest, ans[i]);
                    ans[i] -= delta;
                    rest -= delta;
                }
            }

            for (int num : ans) cout << num << ' ';
            return;
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    vii parties(n);
    for (auto& [votes, pay] : parties) cin >> votes >> pay;
    
    vi sorted_votes(n);
    for (int i = 0; i < n; ++i)
    {
        sorted_votes[i] = parties[i].first;
    }
    sort(all(sorted_votes));

    int max_pay = 1;
    for (auto& [votes, pay] : parties) max_pay = max(max_pay, pay);

    vll suff_sum(n + 1);
    for (int i = n - 1; i >= 0; --i)
    {
        suff_sum[i] = suff_sum[i + 1] + sorted_votes[i];
    }

    int l = 0, r = sorted_votes[n - 1] - sorted_votes[0] + 1 + max_pay;
    while (r - l > 1)
    {
        int m = (l + r) / 2;
        if (check(parties, suff_sum, sorted_votes, m))
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }

    cout << r << '\n';
    find_ans(parties, suff_sum, sorted_votes, r);
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

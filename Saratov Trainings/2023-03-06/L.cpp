#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>

using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;

template <typename T>
istream& operator>>(istream& in, vector <T>& arr)
{
    for (T& i : arr) in >> i;
    return in;
}

template <typename T>
ostream& operator<<(ostream& out, vector <T>& arr)
{
    for (T& i : arr) out << i << ' ';
    out << '\n';
    return out;
}

ll merge(vector<int> &a, int l, int m, int r)
{
    std::queue<int> lq, rq;
    for (int i = l; i < m; ++i)
    {
        lq.push(a[i]);
    }
    for (int j = m; j < r; ++j)
    {
        rq.push(a[j]);
    }
    lq.push(2e9); // inf
    rq.push(2e9); // inf

    ll res = 0;
    for (int i = l; i < r; ++i)
    {
        int lv = lq.front(), rv = rq.front();
        if (lv <= rv)
        {
            a[i] = lv;
            lq.pop();
        }
        else
        {
            a[i] = rv;
            rq.pop();
            res += lq.size() - 1;
        }
    }
    return res;
}

ll merge_sort(vector<int> &a, int l, int r)
{
    if (r - l <= 1)
    {
        return 0;
    }
    int m = (l + r) / 2;
    ll res = merge_sort(a, l, m);
    res += merge_sort(a, m, r);
    res += merge(a, l, m, r);
    return res;
}

ll count_inversions(vector<int>& a)
{
    return merge_sort(a, 0, a.size());
}

void solve()
{
    int n;
    cin >> n;
    vector<pair<bool, int>> animals;
    vector<int> toads, frogs;
    for (int u = 0; u < 2 * n; ++u)
    {
        char type;
        int num;
        cin >> type >> num;
        type = (type == 'T');
        --num;
        animals.push_back({ type, num });
        if (type)
        {
            toads.push_back(num);
        }
        else
        {
            frogs.push_back(num);
        }
    }
    
    int toads_inversions = count_inversions(toads);
    int frogs_inversions = count_inversions(frogs);

    vvi toads_to_pass(n + 1, vi(n + 1)); // [num][frog] = toads with number >= num to the left of the frog
    vvi frogs_to_pass(n + 1, vi(n + 1)); // [num][toad] = frogs with number >= num to the left of the toad
    for (int i = 0; i < n; ++i)
    {
        int toads_passed = 0;
        int frogs_passed = 0;
        for (int j = 0; j < animals.size(); ++j)
        {
            if (animals[j].first)
            {
                frogs_to_pass[i][animals[j].second] = frogs_passed;
                toads_passed += (animals[j].second >= i);
            }
            else
            {
                toads_to_pass[i][animals[j].second] = toads_passed;
                frogs_passed += (animals[j].second >= i);
            }
        }
    }
    for (int i = 0; i <= n; ++i) // there are no frogs or toads with number >= n (0-based)
    {
        toads_to_pass[i][n] = 0;
        frogs_to_pass[i][n] = 0;
    }

    vvi dp(n + 1, vi(n + 1)); // dp[toads][frogs] = required swaps between kinds
    for (int i = 1; i <= n; ++i)
    {
        dp[i][0] = dp[i - 1][0] + frogs_to_pass[0][i - 1];
        dp[0][i] = dp[0][i - 1] + toads_to_pass[0][i - 1];
    }
    for (int i = 1; i <= n; ++i) // toads
    {
        for (int j = 1; j <= n; ++j) // frogs
        {
            dp[i][j] = min(dp[i - 1][j] + frogs_to_pass[j][i - 1], dp[i][j - 1] + toads_to_pass[i][j - 1]);
        }
    }
    cout << toads_inversions + frogs_inversions + dp[n][n];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    #ifndef ONLINE_JUDGE
        FILE* fin;
        freopen_s(&fin, "input.txt", "r", stdin);
    #endif
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

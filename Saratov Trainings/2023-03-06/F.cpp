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

void solve()
{
    ll n, d;
    cin >> n >> d;
    cout << ((n + 1) * (n + 1) - 4 * d >= 0 ? "YES\n" : "NO\n");
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
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

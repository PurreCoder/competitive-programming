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

void check_set(vi& sets, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            int nm = sets[i] & sets[j];
            if (nm & (nm - 1))
            {
                return;
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int bit = n - 1; bit >= 0; --bit)
        {
            cout << ((sets[i] & (1 << bit)) != 0);
        }
        cout << '\n';
    }
    cout << "\n\n\n";
}

void generate_set(vi& nums, vi& sets, int ind)
{
    int n = nums.size();
    int set = (1 << nums[ind]) - 1;
    
    if (set)
    {
        int limit = (1LL << n);
        while (set < limit)
        {
            if (ind != n - 1)
            {
                sets[ind] = set;
                generate_set(nums, sets, ind + 1);
            }
            else
            {
                sets[ind] = set;
                check_set(sets, n);
            }
            int c = set & -set;
            int r = set + c;
            set = (((r ^ set) >> 2) / c) | r;
        }
    }
    else
    {
        if (ind != n - 1)
        {
            sets[ind] = set;
            generate_set(nums, sets, ind + 1);
        }
        else
        {
            sets[ind] = set;
            check_set(sets, n);
        }
    }
    
}

void place_dots(vi& nums, int n)
{
    /*for (int num : nums)
    {
        cout << num << ' ';
    }
    cout << '\n';*/

    vi sets(n);
    generate_set(nums, sets, 0);
}

void find_solution(int n, int hyp)
{
    if (n <= 1) return;
    vi nums;
    int last_nz = 0;
    int base_num = hyp / n;
    hyp = hyp % n;
    {
        nums.assign(n, base_num);
        for (int i = 0; hyp; ++i)
        {
            ++nums[i];
            --hyp;
        }
        while (last_nz + 1 < n && nums[last_nz + 1] != 0) ++last_nz;
    }

    while (true)
    {
        place_dots(nums, n);

        int min_ind = last_nz - 1;
        if (min_ind == 0) break;
        while (min_ind - 1 >= 0 && nums[min_ind - 1] == nums[last_nz - 1]) --min_ind;
        
        if (++nums[min_ind] > n) break;
        nums[last_nz]--;

        int sum = 0;
        for (int i = min_ind + 1; i < n; ++i)
        {
            sum += nums[i];
        }
        base_num = sum / (n - min_ind - 1);
        int rest = sum - base_num * (n - min_ind - 1);
        for (int i = min_ind + 1; i < n; ++i)
        {
            nums[i] = base_num;
            if (rest)
            {
                ++nums[i];
                --rest;
            }
        }
        last_nz = 0;
        while (last_nz + 1 < n && nums[last_nz + 1] != 0) ++last_nz;
    }
}

void solve()
{
    find_solution(7, 22); // 21 possible, 22 impossible (checked for 20 mins)
}

int main()
{
    solve();
    return 0;
}

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
#include <random>

using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define mp(x, y) make_pair(x, y)

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

template<class T>
class Treap
{
    static inline std::minstd_rand generator = std::minstd_rand();

    struct Node
    {
        T value;
        int priority;
        int size;
        Node* l = nullptr, * r = nullptr;
        Node(T val) : value(val), priority(generator()), size(1) {}
    } *root = nullptr;

    static int get_size(Node *node)
    {
        return (node ? node->size : 0);
    }

    static void update_size(Node* node)
    {
        if (node)
        {
            node->size = get_size(node->l) + get_size(node->r) + 1;
        }
    }

    static Node* merge(Node* lhs, Node* rhs)
    {
        if (!lhs || !rhs) return (lhs ? lhs : rhs);
        if (lhs->priority > rhs->priority)
        {
            lhs->r = merge(lhs->r, rhs);
            update_size(lhs);
            return lhs;
        }
        else
        {
            rhs->l = merge(lhs, rhs->l);
            update_size(rhs);
            return rhs;
        }
    }

    static void split(Node* node, int cnt, Node*& lhs, Node*& rhs)
    {
        if (!node)
        {
            lhs = rhs = nullptr;
            return;
        }
        if (get_size(node->l) < cnt)
        {
            split(node->r, cnt - get_size(node->l) - 1, node->r, rhs);
            lhs = node;
        }
        else
        {
            split(node->l, cnt, lhs, node->l);
            rhs = node;
        }
        update_size(lhs);
        update_size(rhs);
    }

public:
    T get(int index)
    {
        Node* less, * equal, * greater;
        split(root, index, less, greater);
        split(greater, 1, equal, greater);
        T result = equal->value;
        root = merge(merge(less, equal), greater);
        return result;
    }

    void push_back(T value)
    {
        root = merge(root, new Node(value));
    }

    void push_front(T value)
    {
        root = merge(new Node(value), root);
    }

    void insert(int index, T value)
    {
        Node* less, *greater;
        split(root, index, less, greater);
        root = merge(merge(less, new Node(value)), greater);
    }

    void erase(int index)
    {
        Node* less, * equal, * greater;
        split(root, index, less, greater);
        split(greater, 1, equal, greater);
        root = merge(less, greater);
    }

    void erase(int l, int r)
    {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r - l + 1, equal, greater);
        root = merge(less, greater);
    }

    void move_to_front(int l, int r)
    {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r - l + 1, equal, greater);
        root = merge(equal, merge(less, greater));
    }

    int size() const
    {
        return getSize(root);
    }
};


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    FILE* fin;
    freopen_s(&fin, "input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    Treap<char> tr;
    for (int i = 0; i < n; ++i)
    {
        char c;
        cin >> c;
        tr.push_back(c);
    }

    while (m--)
    {
        char query_type;
        cin >> query_type;
        if (query_type == 'a')
        {
            int from, to;
            cin >> from >> to;
            char particle = tr.get(from - 1);
            tr.erase(from - 1);
            tr.insert(to - 1, particle);
        }
        else
        {
            int pos;
            cin >> pos;
            cout << tr.get(pos - 1) << '\n';
        }
    }

    return 0;
}

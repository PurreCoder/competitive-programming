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

class Treap
{
    static minstd_rand generator;

    struct Node
    {
        int key, priority;
        int size;
        Node* l = nullptr, * r = nullptr;
        Node(int key) : key(key), priority(generator()), size(1) {}
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

    // all keys in lhs are less than all keys in rhs
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

    static void split(Node* node, int key, Node*& lhs, Node*& rhs)
    {
        if (!node)
        {
            lhs = rhs = nullptr;
            return;
        }
        if (node->key < key)
        {
            split(node->r, key, node->r, rhs);
            lhs = node;
        }
        else
        {
            split(node->l, key, lhs, node->l);
            rhs = node;
        }
        update_size(lhs);
        update_size(rhs);
    }

    static int min(Node* node)
    {
        if (!node)
        {
            return -1; //
        }
        while (node)
        {
            node = node->l;
        }
        return node->key;
    }

public:
    bool contains(int key)
    {
        Node* node = root;
        while (node)
        {
            if (node->key == key) return true;
            node = (node->key < key ? node->r : node->l);
        }
        return false;
    }

    void insert(int key)
    {
        Node* less, *greater;
        split(root, key, less, greater);
        root = merge(merge(less, new Node(key)), greater);
    }

    void erase(int key)
    {
        Node* less, * equal, * greater;
        split(root, key, less, greater);
        split(greater, key + 1, equal, greater);
        equal = merge(equal->l, equal->r);
        root = merge(less, greater);
    }

    int next(int key)
    {
        Node* less, * greater;
        split(root, key + 1, less, greater);
        int result = min(greater);
        root = merge(less, greater);
        return result;
    }

    int index_by_key(int key)
    {
        Node* less, * greater;
        split(root, key, less, greater);
        int result = get_size(less);
        root = merge(less, greater);
        return result;
    }

    int key_by_index(int index)
    {
        Node* cur = root;
        while (cur)
        {
            int left_size = get_size(cur->l);
            if (index == left_size) return cur->key;
            if (index < left_size)
            {
                cur = cur->l;
            }
            else
            {
                cur = cur->r;
                index -= left_size + 1;
            }
        }
        return -1;
    }
};

minstd_rand Treap::generator;

int main()
{
    Treap tr;
    for (int i = 0; i < 10; ++i)
    {
        tr.insert(5);
    }
    for (int i = -11; i < 11; ++i)
    {
        cout << i << ' ' << tr.key_by_index(i) << '\n';
    }
    return 0;
}

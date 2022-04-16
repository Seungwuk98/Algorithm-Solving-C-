#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

const int AL = 27;
int n;

struct Node
{
    vector<pair<char, Node *>> child;
    int visit;
    int end;
    Node() : visit(0), end(n - 1) {}
    ~Node()
    {
        for (auto &p : child)
        {
            delete p.second;
        }
    }

    void insert(string &s, int i, int &idx)
    {
        if (s.size() == i)
        {
            child.push_back(make_pair(0, new Node()));
            child.back().second->visit += 1;
            end = idx;
            return;
        }
        for (auto &p : child)
        {
            if (p.first == s[i])
            {
                p.second->visit += 1;
                p.second->insert(s, i + 1, idx);
                return;
            }
        }
        child.push_back(make_pair(s[i], new Node()));
        child.back().second->visit += 1;
        child.back().second->insert(s, i + 1, idx);
    }

    int find(string &s, int i)
    {
        if (s.size() == i)
            return end;
        for (auto &p : child)
        {
            if (s[i] == p.first)
                return p.second->find(s, i + 1);
        }
        return n - 1;
    }

    int value(string &s, int i)
    {
        int result = 0;
        for (auto &p : child)
        {
            result += p.second->visit;
        }
        if (s.size() == i)
            return result;
        for (auto &p : child)
        {
            if (p.first == s[i])
            {
                result += p.second->value(s, i + 1);
                break;
            }
        }
        return result;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    string word[n];
    Node *root;
    root = new Node();
    for (int i = 0; i < n; i++)
    {
        cin >> word[i];
        root->insert(word[i], 0, i);
    }
    int q;
    string search;
    cin >> q;
    int idx;
    vector<tuple<int, string, int>> query;
    Node *nroot = new Node();
    for (int i = 0; i < q; i++)
    {
        cin >> search;
        idx = root->find(search, 0);
        query.push_back(make_tuple(idx, search, i));
    }
    sort(query.begin(), query.end());
    int li = -1, ni = 0;
    int result[q]{};
    for (auto &p : query)
    {
        ni = get<0>(p);
        for (int i = li + 1; i <= ni; i++)
        {
            nroot->insert(word[i], 0, i);
        }
        result[get<2>(p)] = nroot->value(get<1>(p), 0);
        li = ni;
    }
    for (int r : result)
        cout << r << '\n';

    delete root, nroot;

} // namespace std;

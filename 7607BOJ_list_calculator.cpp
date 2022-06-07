#include <bits/stdc++.h>

using namespace std;

struct lst{
    vector<int> array;
    string recursion;

    lst(){
        recursion = "";
    }
    lst(vector<int> array, string recursion) :
        array(array), recursion(recursion) {}

    lst operator+(lst other) {

    }
    oper
    int size(){
        return array.size();
    }
    void push_back(int x){
        if (!recursion.empty()) array.push_back(x);

    }

    int back(){
        return array.back();
    }

    void static make_same_size(lst &A, lst &B) {
        while (A.size() > B.size()) B.push_back(B.back());
        while (A.size() < B.size()) A.push_back(A.back());
    }
};

unordered_map<char, int> prefer;

vector<int> simpleLst(string s) {
    vector<int> ret;
    string t = "";
    for (int i=0; i<s.size(); ++i) {
        if (s[i] == ':') {
            ret.push_back('')
        }
    }
}

vector<string> seperate(string p) {
    vector<string> s1;
    for (int i=0, j=0; i<p.size(); i=j) {
        string c = "";
        while (j < p.size() && prefer.find(p[j]) == prefer.end()) {
            c += p[j++];
        }
        if (!c.empty()) s1.push_back(c);
        if (j < p.size()) {
            string t; t += p[j++];
            s1.emplace_back(t);
        } 
    }
    return s1;
}


int main()
{
    string s; 
    prefer['('] = 0;
    prefer[')'] = 1;
    prefer['+'] = 2;
    prefer['-'] = 2;
    prefer['/'] = 3;
    prefer['*'] = 3;
    while (cin >> s) {
        if (s == "#") break;
        if (s == "print") {
            cin >> s;
            vector<string> x = seperate(s);
            for (auto t : x) cout << t << ' ';
            cout << endl;
        } else {

        }
    }

} // namespace std;

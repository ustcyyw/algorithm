/**
 * @Time : 2025/3/9-11:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF159C 1400 数据结构 线段树 二分查找
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, P = 13331;
ll n, k, q;
vector<int> chars[26];
string s, t;
#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = val[ls] + val[rs];
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res += search(rs, mid + 1, r, a, b);
        return res;
    }
public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};
vector<SegmentTree> trees;

void change(SegmentTree& tree, vector<int>& arr, int p) {
    int lo = 0, hi = arr.size() - 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        int cnt = tree.search(0, mid);
        if(cnt >= p) hi = mid;
        else lo = mid + 1;
    }
    tree.add(lo, 0);
    s[arr[lo]] = '.';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> k >> t >> q;
    for(int i = 0; i < k; i++)
        s += t;
    for(int i = 0; i < s.size(); i++)
        chars[s[i] - 'a'].push_back(i);
    for(int i = 0; i < 26; i++) {
        trees.push_back(SegmentTree(chars[i].size() + 1));
        for(int j = 0; j < chars[i].size(); j++)
            trees[i].add(j, 1);
    }
    char c;
    for(int i = 1, p; i <= q; i++) {
        cin >> p >> c;
        change(trees[c - 'a'], chars[c - 'a'], p);
    }
    string ans;
    for(char c : s)
        if(c != '.') ans.push_back(c);
    cout << ans;
}
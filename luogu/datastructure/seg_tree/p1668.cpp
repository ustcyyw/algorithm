/**
 * @Time : 2023/5/9-9:36 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

# define ls (x << 1)
# define rs (x << 1 | 1)
using namespace std;
int n, t;

class Tree{
    int R;
    vector<int> val, tag;
public:
    Tree(int r) {
        this->R = r;
        val = vector(4 * (r + 1), INT_MAX);
        tag = vector(4 * (r + 1), 0);
    }

    int search(int a, int b) {
        return search(1, 0, R, a, b);
    }

    int search(int x, int l, int r, int a, int b){
        if(a <= l && r <= b) return val[x];
        down(x);
        int mid = (l + r) >> 1, res = INT_MAX;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
        return res;
    }

    void change(int a, int b, int v) {
        change(1, 0, R, a, b, v);
    }

    void change(int x, int l, int r, int a, int b, int v) {
        if(a <= l && r <= b) {
            val[x] = tag[x] = v;
            return;
        }
        down(x);
        int mid = (r + l) >> 1;
        if(a <= mid) change(ls, l, mid, a, b, v);
        if(b > mid) change(rs, mid + 1, r, a, b, v);
        update(x);
    }

    void down(int x){
        if(tag[x] == 0) return;
        tag[ls] = tag[rs] = tag[x];
        val[ls] = val[rs] = tag[x];
        tag[x] = 0;
    }

    void update(int x) {
        val[x] = min(val[ls], val[rs]);
    }
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> t;
    vector<int> range(t + 1, INT_MAX);
    for(int i = 0, s, e; i < n; i++) {
        cin >> s >> e;
        range[e] = min(range[e], s);
    }
    vector<vector<int>> cows;
    for(int i = 1; i <= t; i++)
        if(range[i] != INT_MAX) cows.push_back({range[i], i});
    sort(cows.begin(), cows.end(),
         [](auto& a, auto& b) -> bool {return a[1] < b[1];});
    Tree tree(t);
    tree.change(0, 0, 0);
    for(int i = 0, j = 1; i < cows.size(); i++) {
        int l = cows[i][0], r = cows[i][1];
        int val = tree.search(l - 1, r - 1);
        if(val == INT_MAX) continue;
        tree.change(j, r, val + 1);
        j = r + 1;
    }
    int res = tree.search(t, t);
    cout << (res == INT_MAX ? -1 : res) << endl;
}
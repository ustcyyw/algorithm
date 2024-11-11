/**
 * @Time : 2023/10/18-9:26 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
#define ls (2 * x)
#define rs (2 * x + 1)
int T, n, m;
vector<int> s, tag;
multimap<int, int> mp;

void down_add(int x) {
    if(tag[x] == 0) return;
    tag[ls] += tag[x]; tag[rs] += tag[x];
    tag[x] = 0;
}

// a, b是所指定的区间
void add(int x, int l, int r, int a, int b, int val) {
    if(a <= l && r <= b) {
        tag[x] += val;
        return;
    }
    down_add(x);
    int mid = (l + r) >> 1;
    if(a <= mid) add(ls, l, mid, a, b, val);
    if(b > mid) add(rs, mid + 1, r, a, b, val);
}

// 单点查询
int search(int x, int l, int r, int pos) {
    if(l == r) return tag[x];
    down_add(x);
    int mid = (l + r) >> 1;
    if(pos <= mid) return search(ls, l, mid, pos);
    else return search(rs, mid + 1, r, pos);
}
// 更新回文串信息 先删除后重新check
void remove_add(int i) {
    mp.erase(i);
    int v1 = (s[i] + search(1, 1, n, i)) % 26;
    int v2 = (s[i + 1] + search(1, 1, n, i + 1)) % 26;
    int v3 = i == n - 1 ? -1 : (s[i + 2] + search(1, 1, n, i + 2)) % 26;
    if(v1 == v2) mp.insert(make_pair(i, i + 1));
    if(v1 == v3) mp.insert(make_pair(i, i + 2));
}
void query1(int l, int r, int x) {
    add(1, 1, n, l, r, x % 26);
    // 左边界会影响到回文串
    if(l - 1 >= 1) remove_add(l - 1);
    if(l - 2 >= 1) remove_add(l - 2);
    // 右边界也会影响到回文串
    if(r < n) remove_add(r);
    if(r - 1 >= 1) remove_add(r - 1);
}
// 判断[l,r]上是否包含回文串
bool query2(int l, int r) {
    auto it = mp.lower_bound(l);
    if(it == mp.end() || (*it).first >= r) return false;
    if((*it).second <= r) return true;
    if(++it == mp.end()) return false;
    return (*it).second <= r;
}

// 检查初始时刻的长度为2和3的回文字符串
void check() {
    for(int i = 1; i <= n; i++) {
        if(s[i] == s[i + 1]) mp.insert(make_pair(i, i + 1));
        if(s[i - 1] == s[i + 1]) mp.insert(make_pair(i - 1, i + 1));
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> n >> m;
        string temp;
        cin >> temp;
        tag = vector(4 * n, 0);
        mp = {};
        s = vector(n + 2, -1);
        for(int j = 1; j <= n; j++)
            s[j] = temp[j - 1] - 'a';
        check();
        for(int j = 1, t, l, r, x; j <= m; j++) {
            cin >> t >> l >> r;
            if(t == 2) cout << (query2(l, r) ? "NO" : "YES") << endl;
            else {
                cin >> x;
                query1(l, r, x);
            }
        }
    }
}
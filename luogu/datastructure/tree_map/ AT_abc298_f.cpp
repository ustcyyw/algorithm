/**
 * @Time : 2023/8/28-4:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
long long n;

unordered_map<int, unordered_map<int, int>> cols; // 某一行的点对应所在的(列,值)集合
unordered_map<int, long long> r_sum, c_sum; // 行、列对应的和
multiset<long long> vals;

void change(int x, int sign) {
    for(auto& p : cols[x]) {
        int y = p.first, v = p.second;
        long long sum = c_sum[y], ns = sum + sign * v;
        vals.erase(vals.find(sum));
        vals.insert(ns);
        c_sum[y] = ns;
    }
}

long long solve() {
    long long res = 0ll;
    for(auto& p : r_sum) {
        int x = p.first;
        long long s1 = p.second;
        change(x, -1);
        res = max(res, s1 + *(vals.rbegin()));
        change(x, 1);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vals.clear(), cols.clear(), r_sum.clear(), c_sum.clear();
    for(int i = 0, x, y, v; i < n; i++) {
        cin >> x >> y >> v;
        cols[x][y] = v;
        r_sum[x] += v, c_sum[y] += v;
    }
    for(auto& p : c_sum)
        vals.insert(p.second);
    cout << solve() << endl;
}
/**
 * @Time : 2024/11/19-5:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2037F 二分 离散化 差分 2100
 */
 /*
  * (m - dx) * t >= hi
  * m - dx >= hi / t, 向上取整,  dx <= m - hi / t
  * abs(x - p) <= val[i] = m - hi / t
  * p的取值范围[x - val[i], x + val[i]]
  * 对t进行二分 对于确定的t计算每个点对应的p可行区间 进行离散化之后差分 观察区间端点处的值是否 >= k
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, k, h[N], x[N], range[N][2];

/*
 * 将数组进行离散化
 */
vector<int> scatter(vector<int>& num) {
    vector<int> pos = num;
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    return pos;
}
/*
 * 离散化之后查询某个数在第几个位置 可以同时记录该位置对应的数
 */
int find(vector<int>& pos, int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

bool check(int t) {
    vector<int> arr;
    for(int i = 1; i <= n; i++) {
        int val = m - (h[i] % t == 0 ? h[i] / t : h[i] / t + 1);
        int lo = x[i] - val, hi = x[i] + val;
        range[i][0] = lo, range[i][1] = hi;
        // lo > hi 说明无解 也就是把p设置在x[i]在规定时间内还是没法消灭敌人
        if(lo <= hi) arr.push_back(lo), arr.push_back(hi);
    }
    vector<int> pos = scatter(arr);
    vector<int> diff(pos.size() + 1, 0);
    for(int i = 1; i <= n; i++) {
        if(range[i][0] > range[i][1]) continue;
        int l = find(pos, range[i][0]), r = find(pos, range[i][1]);
        diff[l]++, diff[r + 1]--;
    }
    for(int i = 0, sum = 0; i < diff.size(); i++) {
        sum += diff[i];
        if(sum >= k) return true;
    }
    return false;
}

void solve() {
    int lo = 1, hi = 1e9 + 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    if(lo == 1e9 + 1) cout << "-1\n";
    else cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> n >> m >> k;
        map<ll, vector<int>> mp;
        for(int i = 1; i <= n; i++)
            cin >> h[i];
        for(int i = 1; i <= n; i++)
            cin >> x[i];
        solve();
    }
};
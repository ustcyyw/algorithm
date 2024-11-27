/**
 * @Time : 2024/11/26-11:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1607H 贪心 排序 双指针 2200
 */
/*
  * 要能满足相同 一个必要条件是 总重量相同 所以首先按总重量分组 a + b - m
对于每一个分组 可以算食物a的范围
1. m都用于吃a: max(0, a - m)
2. m都用于吃b 那么a就可以少吃 剩下的a就多。b这边的消耗为min(b, m)，那么还需要吃 m - min(b, m)
a能剩的最多的情况为 a - (m - min(b, m)) = a - m + min(b, m)

从食物a的范围来看 如果两个菜有交集 就可以通过操作将两个菜变为同一个菜（同组） 总的菜品组数量-1
先考虑边界 也就是a范围右边界最小的那个菜（这个右边界为hi） 他总要在某一个组中
那么为了能让这个组的菜更多，应该将a的值定为hi，然后看后续有多少个菜可以将a调整到这个值
这些菜最终变成一个菜品组（归为这个菜品组的菜 也可以归到后续其它组 但菜品组的数量并不会变）
将这个组归类好后，继续在剩余的菜中考虑上述过程
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, ans[N][2];
map<int, vector<vector<int>>> mp;

int cal(vector<vector<int>>& arr) {
    sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {
        return a[5] == b[5] ? a[4] < b[4] : a[5] < b[5];
    });
    int cnt = 0, sz = arr.size();
    for(int i = 0, j; i < sz; ) {
        j = i, cnt++;
        int hi = arr[i][5];
        while(j < sz && arr[j][4] <= hi) {
            int idx = arr[j][0], a = arr[j][1], m = arr[j][3];
            int am = a - hi, bm = m - am;
            ans[idx][0] = am, ans[idx][1] = bm;
            j++;
        }
        i = j;
    }
    return cnt;
}

void solve() {
    int cnt = 0;
    for(auto& p : mp)
        cnt += cal(p.second);
    cout << cnt << "\n";
    for(int i = 1; i <= n; i++)
        cout << ans[i][0] << " " << ans[i][1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        mp = {};
        for(int i = 1, a, b, m; i <= n; i++) {
            cin >> a >> b >> m;
            int l = max(0, a - m), r = a - m + min(b, m);
            mp[a + b - m].push_back({i, a, b, m, l, r});
        }
        solve();
    };
};
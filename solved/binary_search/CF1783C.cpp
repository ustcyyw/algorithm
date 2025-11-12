/**
 * @Time : 2024/5/28-10:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * n个人 相等的剩场 名次是相同的
  * 第1、2、3、4、...n
  * 已经确定会赢0、1、2、3、... n - 2、n - 1场
  *
  * 要拿第一名：全赢 或者赢n-1个人 且要赢最后一个人
  *
  * 拿第二名：
  * 总胜场n-1 要赢n-1个人 那就赢需要准备时间最少的n-1个
  * 总胜利场n-2 并且要赢了倒数第二个人
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
typedef long long ll;
ll T, n, m, sum[N], pos[N];
vector<vector<int>> infos;

bool check(int rk) {
    // 如果要独占第rk名 需要赢的场次;
    // 或者并列rk名，需要赢t-1场，并且一定要赢编号为t的这个人
    int t = n + 1 - rk;
    if(sum[t] <= m) return true;
    if(pos[t] <= t - 1 && sum[t - 1] <= m) return true;
    if(t > 1 && pos[t] > t - 1 && sum[t - 2] + infos[pos[t] - 1][0] <= m) return true;
    return false;
}

void solve() {
    sort(infos.begin(), infos.end());
    for(int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + infos[i - 1][0];
        pos[infos[i - 1][1]] = i; // 记录第i个人所在的位置
    }
    int lo = 1, hi = n + 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        infos.clear();
        for(int i = 1, val; i <= n; i++) {
            cin >> val;
            infos.push_back({val, i});
        }
        solve();
    }
};
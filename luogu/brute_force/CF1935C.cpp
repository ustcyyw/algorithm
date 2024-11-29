/**
 * @Time : 2024/11/28-10:56 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1935C 1800 暴力枚举 贪心 优先队列
 */
 /*
  * 将bi贡献的项拆解 这一项的值就是第一项和最后一项的差
  * 因此只要固定首项和尾项这个值固定，中间的数就尽量选ai小的
  * n = 2000 所以直接枚举首项和尾项即可
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, l;
vector<vector<int>> arr;

void solve() {
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        priority_queue<int> pq;
        ll sum = 0, bl = arr[i][1];
        for(int j = i; j <= n && arr[j][1] - bl <= l; j++) {
            sum += arr[j][0], pq.push(arr[j][0]);
            while(!pq.empty() && sum + arr[j][1] - bl > l) {
                sum -= pq.top();
                pq.pop();
            }
            ans = max(ans, (int)pq.size());
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> l;
        arr.assign(n + 1, vector(2, 0));
        for(int i = 1; i <= n; i++)
            cin >> arr[i][0] >> arr[i][1];
        sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {return a[1] < b[1];});
        solve();
    };
};
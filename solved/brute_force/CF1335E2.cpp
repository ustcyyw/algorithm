/**
 * @Time : 2024/6/23-3:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1335E2 暴力枚举 前后缀分解
 */
 /*
  * 枚举作为两边部分的x的数以及其相应x部分的边界
  * 然后枚举中间y部分的数 根据x部分的边界确定y部分最大元素个数
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, ans;
vector<int> arr[201];

void cal(vector<int>& aux) {
    for(int i = 0, j = aux.size() - 1; i < j; i++, j--) {
        int lo = aux[i], hi = aux[j], base = i + 1 + aux.size() - j;
        for(int k = 1; k <= 200; k++) {
            if(arr[k].empty()) continue;
            auto it1 = upper_bound(arr[k].begin(), arr[k].end(), lo);
            if(it1 == arr[k].end()) continue;
            auto it2 = lower_bound(arr[k].begin(), arr[k].end(), hi);
            if(it2 == arr[k].begin()) continue;
            int l = it1 - arr[k].begin(), r = --it2 - arr[k].begin();
            ans = max(ans, r - l + 1 + base);
        }
    }
}

void solve() {
    // 枚举作为两边x部分的数字
    for(int i = 1; i <= 200; i++) {
        if(arr[i].empty()) continue;
        ans = max(ans, (int)arr[i].size());
        cal(arr[i]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        memset(arr, {}, sizeof(arr));
        ans = 0;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            arr[num].push_back(i);
        }
        solve();
    }
};
/**
 * @Time : 2024/6/24-10:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1311D 数学 暴力枚举
 */
 /*
  * b和a、c都直接相关 并且看到值域1e4 想到如果枚举b是否有一个上限
  * 假设a = 9999, a <= b <= c
  * b增大意味着c也要增大 b增大到2 * a后再增大绝对无意义
  * 因此保守估计b的枚举范围是 [1,2e4]
  * 枚举b的值 那么a的变化和c的变化 就贪心得找即可
  * a就找b的因子中最接近a的两个数
  * c就找b的倍数中最接近b的两个数
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e4 + 5;
typedef long long ll;
int T, n, a, b, c, a1, b1, c1, t1, t2, t3;
vector<int> arr[N];
int init = []() -> int {
    for(int num = 1; num < N; num++) {
        for(int i = 1; i <= sqrt(num); i++) {
            if(num % i == 0)
                arr[num].push_back(i), arr[num].push_back(num / i);
        }
        sort(arr[num].begin(), arr[num].end());
    }
    return 0;
}();

int cal(int bt) {
    int bc = abs(b - bt);
    t2 = bt;
    auto it = lower_bound(arr[bt].begin(), arr[bt].end(), a);
    int ac = INT_MAX;
    if(it != arr[bt].end()) {
        t1 = *it;
        ac = abs(a - *it);
    }
    if(it != arr[bt].begin() && ac > abs(a - *(--it))) {
        t1 = *it;
        ac = abs(a - *it);
    }
    int cc = c / bt;
    if(abs(c - cc * bt) < abs(c - (cc + 1) * bt)) t3 = cc * bt;
    else t3 = (cc + 1) * bt;
    cc = abs(c - t3);
    return ac + bc + cc;
}

void solve() {
    int ans = INT_MAX;
    for(int bt = 1; bt < N; bt++) {
        int temp = cal(bt);
        if(temp < ans)
            ans = temp, a1 = t1, b1 = t2, c1 = t3;
    }
    cout << ans << "\n";
    cout << a1 << " " << b1 << " " << c1 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> a >> b >> c;
        solve();
    }
};
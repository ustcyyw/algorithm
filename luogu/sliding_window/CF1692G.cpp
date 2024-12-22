/**
 * @Time : 2024/12/21-5:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1692G 1400 滑动窗口
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, k, nums[N];

void solve() {
    int ans = 0;
    for(int i = 1, j = i + 1; j <= n; ) {
        if(j <= n && nums[j] * 2 <= nums[j - 1]) i = j, j++;
        else j++;
        if(j - i == k) ans++, i++;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> k;
        k++;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};
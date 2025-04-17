/**
 * @Time : 2025/4/17-11:03 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, M = 30;
int T, n, nums[N], cnt0[32], cnt1[32];

ll cal(int num) {
    ll sum = 0;
    for(int j = 0; j < 32; j++) {
        ll temp = 1 << j;
        if(temp & num) sum += temp * cnt0[j];
        else sum += temp * cnt1[j];
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        memset(cnt0, 0, sizeof(cnt0)), memset(cnt1, 0, sizeof(cnt1));
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            for(int j = 0; j < 32; j++) {
                if((1 << j) & nums[i]) cnt1[j]++;
                else cnt0[j]++;
            }
        }
        ll ans = 0;
        for(int i = 1; i <= n; i++)
            ans = max(ans, cal(nums[i]));
        cout << ans << "\n";
    }
}
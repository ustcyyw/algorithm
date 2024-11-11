/**
 * @Time : 2024/6/20-10:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1328F
 */
 /*
  * 最终相同的k个数一定是原本数组中就有的数
  * 这题的限制是只能操作最小或者最大的数 那么要将a变为b
  * a > b的情况下，要将所有大于b的数都变为b+1，然后选其中一个-1变为b
  * a < b的情况下，要将所有小于b的数都变为b-1，然后选其中一个+1变为b
  * 因此在枚举最终数值num时，要考虑将小于它/大于它的数统统变为num-1/num+1
  * 可以借鉴中位数贪心的思路 前后缀分解预处理
  *
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, T = 1e6;
typedef long long ll;
int n, k;
map<int, int> mp;
vector<vector<int>> nums;

void solve() {
    int lCnt[N] = {0}, rCnt[N] = {0};
    ll lSum[N] = {0}, pre[N] = {0}, rSum[N] = {0}, suf[N] = {0};
    for(int i = 1; i <= n; i++) {
        ll num = nums[i][0], c = nums[i][1];
        lSum[i] = lSum[i - 1] + num * c;
        lCnt[i] = lCnt[i - 1] + c;
        pre[i] = (num - 1) * lCnt[i - 1] - lSum[i - 1];
    }
    ll ans = LONG_LONG_MAX;
    for(int i = n; i >= 1; i--) {
        ll num = nums[i][0], c = nums[i][1];
        rSum[i] = rSum[i + 1] + num * c;
        rCnt[i] = rCnt[i + 1] + c;
        suf[i] = rSum[i + 1] - (num + 1) * rCnt[i + 1];
        if(c >= k) ans = 0;
        else {
            ll need = k - c; // 还需要改变为num的数
            if(lCnt[i - 1] >= need) ans = min(ans, pre[i] + need);
            if(rCnt[i + 1] >= need) ans = min(ans, suf[i] + need);
            ans = min(ans, pre[i] + suf[i] + need);
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        mp[num]++;
    }
    nums.push_back({0, 0});
    for(auto& p : mp) {
        nums.push_back({p.first, p.second});
    }
    n = nums.size() - 1;
    solve();
};
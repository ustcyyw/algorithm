/**
 * @Time : 2024/6/26-10:47 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1986E 数学 + 贪心
 */
 /*
  * 注意到操作前后两个数同余 也就是说要能配对相等的两个数 一定是同余的 先进行分组
  * 然后组内思考怎么安排
  * 1.偶数个数 直接贪心 肯定是从大到小两两配对
  * 2.奇数个数 有一个数放在中心位置 其它数两两配对 但是放谁到中间呢？动态规划
  * 并且注意 奇数个元素的组 只能出现一组
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 5e5 + 5;
typedef long long ll;
int T, n, k;
map<int, vector<int>> mp;

ll cal1(vector<int>& arr) {
    ll ans = 0;
    for(int i = 0; i < arr.size(); i += 2)
        ans += (arr[i + 1] - arr[i]) / k;
    return ans;
}

ll cal2(vector<int>& nums) {
    int m = nums.size();
    vector<ll> dp0(m + 1, 0ll), dp1(m + 1, 0ll);
    for(int i = 1; i <= m; i++) {
        if(i % 2 == 0) dp0[i] = dp0[i - 2] + (nums[i - 1] - nums[i - 2]) / k;
        else {
            dp1[i] = dp0[i-1];
            if(i - 3 >= 0) dp1[i] = min(dp1[i], dp0[i - 3] + (nums[i - 1] - nums[i - 3]) / k);
            if(i - 2 >= 0) dp1[i] = min(dp1[i], dp1[i - 2] + (nums[i - 1] - nums[i - 2]) / k);
        }
    }
    return dp1[m];
}

ll solve() {
    ll cnt = 0, ans = 0;
    for(auto& p : mp) {
        sort(p.second.begin(), p.second.end());
        if(p.second.size() % 2 == 1) {
            cnt++;
            ans += cal2(p.second);
        } else ans += cal1(p.second);
        if(cnt > 1) return -1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        mp = {};
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            mp[num % k].push_back(num);
        }
        cout << solve() << "\n";
    }
};
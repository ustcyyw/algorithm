/**
 * @Time : 2024/12/18-11:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1352E 1500 前缀和 暴力枚举
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, nums[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        map<int, int> mp = {{0, 0}};
        unordered_set<int> st;
        for(int i = 1, sum = 0; i <= n; i++) {
            cin >> nums[i];
            sum += nums[i];
            for(auto& [val, idx] : mp) {
                if(i - idx >= 2 && sum - val <= n && sum - val >= 0)
                    st.insert(sum - val);
            }
            if(!mp.count(sum)) mp[sum] = i;
        }
        int cnt = 0;
        for(int i = 1; i <= n; i++)
            if(st.count(nums[i])) cnt++;
        cout << cnt << "\n";
    }
};
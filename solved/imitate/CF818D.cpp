/**
 * @Time : 2025/3/2-5:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF818D 1700 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, M = 1e6 + 5, mod = 1e9 + 7;
ll T, n, a, nums[N], cnt[M];

int solve() {
    set<int> st;
    for(int i = 1; i <= n; i++) {
        if(nums[i] == a) break;
        st.insert(nums[i]);
    }
    for(int i = 1, j = 0, cntA = 0; i <= n && !st.empty(); i = j + 1) {
        j = i;
        while(j <= n && nums[j] != a) {
            cnt[nums[j]]++;
            j++;
        }
        if(j <= n) cntA++;
        set<int> temp;
        for(int num : st) {
            if(cnt[num] < cntA)
                temp.insert(num);
        }
        for(int num : temp)
            st.erase(num);
    }
    return st.empty() ? -1 : *st.begin();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> a;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    cout << solve();
}
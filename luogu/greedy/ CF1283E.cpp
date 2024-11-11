/**
 * @Time : 2024/6/18-1:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1283E 贪心
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, nums[N], marked1[N], marked2[N];

// 找最小值
int solve1() {
    for(int i = 1; i <= n; i++) {
        if(nums[i] == 0 || marked1[i] || marked1[i - 1]) continue;
        marked1[i + 1] = 1;
    }
    return accumulate(marked1, marked1 + n + 2, 0);
}

int solve2() {
    for(int i = n; i >= 1; i--) {
        if(nums[i] == 0) continue;
        if(!marked2[i + 1]) nums[i]--, marked2[i + 1] = 1;
        if(nums[i] > 0 && !marked2[i]) nums[i]--, marked2[i] = 1;
        if(nums[i] > 0 && !marked2[i - 1]) nums[i]--, marked2[i - 1] = 1;
    }
    return accumulate(marked2, marked2 + n + 2, 0);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++){
        cin >> num;
        nums[num]++;
    }
    cout << solve1() << " " << solve2();
};
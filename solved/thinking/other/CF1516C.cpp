/**
 * @Time : 2024/1/17-3:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 如果原数组和为奇数 不用删除任何数
 * 如果原数组和为偶数 用0-1背包检查是否可以取到和为 sum / 2 的子序列 如果不可以，则不用删除任何数
 *
 * 上述情况都不满足 说明可以分成两个和相同的子序列 都需要删除数
 * 如果存在一个奇数 删除该奇数 数组和就变为奇数了
 * arr = s1 + s2
 * 如果不存在奇数 原数组 arr = s + t
 * arr = 2 * arr1 = 2 * s1 + 2 * t1  ->  arr1 = s1 + t1
 * 因此抽取出2后 arr1是否可以分出两个相等子序列 与 arr是否可以分出两个相等子序列 等价
 * arr1中如果存在一个奇数 就可以将其删除 如果还是没有奇数 继续上述过程
 * 最终一定会有一个数先变为奇数 就删除那个数即可
 * 第一个变为奇数的数 就是二进制中最低位1最小的数（每次抽出2 相当于所有数右移1位）
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 105, M = 2e3 + 5;
int n, arr[N], cnt[M], sum;

bool check() {
    int half = sum / 2;
    vector<vector<bool>> dp(n + 1, vector(sum / 2 + 1, false));
    dp[0][0] = true;
    for(int i = 1; i <= n; i++) {
        dp[i][0] = true;
        for(int j = 1; j <= half; j++) {
            dp[i][j] = dp[i - 1][j];
            if(j - arr[i] >= 0) dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i]];
        }
    }
    return !dp[n][half];
}

int low_bit(int num) {
    for(int i = 0; i < 20; i++)
        if((1 << i) & num) return i;
    return 20;
}

void solve() {
    if(sum % 2 == 1 || check()) {
        cout << 0 << endl;
        return;
    }
    cout << 1 << endl;
    int index = -1, lb = 21;
    for(int i = 1; i <= n; i++) {
        int t = low_bit(arr[i]);
        if(t < lb) lb = t, index = i;
    }
    cout << index << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    memset(cnt, 0, sizeof(cnt));
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
        sum += arr[i], cnt[arr[i]]++;
    }
    solve();
}
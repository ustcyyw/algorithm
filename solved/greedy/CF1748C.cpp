/**
 * @Time : 2024/2/1-3:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * nums[i] = 0 可以调整nums[i] 影响就是从sum[i, n]都加上一个数（可正可负）
 * 而下一个0是nums[j]，nums[j]又可以进行调整 可以让sum[j, n]都加上一个数
 * 也就是说nums[i]调整 影响的是 sum[i, j - 1]（或者不存在nums[j] = 0的情况，影响sum[i, n]）
 * 要让前缀和的0最多，就找到sum[i, j - 1]上最多的数字v，将nums[i]调整为-v即可得到最多的前缀和0
 * 双指针分段处理即可。
 *
 * 但是要注意 在第一个0之前的部分 需要统计天然形成的为0的前缀和
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
long long T, n, nums[N], sum[N];

void solve() {
    int cnt = 1, res = 0, i = 1;
    map<long long, int> map;
    // 找到第一个0 然后开始统计 在第一个0之前的前缀和都不能改变
    while(i <= n && nums[i] != 0)
        res += sum[i++] == 0;
    while(i <= n) {
        cnt = 1, map.clear();
        map[sum[i]] = 1;
        int j = i + 1;
        while(j <= n && nums[j] != 0) {
            map[sum[j]]++;
            cnt = max(cnt, map[sum[j]]);
            j++;
        }
        res += cnt;
        i = j;
    }
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        sum[0] = 0;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            sum[i] = sum[i - 1] + nums[i];
        }
        solve();
    }
};
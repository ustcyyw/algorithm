/**
 * @Time : 2025/11/7-10:13
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3646 2445 思维 暴力枚举 状态压缩 回溯 打表
 */
 /*
  * 1 2 3 4 5 6 7 8 9
  * 一共9个数字 总共512种选数可能 并且奇数只能出现一次
  * 长度超过15也不用管，因为数据范围最大是1e5
  * 15位的数可以用9+6的组合来构建一个最大的回文15位数
  * 而超过这个最大的回文15位数，可以用 2+6+8的数字组合构建2666888888886662，这是最小的16位回文数
  * 因为诸多限制条件 对于每一种数字组合 实际能构建的数并不多
  * 所以可以暴力枚举所有数字组合 然后对于每个数字组合都用回溯计算所有满足条件的回文数
  * 直接打表
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;
int cnt[10];
vector<ll> arr;

int check(int s) {
    int len = 0, cnt = 0;
    for(int j = 0; j < 9; j++) {
        if(s & (1 << j)) {
            len += j + 1;
            cnt += (j + 1) % 2;
            if(len > 15 || cnt > 1) return -1;
        }
    }
    return len;
}

ll to_num(vector<int>& temp) {
    ll ans = 0;
    for(ll i = temp.size() - 1, base = 1; i >= 0; i--, base *= 10) {
        ans += temp[i] * base;
    }
    return ans;
}

void dfs(int len, int i, vector<int>& temp) {
    if(i > (len - 1) / 2) {
        arr.push_back(to_num(temp));
        return;
    }
    for(int j = 1; j <= 9; j++) {
        if(cnt[j] == 0) continue;
        if(cnt[j] >= 2 || (len % 2 == 1 && i == len / 2)) {
            cnt[j] -= 2, temp[i] = temp[len - 1 - i] = j;
            dfs(len, i + 1, temp);
            cnt[j] += 2;
        }
    }
}

int init = []() -> int {
    for(int i = 1; i <= (1 << 9) - 1; i++) {
        int len = check(i);
        if(len == -1) continue;
        for(int j = 0; j < 9; j++) {
            if(i & (1 << j)) cnt[j + 1] = j + 1;
            else cnt[j + 1] = 0;
        }
        vector<int> temp(len, 0);
        dfs(len, 0, temp);
    }
    arr.push_back(2666888888886662);
    sort(arr.begin(), arr.end());
    return 0;
}();

class Solution {
public:
    long long specialPalindrome(long long n) {
        return *upper_bound(arr.begin(), arr.end(), n);
    }
};
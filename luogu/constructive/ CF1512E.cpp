/**
 * @Time : 2024/7/9-9:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1512E 构造 数学
 */
/*
 * 相当于用 m = r - l + 1 个数 凑够s
 * 最小是 m * (m + 1) / 2, 最大是 (n - m + 1 + n) / 2 * m
 * 不在这个范围 肯定凑不齐
 *
 * 从最小值的组合 1,2,3 ...开始考虑
 * 计算这个组合每个数都加1，要加多少次m能接近但不超过s
 * 还缺多少就从后面的数再加1，知道刚好和为s
 * [l,r]外的数就从还没安排的数中依次排即可
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, l, r, s, nums[505], picked[505];

bool solve() {
    int m = r - l + 1, minV = m * (m + 1) / 2, maxV = (n - m + 1 + n) * m / 2;
    if(s < minV || s > maxV) return false;
    int c = 0;
    while(minV + c * m < s) // c次+2刚好超过 那么c-1次就刚好没超过
        c++;
    for(int i = r, base = c + m, need = s - (minV + (c - 1) * m); i >= l; i--) {
        nums[i] = need > 0 ? base: base - 1;
        picked[nums[i]] = 1;
        need--, base--;
    }
    for(int i = 1, j = 1; i <= n; i++) {
        if(nums[i] != 0) continue;
        while(j <= n && picked[j]) j++;
        nums[i] = j, picked[j] = 1;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> l >> r >> s;
        memset(nums, 0, sizeof(nums)), memset(picked, 0, sizeof(picked));;
        if(!solve()) cout << "-1\n";
        else {
            for(int i = 1; i <= n; i++)
                cout << nums[i] << " ";
            cout << "\n";
        }
    }
};
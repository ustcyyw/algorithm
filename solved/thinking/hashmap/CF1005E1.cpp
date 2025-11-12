/**
 * @Time : 2024/3/15-3:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 奇数长度的数组中 比k小的数的数量 = 比k大的数的数量
 * 偶数长度的数组中 比k小的数的数量 = 比k大的数的数量 - 1
 * 记pos表示比k大的数的数量，neg表示...
 * 在包含有k的数组中 要求 pos - neg = 1 或者 0
 * 借鉴前缀和的思路 通过相减来确定子区间上的数量
 * 当前位置前缀和为p2,n2,前面位置为p1,n1
 * p2 - n2 - (p1 - n1) = p2 - p1 - (n2 - n1)
 * p2 - p1就是子区间上k大的数的数量，n2 - n1就是子区间上k小的数的数量
 * 所以要求 p2 - n2 - (p1 - n1) = 1 or 0。记diff = pi - ni
 * 上式变为 diff2 - diff1 = 1 or 0，可以使用hashmap计数
 * 不过要注意 计算答案时要保证子数组包括了k这个数。因此用hashmap计数，也应该在遇到k之前。
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
ll T, n, m, k;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    unordered_map<int, int> map;
    map[0] = 1;
    ll res = 0, flag = 0, neg = 0, pos = 0;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        if(num < k) neg++;
        else if(num > k) pos++;
        if(num == k) flag = 1;
        int diff = pos - neg;
        if(flag) res += map[diff - 1] + map[diff];
        if(!flag) map[diff]++;
    }
    cout << res << "\n";
};
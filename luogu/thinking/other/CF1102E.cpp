/**
 * @Time : 2024/4/26-4:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1102E
 */
/*
 * b是非递减的 b[i + 1] = b[i] or b[i] + 1
 * 如果a[i] = a[j]要求b[i] = b[j], 那么b[i, j]上所有数都相等
 * 对于a中每一个出现的数num，找到其最先出现的位置l = first[num]，最后出现的位置r = last[num]
 * 那么区间[l, r]上所有数都相等
 * 可能会出现区间有重合的情况（example1） 那么这些区间合并成的大区间内所有数都相等
 * 考虑每个位置b如何选择 在不要求相等的情况下有2种选择
 * 因此将相等区间等价为一个位置后，本题就是要求一个有多少个位置cnt
 * 答案就是 2 ^ (cnt - 1)。减少1是因为规定了b0 = 0
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 5, mod = 998244353;
int n;
map<int, int> first, last;

ll qp(ll a, ll b) {
    ll res = 1;
    while (b != 0){
        if((b & 1) == 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void solve() {
    vector<vector<int>> arr;
    for(auto& p : first) {
        int num = p.first;
        if(first[num] != last[num])
            arr.push_back({first[num], last[num]});
    }
    sort(arr.begin(), arr.end());
    int cnt = 0, pre = 0, m = arr.size();
    for(int i = 0; i < m; ) {
        cnt += arr[i][0] - pre - 1; // 当前区间左端点与上一个区间右端点直接的数字 都不必相等
        int j = i + 1, hi = arr[i][1];
        while(j < m && arr[j][0] <= hi) {
            hi = max(hi, arr[j][1]);
            j++;
        }
        i = j, pre = hi;
        cnt++; // 这一个区间所有数都相等 等价于一个数
    }
    cnt += n - pre;
    cout << qp(2, cnt - 1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        if(!first.count(num)) first[num] = i;
        last[num] = i;
    }
    solve();
};
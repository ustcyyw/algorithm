/**
 * @Time : 2024/6/2-12:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1868B1 思维 位运算
 */
/*
 * 每个人的糖果数量相同 都是val = sum / n
 *
 * 某个人要给出去的或者缺少的就是 v = nums[i] - val
 * v > 0 那么他给出的值 gv > v
 * 这样他才能从别人那里获得糖果 并且给出去后他需要收的糖果数量为 gv - v
 * gv, gv - k都需要是2的幂次
 *
 * v < 0 那么他接收的值 rv > abs(v)
 * 这样他才能接受别人糖果后再给别人 并且接收糖果后他需要给出的数量为 rv - abs(v)
 * rv, rv - abs(v)都需要是2的幂次
 *
 * 要让所有人接收糖果的情况和送出糖果的情况相同才能完成交换
 * 如果 v = 0 可以直接忽略，因为可以让他仅仅做一个传递作用
 * 比人给他多少 他再送给另外一个需要的人多少即可。
 *
 * 给定v 找一个值ov > v， ov是2的幂次，并且ov - v是2的幂
 * 那么一定是找v的最高位的1，记为d位，ov = 1 << (d + 1)
 * 然后查看 ov - v 是否2的幂次
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, m, nums[N];

// 给定v 找一个值ov > v， ov是2的幂次，并且ov - v是2的幂
ll for_other(ll v) {
    for(int i = 33; i >= 0; i--) {
        if((1ll << i) & v) {
            return 1ll << (i + 1);
        }
    }
    return -1;
}

bool solve() {
    ll sum = accumulate(nums, nums + n + 1, 0ll);
    if(sum % n != 0) return false;
    ll av = sum / n;
    vector<ll> given, receive;
    for(int i = 1; i <= n; i++) {
        ll v = nums[i] - av;
        if(v == 0) continue;
        ll ov = for_other(abs(v));
        if(__builtin_popcount(ov - abs(v)) != 1) return false;
        if(v > 0) { // ov是要给出去的 那么需要再接收 ov - abs(v)
            given.push_back(ov);
            receive.push_back(ov - abs(v));
        }
        else { // ov是接收到的 那么要给出去 ov - abs(v)
            receive.push_back(ov);
            given.push_back(ov - abs(v));
        }
    }
    sort(given.begin(), given.end()), sort(receive.begin(), receive.end());
    return given == receive;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};
/**
 * @Time : 2024/3/7-1:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 70以内的质数只有19个
 * 乘积是否是平方数 只取决于质因子是否出现了偶数次 因此可以用状态表示奇偶性
 * 由于元素的值 <= 70 可以先将相同值的元素合并奇数
 * 因为选择同一个值奇数次 1次、3次、等等 乘起来之后质因子出现次数的奇偶性都一致。选择偶数次也一样
 * 如果前面的状态是pre，当前值对应的状态是s
 * 将当前值选择奇数次 与前面的数相乘 相当于状态变为 pre ^ s
 * 将当前值选择偶数次 与前面的数相乘 状态不变 仍为pre
 *
 * 特别注意1 每个1都是可选可不选的。以及最后要扣除空序列
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 1e5 + 5;
int n, T, cnt[75], primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};

int get_status(int num) {
    int i = 0, s = 0;
    while(num >= primes[i]) {
        if(num % primes[i] == 0) num /= primes[i], s ^= 1 << i;
        else i++;
    }
    return s;
}

ll qp(ll a, ll b) {
    ll res = 1;
    while (b != 0){
        if((b & 1) == 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    unordered_map<int, ll> map, temp;
    map[0] = 1; // 表示空序列有1个
    for(int i = 2; i <= 70; i++) {
        if(cnt[i] == 0) continue;
        temp.clear();
        int s = get_status(i);
        // n个数中选取奇数个的和 c(n,1) + c(n,3) +...+c(n,2k-1) = 2 ^ (n - 1)
        ll odd = qp(2, cnt[i] - 1), even = (odd - 1 + MOD) % MOD;
        for(auto& p : map) {
            int pre = p.first, t = pre ^ s;
            temp[t] = (temp[t] + map[pre] * odd % MOD) % MOD;
            temp[pre] = (temp[pre] + map[pre] * even % MOD) % MOD;
        }
        for(auto& p : map)
            temp[p.first] = (temp[p.first] + map[p.first]) % MOD;
        swap(map, temp);
    }
    ll ans = (map[0] * qp(2, cnt[1]) % MOD + MOD - 1) % MOD;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    memset(cnt, 0, sizeof(cnt));
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        cnt[num]++;
    }
    solve();
};
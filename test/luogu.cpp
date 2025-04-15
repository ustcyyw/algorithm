/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
 /*
  * 根据伪代码 k会在只会在其因子处变化 因此一个k的值 涵盖了一个区间
  * 只要找k在什么位置变化即可，并且k最多可以变化 logk次 （k就是2的幂的情况）
  * 假设现在枚举到idx, 找下一个位置nxt使得有一个a[nxt]是k的因子 那么[idx, nxt - 1]上 k维持不变
  * 好在k的范围1e5其因子个数最多100个左右 直接暴力枚举所有因子 找离idx最近的哪个即可
  * 找最近可以预处理，将a[i]按数值归类，然后进行二分查找即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 15, M = 30;
ll T, n, q, a[N], k, l, r;
map<int, vector<int>> pos;

const int max_num = 100001;
vector<int> divisors[max_num];
int init = []() {
    for (int i = 1; i < max_num; ++i)
        for (int j = i; j < max_num; j += i)
            divisors[j].push_back(i);
    return 0;
}();

int find(int num, int idx) {
    if(!pos.count(num) || pos[num].empty()) return INT_MAX;
    auto it = lower_bound(pos[num].begin(), pos[num].end(), idx);
    return it == pos[num].end() ? INT_MAX : *it;
}

void solve() {
    ll ans = 0;
    for(int i = l; i <= r; ) {
        int j = r + 1;
        for(int num : divisors[k])
            j = min(j, find(num, i));
        ans += k * (j - i);
        i = j;
        if(j != r + 1) k /= a[j];
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> q;
        pos = {};
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }
        for(int i = 1; i <= q; i++) {
            cin >> k >> l >> r;
            solve();
        }
    }
}
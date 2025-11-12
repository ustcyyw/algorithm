/**
 * @Time : 2025/11/11-20:21
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2148G 1900 数学 数论 思维
 */
 /*
  * gcd(1,k) = d1 说明前面这些数都含因子d1
  * gcd(1,k+1) >= gcd(1,k) = d1 要找 gcd(1,k+1) > gcd(1,k) 去掉等号
  * 那么nums[k+1]中不含有因子d1，否则gcd(1,k+1) = d1
  * 要找最大的k使得等式成立，就要需要找有公共因子d的数最多有多少个
  * 并且得保证并非所有数都含该因子，得让一个数使得gcd(d, num) < d
  *
  * 随着可以自由排列的数月来越多 最大k是非递减的
  * 因为你完全可以把原本那个排列保持不变，新增加的数就添加在最后 k至少是不变的
  * 所以随着数越来越多，我们只用持续更新答案
  * 1. 当前数cur拥有的因子d，使得d因子对应的数增加1，但是d不能是当前所有数公共因子
  * 2. 因为上一个情况的附加条件，导致上一数pre的某些因子没有更新答案，但是当前数并没有那个因子，那个答案有效了
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, mp[N], nums[N], ans;
vector<int> divide[N];

int init = []() -> int {
    for(int i = 2; i < N; i++) {
        for(int j = i; j < N; j += i)
            divide[j].push_back(i);
    }
    return 0;
}();

void solve(int cur) {
    for(int d : divide[nums[cur]]) {
        mp[d]++;
        if(mp[d] != cur) ans = max(ans, mp[d]);
    }
    if(cur > 1) {
        for(int d : divide[nums[cur - 1]])
            if(mp[d] != cur) ans = max(ans, mp[d]);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        ans = 0;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            solve(i);
            cout << ans << " ";
        }
        for(int i = 1; i <= n; i++) {
            for(int d : divide[nums[i]]) {
                mp[d] = 0;
            }
        }
        cout << "\n";
    }
}
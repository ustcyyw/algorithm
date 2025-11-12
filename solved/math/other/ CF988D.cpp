/**
 * @Time : 2024/4/10-2:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 容易发现 这样的集合最多3个数
  * 相邻的两个相差 2 ^ k, 两端的数相差2 ^ (k + 1)次
  * 因此枚举每一个数作为第一个数，然后枚举第二个数和它相差 2 ^ k
  * 看看是否存在第二个 第三个数即可
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll N = 2e5 + 5, T = 2e9 + 1;
int n, nums[N];
set<ll> st;

pair<int, int> cal(ll num) {
    int len = 1, add = -1;
    for(ll t = 1; t < INT_MAX; t *= 2) {
        if(st.count(num + t)) {
            if(st.count(num + 2 * t)) return {3, t};
            else len = 2, add = t;
        }
    }
    return {len, add};
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        st.insert(num);
    }
    int base = 0, cnt = 0, add = -1;
    for(ll num : st) {
        pair<int, int> p = cal(num);
        if(p.first > cnt) cnt = p.first, base = num, add = p.second;
        if(cnt == 3) break;
    }
    cout << cnt << "\n";
    for(int i = 0; i < cnt; i++)
        cout << (base + i * add) << " ";
};
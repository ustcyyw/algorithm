/**
 * @Time : 2024/3/25-9:16 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 大的方向 比较明显是要用二分的 重点是如何check
  * g(t, m)：t中的字母 每一个都连续重复m次
  * 要让n个s找出这样的子序列，m个相同字母为一组地去找 计算需要使用cnt个s
  * 既然是m个相同字母为一组地查找，就按字母将s中的下标分组。
  * 每个组的元素个数sz就表示一个s可以找到多少个该字母
  * 其余看注释
  */
#include<bits/stdc++.h>

typedef unsigned long long ll;
using namespace std;
const int N = 2e5 + 5, MOD = 1e9 + 7;
ll n, ns, nt;
vector<vector<int>> aux;
string s, t;

bool check(ll m) {
    ll cnt = 1, j = 0; // j表示s当前可用的开始下标, cnt初始化为1表示 暂时表示当前要使用的这个s
    for(int i = 0; i < nt; i++) {
        vector<int>& arr = aux[t[i] - 'a'];
        if(arr.empty()) return false; // s中压根不存在t所需的字母
        // idx 当前t中所需字符在s中的第一个下标 对应的索引
        ll idx = lower_bound(arr.begin(), arr.end(), j) - arr.begin();
        ll need = m, sz = arr.size();
        // 还需要的比在s[arr[idx], st-1]上可用的多 为了方便处理将子串的这部分单独计算
        if(need > sz - idx) { // 不能取等号 因为刚好够用的话 不需要使用新的s
            need -= sz - idx; // 剩余还需要
            idx = 0, cnt++; // idx移动到0 使用一个新的s 所以cnt++
        }
        // 这个可以举例计算 如果need == sz，刚好使用完上一个if语句中预先计数的s，因此cnt += 0
        // 如果need == 2 * z, 刚好使用完上一个if语句中预先计数的后，再使用一个 因此 cnt += 1
        // 所以对于除尽的状态，就是need / sz - 1。类似考虑不可以除尽的状态
        if(need >= sz) cnt += need % sz == 0 ? need / sz - 1 : need / sz;
        idx = (idx + need) % sz; // 使用了相应的字母 idx也要相应移动
        j = idx > 0 ? arr[idx - 1] + 1 : arr[sz - 1] + 1; // s后续可用的开始下标要更新
    }
    if(j == 0) cnt--;
    return cnt <= n;
}

void solve() {
    ll lo = 0, hi = (ll)1e17;
    while(lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s >> t;
    ns = s.size(), nt = t.size();
    aux.assign(26, {});
    for(int i = 0; i < ns; i++)
        aux[s[i] - 'a'].push_back(i);
    solve();
};
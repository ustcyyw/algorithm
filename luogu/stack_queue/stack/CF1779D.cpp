/**
 * @Time : 2024/6/3-8:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1779D 单调栈
 */
 /*
  * [l, r] 上 min(ai, x)
  * 如果 x >= ai 没变化
  * bi <= x < ai 一起改变了也没事 看后续能不能继续将ai变为bi
  * 如果 x < bi 就不能进行改变 否则变了以后 ai < bi了 再也变不回去了
  *
  * 因此给定x的情况下
  * 如果要使用 那肯定是要先找b中x在什么位置 假设就在j位置 b[j] = x
  * 那么j位置附近 比x小的数 不受x的影响（后面可以继续改变）
  * 但是比x大的数 一旦变为x 就再也变不回去了 因此操作的范围就是j附近所有小于等于它的数
  * 于是就确定了操作范围
  *
  * 不使用的情况则是 b没有x或者b中为x的数都已经被操作过了
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, MV = 1e9;
typedef long long ll;
int T, n, m, a[N], b[N], xs[N], pre[N];
map<int, vector<int>> mp;

void pre_more() {
    stack<int> stack;
    for(int i = 1; i <= n; i++) {
        while(!stack.empty() && b[stack.top()] <= b[i])
            stack.pop();
        pre[i] = stack.empty() ? 0 : stack.top();
        stack.push(i);
    }
}

bool check() {
    for(int i = 1; i <= n; i++)
        if(a[i] != b[i]) return false;
    return true;
}

void solve() {
    pre_more();
    for(int i = 1; i <= m; i++) {
        int x = xs[i];
        if(!mp.count(x) || mp[x].empty()) continue;
        vector<int>& arr = mp[x];
        int j = arr.back(), lo = pre[j];
        while(!arr.empty() && arr.back() >= lo) {
            a[arr.back()] = min(x, a[arr.back()]);
            arr.pop_back(); // 操作过的位置就不再保留
        }
    }
    cout << (check() ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        mp = {};
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++) {
            cin >> b[i];
            mp[b[i]].push_back(i);
        }
        cin >> m;
        for(int i = 1; i <= m; i++)
            cin >> xs[i];
        solve();
    }
};
/**
 * @Time : 2025/4/25-3:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2106G1 2220 思维 数学 二分 交互题
 */
/*
  * 特别注意每个结点都连接到1结点 1是特殊的 先来讨论它
  * 1. 假设根结点是1，那么询问 q1(1)，结果就是1的值
  * 2. 假设根结点不是1，那么询问 q1(1)，结果就是1和根结点值之和
  * 因为每个结点值都是奇数 所以两次询问的奇偶性不同 通过这个判断根是否为1
  * 对于根是1的情况 只需要再询问 q1(i) for i in [2, n]
  * 这些询问的答案都是 1和i的结点值之和 再减去1的值 就得到答案
  *
  * 现在讨论根结点不是1，那么根结点是[2,n]
  * 除了q1(root) = v(root)外，都有 q1(i) = v(root) + v(1) + v(i)
  * 如果询问q1(lo,hi)，如果root不在[lo,hi]，那么询问的结果是 cnt * (v(root) + v(1)) + sum{v(i)}
  * 但是root在[lo,hi]，询问的结果就是 (cnt - 1) * (v(root) + v(1)) + sum{v(i)
  * 再考虑 q2(1) 操作
  * 在q2(1)前后，q1(lo,hi)的值 变化的部分是 cnt * v(1) 或者 (cnt - 1) * v(1)
  * v(1)的变化 会使这差值为2，因此只需要计算q1(lo,hi)前后的变化，就能判断根结点是否在[lo,hi]
  * 使用二分查找root
  *
  * 找到root后
  * q1(1)_1 = v(root) + v(1)
  * q2(1)
  * q1(1)_2 = v(root) - v(1) (这里v(1)代表一开始的值)
  * 于是就能求v(root)和变化后的1的值
  * 而非1和非root结点 则根据 q1(i) = v(root) + v(1) + v(i)
  * v(i) = q1(i) - (v(root) + v(1))
  *
  * 因为计算限制，所以在执行q2(1)操作前，先将所有q1(i)计算一遍，记录前缀和
  * 执行q2(1)后，只执行一次q1(1)来求root的值，然后使用二分来确定root是哪个结点
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e3 + 5, mod = 998244353;
int T, n, k, ans[N], sum[N];

int get_val(string& suf) {
    int val;
    cout << "? 1 " << suf << endl;
    cin >> val;
    return val;
}

int get_one_val(int node) {
    string temp = "1 " + to_string(node);
    return get_val(temp);
}

// 1就是根结点的情况
void solve1(int one) {
    ans[1] = one;
    for(int i = 2, val; i <= n; i++) {
        val = get_one_val(i);
        ans[i] = val - one;
    }
}

int find_root() {
    int lo = 2, hi = n;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        int cnt = mid - 2 + 1, v1 = sum[mid] - sum[1];
        string temp = to_string(cnt);
        for(int i = 2; i <= mid; i++)
            temp.append(" " + to_string(i));
        int v2 = get_val(temp), diff = abs(v2 - v1);
        if(diff != cnt * 2) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

void solve2() {
    for(int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + get_one_val(i);
    int base1 = sum[1];
    cout << "? 2 1" << endl;
    int base2 = get_one_val(1);
    int root_val = (base1 + base2) / 2, root = find_root();
    ans[1] = base2 - root_val, ans[root] = root_val;
    for(int i = 2; i <= n; i++) {
        if(i == root) continue;
        ans[i] = sum[i] - sum[i - 1] - base1;
    }
}

void solve() {
    int val = get_one_val(1); // 查询root是否为结点1
    if(abs(val) % 2 == 1) solve1(val);
    else solve2();
    cout << "! ";
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1, a, b; i < n; i++)
            cin >> a >> b;
        solve();
    }
}
/**
 * @Time : 2025/11/13-23:17
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2121H 2300 思维题 动态规划 二分
 */
/*
  * 考虑lis类似的做法 用t[i]表示长度为i的序列 末尾元素最小值为t[i], t是一个单调不减的序列
  * 1. r >= t[m], 当前数可以扩展序列总长度 向序列中插入 max(l, t[m])
  *
  * 考虑当前数可以放在某些序列t[i]的末尾，那么最基本的要求是 r >= t[i]
  * 要能放在t[i]的后面，当前数最小要取t[i], 当前数最小只能是l
  * 所以t[i+1]可能会被更新为 max(t[i],l)
  *
  * 2. l >= t[i], t[i+1] 可能替换为l，那么还要求t[i+1] > l，不然没有改动的必要
  * 此时l >= t[i], 也保证了大前提 r >= l >= t[i],
  * 因此条件直接简化为 t[i] <= l < t[i+1] 满足这个条件的i有且仅有1个
  * 找比l大的第一个元素 然后修改其为l
  *
  * 3. l < t[i], t[i+1] 可能替换为t[i], 此时的限制条件是 l < t[i] <= r
  * 找到最小的i1满足 t[i1] > l, 然后找到最大的i2, 满足t[i2] <= r
  * 对于t[i1,i2]上的所值，都向后覆盖一个值
  * 在有序集合中 等价于 多加一个t[i1], 然后将t[i2+1]删除
  *
  * 以上这些操作 都需要快速定位 就是二分查找 并且是有重复元素的 所以使用multiset
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, l, r, idx, tail[N];
multiset<int> st;

// 暴力对拍可以用
//void solve1() {
//    if(r >= tail[idx]) {
//        int temp = max(l, tail[idx]);
//        tail[++idx] = temp;
//    }
//    for(int j = idx; j >= 1; j--) {
//        int temp = max(tail[j - 1], l);
//        if(temp < tail[j] && r >= tail[j - 1]) tail[j] = temp;
//    }
//    cout << idx << " ";
//}

void solve() {
    int last = *st.rbegin();
    if(r >= last) st.insert(max(l, last));
    // 找最小的i1使得t[i1] > l
    auto it1 = st.upper_bound(l);
    if(it1 != st.end()) {
        st.insert(*it1);
        auto it2 = st.upper_bound(r);
        if(it2 == st.end()) --it2;
        st.erase(it2);
    }
    auto it = st.upper_bound(l);
    if(it != st.end() && *it != l)
        st.erase(it), st.insert(l);
    cout << st.size() << " ";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        idx = 0, st = {};
        for(int i = 1; i <= n; i++) {
            cin >> l >> r;
            solve();
        }
        cout << "\n";
    }
}
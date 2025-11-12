/**
 * @Time : 2024/9/14-3:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1862G 找规律题 模拟
 */
/*
 * 1. 每次数组的加操作 能将排序后相邻两个数的差值减少1
 * 最后剩下一个数的前提条件是 所有数都通过操作变相等了
 * 因此总的操作次数 就是最大差值
 *
 * 2. 数组的加操作 每次都是在元素不同的数组上进行 数组共有n个元素
 * 那么最大数和最小数之差 至少是 n - 1
 * 第一个数假设为a, 最后一个数为a + n - 1
 * 通过加操作 第一个数变为a + n, 最后一个数变为 a + n - 1 + 1 = a + n
 * 因此加操作不会使得最大数的排序变化 依旧是最大数
 *
 * 3.某一个值 不会在消除操作中完全被消除
 * 因此 最大数每次加操作后依旧是最大数 这个值是一直不会被消除的
 *
 * 4. 综上所述 总操作次数为md 最大数在这些操作之中一直都是最大数 每次操作刚好+1
 * 那么最后剩下的数就是 最大数+md 也就是答案
 *
 * 因此只需要维护数组中的数的相对位置 及相邻两个数之间的差值即可
 * 用两个multiset维护
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, q, nums[N];
multiset<int> diffs, st; // 分别是按大小排序后相邻两个位置的数之间的差的集合、数的集合


int cal(int idx, int val) {
    if (n == 1) return val;
    int num = nums[idx];
    st.erase(st.find(num));
    auto it = st.upper_bound(num);
    if (it == st.begin()) diffs.erase(diffs.find(*it - num)); // num是最小值的情况
    else if (it == st.end()) diffs.erase(diffs.find(num - *(--it))); // num是最大值的情况
    else {
        int next = *it, pre = *(--it);
        diffs.erase(diffs.find(next - num));
        diffs.erase(diffs.find(num - pre));
        diffs.insert(next - pre);
    }
    nums[idx] = val, num = val;
    it = st.upper_bound(num);
    if (it == st.begin()) diffs.insert(*it - num); // num是最小值的情况
    else if (it == st.end()) diffs.insert(num - *(--it)); // num是最大值的情况
    else {
        int next = *it, pre = *(--it);
        diffs.insert(next - num);
        diffs.insert(num - pre);
        diffs.erase(diffs.find(next - pre));
    }
    st.insert(val);
    return *st.rbegin() + (diffs.empty() ? 0 : *diffs.rbegin());
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        diffs = {}, st = {};
        for (int i = 1; i <= n; i++) {
            cin >> nums[i];
            st.insert(nums[i]);
        }
        auto it1 = st.begin(), it2 = ++st.begin();
        while (it2 != st.end()) {
            diffs.insert(*it2 - *it1);
            it1++, it2++;
        }
        cin >> q;
        for (int i = 1, idx, val; i <= q; i++) {
            cin >> idx >> val;
            cout << cal(idx, val) << " ";
        }
        cout << "\n";
    }
};
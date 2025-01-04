/**
 * @Time : 2025/1/3-9:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2009G1 1900 滑动窗口 数据结构 思维
 */
 /*
  * 连续的子数组中 所有 nums[i] - i 都为定值
  * 所以要找某个区间上最少需要修改几个值 就是找到 nums[i] - i 出现的最大次数
  * 然后用区间长度减去这个最大次数即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k, q, nums[N], ans[N];
map<int, int> cnt;
multiset<int> st;

void add(int num) {
    int cc = ++cnt[num];
    st.insert(cc);
    if(cc > 1) st.erase(st.find(cc - 1));
}

void remove(int num) {
    int cc = --cnt[num];
    if(cc > 0) st.insert(cc);
    st.erase(st.find(cc + 1));
}

void init() {
    for(int lo = 1, hi = 1; hi <= n; hi++) {
        add(nums[hi]);
        if(hi - lo + 1 > k) remove(nums[lo++]);
        ans[hi] = k - *st.rbegin();
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cnt = {}, st = {};
        cin >> n >> k >> q;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            nums[i] -= i;
        }
        init();
        for(int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            cout << ans[r] << "\n";
        }
    }
};
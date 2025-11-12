/**
 * @Time : 2024/12/9-10:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1859D 1800 思维 排序 看答案学习
 */
/*
  * 对于某一区间，点x位于[l,b]都可以移动到b点 [l,b]区间是有价值的区间
  * 反之x位于(b, r]，最远移动到b点是负向作用
  *
  * 对于两个区间 大区间如果不相交 小区间必然也不相交 完全不相互影响
  * 考虑大区间相交的情况 l2 <= r1
  * 如果b1 < l2, 就是[l1,b1]与[l2,b2]不相交的情况
  * 那么在(b1,l2)上的点 没有办法到达b2, 两个大区间实质上也相互不影响
  * 如果b1 >= l2, [l1,b1]与[l2,b2]相交,
  * 那么在[l1, r1]上的点都可以先移动到b1，然后到了[l2,r2]上，最远可以到b2
  *
  * 所以可以将每个区间从最远可移动的角度上等价为[l,b]，然后再找相交区间进行合并
  * 对于任意给定的x，先找比x小的区间左端点 然后取该区间右端点与x的最大值 就是x能移动到的最远位置
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, q;
vector<vector<int>> arr;
map<int, int> mp;

void merge() {
    sort(arr.begin(), arr.end());
    for(int n = arr.size(), i = 0, j; i < n; i = j) {
        j = i + 1;
        int hi = arr[i][1];
        while(j < n && arr[j][0] <= hi) {
            hi = max(hi, arr[j][1]);
            j++;
        }
        mp[arr[i][0]] = hi;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        arr = {}, mp = {};
        for(int i = 0, l, r, a, b; i < n; i++) {
            cin >> l >> r >> a >> b;
            arr.push_back({l, b});
        }
        merge();
        cin >> q;
        for(int i = 1, x; i <= q; i++) {
            cin >> x;
            auto it = mp.upper_bound(x);
            if(it == mp.begin()) cout << x << " ";
            else cout << (max(x, (--it)->second)) << " ";
        }
        cout << "\n";
    };
};
/**
 * @Time : 2024/7/19-7:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 值a[i] <= 1e6 删除值在[l,r]内的数 让a数组非减
  * 对于某个[l,r]
  * [0,l-1], [r + 1, x]这些值上的数没有逆序对的话
  * [0,l-1], [r + 2, x]上这些值 也不会产生逆序对
  *
  * 所以对于某一个l 找到最小的r即可
  * 不同数值的数 位置不能出现交叉
  * [0,l-1]上 一定不能出现位置交叉 [r + 1, x]上也是
  *
  * 将各个值出现的区间处理出来 对值进行双指针
  * 记删除的区间[lo, hi]
  * 首先在lo = 1时，hi最小可取的值 取决于右侧第一个出现交叉的值
  * 随着lo的增大 hi可能会增大 因为左边的数 右边界增大 可能会出现交叉
  * 此时 hi >= lo 并且要保证将存在交叉的数都删除
  *
  * 因为对值进行双指针 要尤其注意那些数组中没出现过的值的处理
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, x, minIdx[N], maxIdx[N];

void solve() {
    ll ans = 0;
    int lo = 1, hi = x;
    for(int suf = n + 1; hi >= 1; hi--) {
        if(maxIdx[hi] == 0) continue;
        if(maxIdx[hi] > suf) break;
        suf = minIdx[hi];
    }
    for(int i = x - 1; i > hi; i--)
        minIdx[i] = min(minIdx[i], minIdx[i + 1]);
    for(int pre = 0; lo <= x; lo++) {
        while(hi < x && (hi < lo || minIdx[hi + 1] < pre))
            hi++;
        ans += x - hi + 1;
        // maxIdx[lo] != 0 才说明lo这个数值出现过 才需要考虑lo这个值如果不删 会不会造成矛盾
        if(maxIdx[lo] != 0 && minIdx[lo] < pre)
            break;
        pre = max(pre, maxIdx[lo]);
    }
    cout << ans << "\n";
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> x;
    fill(minIdx, minIdx + x + 1, INT_MAX);
    for (int i = 1, num; i <= n; i++) {
        cin >> num;
        minIdx[num] = min(minIdx[num], i);
        maxIdx[num] = max(maxIdx[num], i);
    }
    solve();
};
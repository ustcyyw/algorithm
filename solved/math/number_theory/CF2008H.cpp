/**
 * @Time : 2024/10/25-10:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2008H 数论 + 二分
 */
/*
  * 中位数最小 假定现在中位数就是x
  * 1. 比x小的数再继续操作 不影响中位数依旧是x
  * 2. 比x大的数再操作
  *     2.1 但是操作后依旧比x大 不影响中位数依旧是x
  *     2.2 但是操作后的数比x小 那么x的排序往后移动 中位数变小
  * 也就是说在还能操作的情况下 继续操作可能会变好 或者至少不变 因此一定要通关操作将所有数变到最小
  * 将所有数按操作变为最小 其实就是对x取余
  *
  * 求数组的中位数 换一个角度说明中位数。 假定数组元素数量的一半是cnt
  * 那么中位数就是找 最小的数k 使得数组中 <= k 的元素数量 >= cnt
  * 于是可以用二分的思路求
  * 二分的关键在于如何求 <= k 的元素数量
  * 在本题中 数组是原数组对x取余数后的数组
  * 那么对x取余后会小于k的元素，需要满足的条件是 num 属于 [i * x, i * x + k]
  * 属于这个范围内的数对x取模后变为[0,k]
  * 对于给定的k和x，只需要求一系列区间上的元素总和即可（i从0开始直到i * x > n）
  * 不需要真的把原数组中每个元素都对x取余
  *
  * 由于x的范围是1～n 加速x刚好就是从1～n不同值的最坏情况
  * 在暂时不考虑二分复杂度的情况下，求元素数量的操作
  * 一系列区间的起点分别是
  * 0 1 2 3 4 ... n
  * 0 2 4 6 8 ... n
  * 0 3 6 9 12 ... n
  * 典型调和级数求和 总的时间复杂度nlog(n)
  * 而二分是至少而外增加了log(x)的时间复杂度（中位数小于x，二分的范围从0到x-1）
  *
  * 整体的时间复杂度是 nlog(n) * log(x)
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5 + 5;
int T, n, q, sum[N], m;
map<int, int> ans;

bool check(int k, int x) {
    int cnt = 0;
    for(int i = 0; i * x <= n; i++) {
        int lo = i * x, hi = min(i * x + k, n);
        if(i == 0) cnt += sum[hi];
        else cnt += sum[hi] - sum[lo - 1];
    }
    return cnt >= m;
}

void solve(int x) {
    int lo = 0, hi = x - 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid, x)) hi = mid;
        else lo = mid + 1;
    }
    ans[x] = lo;
    cout << lo << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> q;
        m = n % 2 == 0 ? (n + 2) / 2 : (n + 1) / 2;
        fill(sum, sum + n + 1, 0);
        ans = {};
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            sum[num]++;
        }
        for(int i = 1; i <= n; i++)
            sum[i] += sum[i - 1];
        for(int i = 1, x; i <= q; i++) {
            cin >> x;
            if(ans.count(x)) cout << ans[x] << " ";
            else solve(x);
        }
        cout << "\n";
    }
};
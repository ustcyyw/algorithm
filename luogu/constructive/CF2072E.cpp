/**
 * @Time : 2025/2/26-10:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2072E 构造 二分
 */
 /*
  * 如果两个点不共线 曼哈顿距离是两条直角边距离和 几何距离是斜边距离 不可能相等
  * 所以要满足等式的条件 就要求点共线
  * 一条线上有i个点，那么一共能产生满足条件的点对是 vi = i * (i - 1) / 2个
  * 假设有很多条水平线 分别有1 2 3 4 ... 448个点
  * （最大是448 因为有449个点 点对就会超出k的最大范围了）
  * 某条线上的点 不会再和其它点共线 那么等于是用 vi = i * (i - 1) / 2 这些值去凑出来k
  * 前后两个值最大差值是 448 * 447 / 2 - 447 * 446 / 2 = 447
  * 因此给定一个k 找最大的 i 满足 vi <= k, 那么还要需要的点对更新为 k -= vi
  * 一次之后 k 最大为 447。 收敛得很快 500个点足够安排
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 505, mod = 1e9 + 7;
ll T, n, nums[N];

int init = []() -> int {
    for(int i = 2; i < N; i++)
        nums[i] = i * (i - 1) / 2;
    return 0;
}();

void solve() {
    vector<vector<int>> points;
    int layer = 0, x = 0;
    while(n > 0) {
        int idx = upper_bound(nums, nums + 500, n) - nums - 1;
        int cnt = nums[idx];
        n -= cnt;
        for(int i = 0; i < idx; i++)
            points.push_back({layer, x++});
        layer++;
    }
    cout << points.size() << "\n";
    for(auto& p : points)
        cout << p[0] << " " << p[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        solve();
    }
}
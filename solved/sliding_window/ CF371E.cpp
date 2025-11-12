/**
 * @Time : 2024/4/4-5:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 一定是紧挨着的k个点 理由如下
  * k个点的距离和可以写成 (k - 1) * (x[k] - x[1]) + (k - 3) * (x[k - 1] - x[2]) + ...的形式
  * 选择最靠近的k个点，可以使上述每一组x的距离最短 总距离和就最短
  *
  * 于是考虑大小为k的一个窗口
  * 有新的点j添加时 其对距离总和的贡献为 pos[j] * (k - 1) - sum[j - k + 1, j - 1]
  * 就是对前其左边k-1个点的距离之和 要加上
  * 有新的点i从窗口中移除时 原本其对距离的总和贡献为 sum[i + 1, i + k - 1] - pos[i] * (k - 1)
  * 就是其右边k-1个点的距离只和 要扣除
  * 特别注意窗口大小还不到k时，只加上对前面元素的距离贡献
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 3e5 + 5;
ll T, n, k, sum[N] = {0};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vector<vector<ll>> arr;
    arr.push_back({-(int)1e9, -1}); // 哨兵 为了让真实的坐标点从arr数组中的索引1开始
    for(int i = 1, pos; i <= n; i++) {
        cin >> pos;
        arr.push_back({pos, i});
    }
    sort(arr.begin(), arr.end());
    for(int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + arr[i][0];
    cin >> k;
    ll idx = -1, ans = LONG_LONG_MAX, cur = 0;
    for(int i = 1, j = 1; j <= n; j++) {
        if(j - i + 1 <= k) {
            cur += (j - i) * arr[j][0] - sum[j - 1];
        } else {
            cur += (k - 1) * (arr[j][0] + arr[i][0]) - 2 * (sum[j - 1] - sum[i]);
            i++;
        }
        if(j - i + 1 == k && cur < ans) {
            ans = cur;
            idx = i;
        }
    }
    for(int i = 0; i < k; i++)
        cout << arr[idx + i][1] << " ";
};
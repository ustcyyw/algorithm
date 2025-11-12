/**
 * @Time : 2023/12/12-1:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 选出来的点进行排序

x[0]：会被后面n-1个元素减去；
x[n - 1]要减去前面n-1个元素
因此 这一组对距离的贡献值是 (n - 1) * (x[n - 1] - x[0])

x[1]：减去前面1个元素，被后面n-2个元素减去，净剩被减去n-3个；
x[n - 2]：减去前面n-2个元素，被后面一个元素减去，净剩下n-3个
因此 这一组对距离的贡献值是 (n - 3) * (x[n - 2] - x[1])

x[2]：减去前面2个元素，被后面n-3个元素减去，净剩被减去n-5个；
x[n - 3]：类似
因此 这一组对距离的贡献值是 (n - 5) * (x[n - 3] - x[2])

于是要求的表达式中 每一项的值为 (n - 2 * i + 1) * (x[n - 1 - i] - x[i])
并且满足 n - 1 - i > i
让每一组的两个点 x[n - 1 - i] - x[i] 尽可能接近， 整体求和就最小
很形象地表述就是 这些点应该像某个中心靠拢）

对于最外侧的一组 x[0], x[n - 1]。
取x[0] 它是最小的 且要尽可能的靠右 那么他应该取 min{r[i]}
同样 x[n - 1] 它是最大的 尽可能靠左 那么应该取 max{l[i]}
这样的取法 也将剩下的n-2个点的范围 尽可能得往中间取了
同时按定义有 x[n - 1] > x[0]
取完最外侧一组后 再从n-2个区间中取 x[1]和x[n - 2]
同理 x[1] 应该取剩余区间中最小右边界 x[n - 2] 应该取剩余区间中最大左边界
...
如果出现x[i] >= x[n - 1 - i]的情况，说明区间中最小有边界 >= 区间中最大左边界
这些区间都相交了，那这些区间的点应该取在同一个地方 对总距离的贡献为0 直接停止计算
 */
#include<bits/stdc++.h>

using namespace std;
int n;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vector<int> left(n, 0), right(n, 0);
    for (int i = 0; i < n; i++)
        cin >> left[i] >> right[i];
    sort(right.begin(), right.end()); // 右边界找最小的
    sort(left.begin(), left.end()); // 左边界找最大的
    long long res = 0;
    for(int i = 0; i < n && left[n - 1 - i] > right[i]; i++)
        res += (long long)(left[n - 1 - i] - right[i]) * (n -  2 * i - 1);
    cout << res << endl;
};
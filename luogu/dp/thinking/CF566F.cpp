/**
 * @Time : 2023/10/22-1:30 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 要能有边链接 a % b = 0 或者 b % a = 0
 * 一个团内任意两点都满足这个关系 那么将这个序列从大到小排列
 * 前面的元素一定是后面元素的因子 比如 3 6 18 54
 *
 * 问题转化为找最长子序列
 * 考虑从较小的数开始
 * 例如当前数是 num， 他可以作为 num * 2, num * 3 .... 的前置元素
 * len[num * 2] = len[num] + 1
 * len[num * 3] = len[num] + 1
 * 那么等逐渐枚举到 num * 2 时 又会更新到 (num * 2) * 2, (num * 2) * 3
 *
 * 题目中明确 每个数字的都是不同的 并且最大为N = 1e6
 * 那么上述更新过程 每一轮最多 N / num 次
 * 将所有轮次相加 最坏的情况下是 N / 1 + N / 2 + N / 4 + ... N / N
 * 这是调和级数 和为 NlogN
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 1;
int n, nums[N], len[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    memset(nums, 0, sizeof(nums));
    memset(len, 0, sizeof(len));
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        nums[num]++;
    }
    int res = 0;
    for(int i = 1; i < N; i++) {
        if(nums[i] == 0) continue;
        len[i]++; // 这个序列目前以i结尾 之前len[i]存放的是其因子结尾的最长序列
        for(int x = 2 * i; x < N; x += i) {
            len[x] = max(len[x], len[i]);
        }
        res = max(res, len[i]);
    }
    cout << res << endl;
}
/**
 * @Time : 2024/9/27-11:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1899E 思维
 */
/*
 * 数组中第一个最小值出现在i位置
 * 1. 必须对nums[1, i-1]的数进行操作 这样才能保证最小值出现在数组第一个位置
 * nums[1, i-1]的数操作 都会被放置在nums[i]之后相对合理的位置
 * 2. nums[i]在数组第一个位置 对nums[i]操作 他还是回到第一个位置 数组保持不变
 * 3. 由2可知 nums[i]之后的数永远不会被操作，相对位置是不变的 这些位置如果开始时候没有排序
 * 那就不可能完成排序
 * 4. 如果3的检查通过 nums[i + 1, n]是排序的 那么nums[1, i-1]的数经过操作
 * 他们都会进行一次冒泡排序 于是数组就有序了
 *
 * 因此 我们只需要找到第一最小值 然后检查从它开始的子数组是否有序
 * 如果有序 操作次数就是i-1，否则就无法完成排序输出-1
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, nums[N], minV, idx;

int solve() {
    for(int i = idx; i < n; i++) {
        if(nums[i] > nums[i + 1])
            return -1;
    }
    return idx - 1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        minV = INT_MAX, idx = -1;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            if(nums[i] < minV) minV = nums[i], idx = i;
        }
        cout << solve() << "\n";
    }
};
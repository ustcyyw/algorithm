/**
 * @Time : 2023/5/4-4:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 首先会想到枚举长度为k的窗口，然后考虑确定窗口位置后，将1置换进来
     * 但是确定窗口位置 置换1并不容易计算最小置换步骤，不知道分别在左边和右边取多少个1换进来
     *
     * 转换思路 找到相邻到k个1，那么将这k个1置换到一起，一定是当前区间内最好的
     * 直观会觉得将1向"中间"聚拢会比都移到边缘要好
     * 联想到中位数贪心 这个"中间" 就是处于中间到1的位置，其左右两边向它依次聚拢
     * 中位数贪心：找的是各个点到指定点位置的最小值 用到了前缀和来计算距离之和
     * 本题也可以类似地做 但是注意，本题需要1聚拢在一块，计算的是交换次数
     *
     * 假如 中间位置的1，mid，其右边有3个1，a,b,c，到中间位置的距离之和为dis
     * 依次向中间1聚拢，a的交换次数 = (a - mid) - 1
     * 由于a被移动到了mid的右边位置，b只用移动到a右边就聚拢了，b的交换次数 = (b - mid) - 2
     * 类似的 c的交换次数 = (c - mid) - 3
     *
     * 可以找规律 如果中间1的右边有m个元素
     * 交换次数=(a - mid) - 1 + (b - mid) - 2 + (c - mid) - 3 + .... (m - mid) - m
     * = (a + b + ... + m) - mid * m - (1 + 2 + 3 + ... + m)
     * = 中位数贪心的做法求距离和 - (m + 1) * m / 2
     */
    int minMoves(vector<int>& nums, int k) {
        vector<int> ones;
        for (int i = 0; i < nums.size(); i++)
            if (nums[i]) ones.push_back(i);
        int n = ones.size();
        vector<long> pre_sum(n + 1, 0l);
        for (int i = 1; i <= n; i++)
            pre_sum[i] = pre_sum[i - 1] + ones[i - 1];
        function<long(int, int, long, int)> cal = [&](int l, int r, long m, int pos) -> long {
            return abs(pre_sum[r + 1] - pre_sum[l] - m * pos) - (m + 1) * m / 2;
        };
        long res = LONG_MAX;
        for (int lo = 0, hi = k - 1, m1 = (k - 1) / 2, m2 = k - 1 - m1; hi < n; lo++, hi++) {
            int mid = (lo + hi) >> 1;
            res = min(res, cal(lo, mid - 1, m1, ones[mid])
                           + cal(mid + 1, hi, m2, ones[mid]));
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
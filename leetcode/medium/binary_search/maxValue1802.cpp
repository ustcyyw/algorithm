/**
 * @Time : 2022/10/13-4:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 要让指定的元素尽可能的大，那么其它元素要尽可能小
     * 保证差的绝对值<=1，并且每个数都大于0
     * 以指定元素为分割线，左边有素有 n1 = index个，右边元素有n2 = n - index个
     * 假设最大值为val，那么左右区间的最大值应该取 val - 1
     * 左右都是一个递减的数列，递减到1则保持1不变
     *
     * 从val减小至1，一共有 val - 1 + 1 = val项
     * 假设 n1 < val 那么最小元素取不到1，假设是x，满足 val - x + 1 = n1
     * x = val + 1 - n1
     * sum = (x + val) / 2 * val = (val + 1 + val - n) / 2 * n1
     * 如果 n1 >= val 那么能取到1，并且还剩余了 n1 - val 项
     * sum = (val + 1) * val / 2 + n1 - val
     */
    int maxValue(int n, int index, int maxSum) {
        if(n == maxSum) return 1;
        int lo = 2, hi = maxSum, n1 = index, n2 = n - index - 1;
        while (lo < hi){
            int mid = (lo + hi + 1) >> 1;
            if(get_sum(n1, mid - 1) + get_sum(n2, mid - 1) + mid <= maxSum)
                lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    long long get_sum(int n, int val){
        if(n < val) return ((long long)val + 1 + val - n) * n / 2;
        return ((long long)val + 1) * val / 2 + n - val;
    }
};

int main(){
    Solution s;
    s.maxValue(4, 2, 6);
    cout << 0 << endl;
}
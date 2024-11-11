/**
 * @Time : 2023/11/29-10:33 PM
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
     * 根据分数 arr[i] / arr[j] 且 i < j，可以说明分数小于1，并且是正数
     * 要找第k小的分数，我们可以先找到一个小数，让小于这个数的分数恰好有k个，并且这个小数最小
     * 可以使用二分答案 最终答案为lo
     * check函数注意到单调性，可以使用双指针来计数
     * 然后找到所有分数中 >= lo的最小分数 就是答案
     * 对于以arr[i]为分子, arr[j]为分母的分数 随着j增大 分数的值变小
     * 因此在固定i 找 >= lo的最小分数时，可以让j不断增大 直到arr[i] / arr[j] < lo
     * 那么 arr[i] / arr[j - 1]就是满足>= lo的最小分数的一个可能答案
     * 然后i++，分子变大，下一个可能的答案必然是接着当前的j继续向右找
     */
    vector<int> kthSmallestPrimeFraction(vector<int> &arr, int k) {
        long double lo = 0.0, hi = 1.0;
        while(abs(hi - lo) >= 1e-6) {
            long double mid = (hi + lo) / 2;
            if(check(arr, mid) >= k) hi = mid;
            else lo = mid;
        }
        int a = 1, b = 1, n = arr.size();
        for(int i = 0, j = 0; i < n; i++) {
            j = max(i + 1, j);
            while(j < n && (1.0 * arr[i] / arr[j] >= lo)) j++;
            if(j - 1 != i && b * arr[j - 1] > a * arr[i])
                a = arr[j - 1], b = arr[i];
        }
        return {b, a};
    }

    int check(vector<int> &arr, long double val) {
        int cnt = 0, n = arr.size();
        for(int i = 0, j = 0; i < n; i++) {
            j = max(i + 1, j);
            while(j < n && (1.0 * arr[i] / arr[j] > val)) j++;
            cnt += n - j;
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
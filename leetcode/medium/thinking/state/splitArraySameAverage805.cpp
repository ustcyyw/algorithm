/**
 * @Time : 2022/10/10-9:03 PM
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
     * 所有n个元素分为两堆，并且第一堆中有n1个元素分给了a数组，这部分和为s1
     * 第二堆中有n2个元素分给了a数组，这部分和为s2
     * 那么b数组的元素个数就是 n - (n1 + n2)，和为s - (s1 + s2)
     * average(a) == average(a)也就是
     * (s1 + s2) / (n1 + n2) = (s - (s1 + s2)) / (n - (n1 + n2))
     * (n1 + n2)s - (n1 + n2)(s1 + s2) = (s1 + s2)n - (n1 + n2)(s1 + s2)
     * (n1 + n2)s = (s1 + s2)n
     * s1 * n - s * n1 = s * n2 - n * s2
     * n * s1 - s * n1 = -(n * s2 - s * n2)
     * 令 ti = n * si - s * ni, 上述条件就是 t1 = -t2
     * 所以average(a) == average(a)的必要条件就是 t1 = -t2
     * 从下往上就证明两 t1 = -t2 是average(a) == average(a)的充分条件
     * 于是我们只需要计算出两堆的 t 值，枚举t1，然后查看第二个堆中是否有-t2存在即可
     */
    int n, s;
    bool splitArraySameAverage(vector<int>& nums) {
        n = nums.size(), s = accumulate(nums.begin(), nums.end(), 0);
        vector<int> arr1, arr2;
        for(int i = 0; i < n; i++){
            if(i < n / 2) arr1.push_back(nums[i]);
            else arr2.push_back(nums[i]);
        }
        vector<int> t1 = calculate_t(arr1, false), t2 = calculate_t(arr2, true);
        t2.push_back(0); // 在其中一组中添加该组所有元素都不分给a的情况。不能两组都加，否则就会出现a数组为空的情况
        unordered_set<int> set;
        for(int t : t2) set.insert(-t);
        for(int t : t1) {
            if(set.count(t)) return true;
        }
        return false;
    }
    // flag为true表示这一堆中不允许将所有元素分给a，否则会出现a中分得所有元素，b为空的情况
    vector<int> calculate_t(vector<int>& nums, bool flag){
        vector<int> res;
        int m = nums.size(), u = (1 << m) - 1;
        for(int state = u; state ; state = (state - 1) & u){
            int si = 0, ni = 0;
            for(int j = 0; j < m; j++){
                if(((1 << j) & state) > 0)
                    ni++, si += nums[j];
            }
            if(state == u && flag) continue;
            res.push_back(n * si - s * ni);
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {3,1};
    cout << s.splitArraySameAverage(arr) << endl;
}
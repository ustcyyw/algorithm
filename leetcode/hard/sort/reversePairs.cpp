/**
 * @Time : 2022/5/29-8:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> aux, nums;
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        this -> nums = nums;
        aux.assign(n, 0);
        return sort(0, n - 1);
    }

    int sort(int lo, int hi){
        if(lo == hi) return 0;
        int mid = (lo + hi) / 2;
        return sort(lo, mid) + sort(mid + 1, hi) + merge(lo, mid, hi);
    }

    int merge(int lo, int mid, int hi){
        // count 表示后子数组有多少个元素已经归并。那么当前子数组的一个元素要归并时，就有count个数比它小但是放在其后面了
        int res = 0, count = 0;
        for(int k = lo, i = lo, j = mid + 1; k <= hi; k++){
            if(i > mid) aux[k] = nums[j++];
            else if(j > hi) {
                aux[k] = nums[i++];
                res += count;
            }
            else if(nums[i] > nums[j]) {
                aux[k] = nums[j++];
                count++;
            }
            else {
                aux[k] = nums[i++];
                res += count;
            }
        }
        for(int k = lo; k <= hi; k++)
            nums[k] = aux[k];
        return res;
    }
};

int main(){
    Solution s;
    vector<int> temp = {7,5,6,4};
    s.reversePairs(temp);
}
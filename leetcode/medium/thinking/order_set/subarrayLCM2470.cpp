/**
 * @Time : 2022/11/16-4:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
//    int subarrayLCM(vector<int>& nums, int k) {
//        int n = nums.size(), cnt = 0;
//        for(int i = 0; i < n; i++){
//            for(int j = i, num = nums[i], t = nums[i]; j < n && num <= k; j++){
//                t = gcd(num, nums[j]);
//                num = num * nums[j] / t;
//                if(num == k) cnt++;
//            }
//        }
//        return cnt;
//    }
/**
     * 2470:最小公倍数lcm为target的子数组的数目
     * 子数组元素增加，lcm不变或者增大，具有单调性
     * lcm增大的时候，最小也是*2，因此lcm的值域比较小，且题目限定了target <= 1000，大于这个值的lcm直接不必考虑
     *
     * 从后往左遍历
     * 有序集合arr维护：<最小公倍数lcm，该值对应的子数组数量>
     * 序列是单调递减，但公倍数不断变大，可能会导致头元素已经超过了target，就可以直接舍弃
     *
     * 当遍历到一个新的元素nums[i]时
     * arr中有效元素的lcm都要更新，如果有想同的lcm，就通过累加进行去重
     */
    int subarrayLCM(vector<int>& nums, int target){
        int n = nums.size(), res = 0;
        vector<pair<int, int>> arr;
        for(int i = n - 1; i >= 0; i--){
            int j = 1, k = 0, num = nums[i];
            arr.push_back({1, 1});
            while (j < arr.size() && arr[0].first > target) // 头元素已经超过了target，就可以直接舍弃
                arr[0] = arr[j++];
            arr[0].first = lcm(arr[0].first, num);
            for(; j < arr.size(); j++){
                arr[j].first = lcm(arr[j].first, num);
                // 注意这里是求数组的数量，所以去重的时候不是替换，而是累加
                if(arr[j].first == arr[k].first) arr[k].second += arr[j].second;
                else arr[++k] = arr[j];
            }
            arr.resize(k + 1);
            for(auto& p : arr)
                if(p.first == target) res += p.second;
        }
        return res;
    }

};

int main(){
    Solution s;
    vector<int> arr = {3,6,2,7,1};
    s.subarrayLCM(arr, 6);
    cout << 0 << endl;
}
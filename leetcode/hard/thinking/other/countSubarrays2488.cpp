/**
 * @Time : 2022/11/30-4:16 PM
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
     * 根据题目对中位数的定义 中位数一定是原数组中的数，且数组元素都是不重复的
     * 因此子数组一定包括元素k
     * 以元素k为界限，将其分为左右两个部分
     * 记cnt为左边部分 大于k的数比小于k的数 多的数目
     *
     * 1.如果左边有奇数个元素：
     *      1.1 右边也有奇数个元素，要让k成为中位数，右边 大于k的数比小于k的数 多的数目 应该为-cnt
     *      这样相加之后，大于k的数和小于k的数，数目一致
     *      2.2 右边有偶数个元素，要让k成为中位数，大于k的数要比小于k的数多1才行，就要求右边为 -cnt + 1
     * 2.如果左右有偶数个元素，类似地分析
     *
     * 但是别忘了k作为左边界，右边界的两种情况。以及只有k一个元素的子数组
     */
    int countSubarrays(vector<int>& nums, int k) {
        int index = find_k(nums, k);
        unordered_map<int, int> odd, even;
        int ans = 1;
        // cnt: 大于k的数比小于k的数 多的数目
        for(int i = 1, cnt = 0; i + index < nums.size(); i++){
            cnt += nums[i + index] > k ? 1 : -1;
            if(i % 2 == 0){
                even[cnt] = even.count(cnt) ? even[cnt] + 1 : 1;
                if(cnt == 0) ans++;
            }
            else{
                odd[cnt] = odd.count(cnt) ? odd[cnt] + 1 : 1;
                if(cnt == 1) ans++;
            }
        }
        for(int i = 1, cnt = 0; index - i >= 0; i++){
            cnt += nums[index - i] > k ? 1 : -1;
            if(i % 2 == 0){
                if(odd.count(1 - cnt)) ans += odd[1 - cnt];
                if(even.count(-cnt)) ans += even[-cnt];
                if(cnt == 0) ans++;
            } else {
                if(odd.count(-cnt)) ans += odd[-cnt];
                if(even.count(1 - cnt)) ans += even[1 - cnt];
                if(cnt == 1) ans++;
            }
        }
        return ans;
    }

    int find_k(vector<int>& nums, int k){
        for(int i = 0; i < nums.size(); i++)
            if(nums[i] == k) return i;
        return 0;
    }
};

int main(){
    Solution s;
    vector<int> arr = {2,5,1,4,3,6};
    s.countSubarrays(arr, 1);
    cout << 0 << endl;
}
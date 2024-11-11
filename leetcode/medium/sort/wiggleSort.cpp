/**
 * @Time : 2022/6/15-11:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
//    void wiggleSort(vector<int>& nums) {
//        map<int, int> count;
//        for(int num : nums){
//            if(count.find(num) != count.end()) count[num]++;
//            else count[num] = 1;
//        }
//        for(int i = 0; i < nums.size(); i += 2){
//            auto it = count.begin();
//            int min_num = it->first;
//            nums[i] = min_num;
//            count[min_num]--;
//            if(i + 1 == nums.size()) break;
//            if(count[min_num] == 0){
//                nums[i + 1] = count.size() == 2 ? (++it)->first : (++++it)->first;
//                count.erase(min_num);
//            } else
//                nums[i + 1] = count.size() == 1 ? it->first : (++it)->first;
//            reduce_erase(count, nums[i + 1]);
//        }
//    }
//
//    void reduce_erase(map<int, int>& count, int key){
//        if(--count[key] == 0)
//            count.erase(key);
//    }
    /**
     * 假设偶数索引为峰
     * nums[0] < nums[1],应该当交换
     * 保证交换后 nums[0] > nums[1]
     * nums[2] < nums[1], 可以推出 nums[2] < nums[1] <= nums[0]应当交换
     * 保证交换后 nums[1] < nums[2],并且 nums[1] < nums[0]
     * 接下来是位置3,nums[2] < nums[3],应该当交换
     * 保证交换后 nums[2] > nums[3],并且 nums[2] > nums[1]
     *
     * 可以发现
     * 局部有序保证了全局的有序
     * @param nums
     */
    void wiggleSort(vector<int>& nums) {
        for(int i = 1; i < nums.size(); i++){
            if((i % 2 == 1 && nums[i] > nums[i - 1]) || (i % 2 == 0 && nums[i] < nums[i - 1])) {
                int temp = nums[i];
                nums[i] = nums[i - 1];
                nums[i - 1] = temp;
            }
        }
    }
};

int main(){
    Solution s;
    vector<int> arr = {8,3,9,9,6};
    s.wiggleSort(arr);
    cout << 0 << endl;
}
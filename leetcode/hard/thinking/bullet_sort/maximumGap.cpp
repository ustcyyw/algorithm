/**
 * @Time : 2022/9/6-7:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个无序的数组 nums，返回 数组在排序之后，相邻元素之间最大的差值 。如果数组元素个数小于 2，则返回 0 。

您必须编写一个在「线性时间」内运行并使用「线性额外空间」的算法。

 

示例 1:

输入: nums = [3,6,9,1]
输出: 3
解释: 排序后的数组是 [1,3,6,9], 其中相邻元素 (3,6) 和 (6,9) 之间都存在最大差值 3。
示例 2:

输入: nums = [10]
输出: 0
解释: 数组元素个数小于 2，因此返回 0。
 

提示:

1 <= nums.length <= 105
0 <= nums[i] <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-gap
 */
class Solution {
public:
    /**
     * 线性可以进行排序的，想到桶排序
     * 但是从数据范围来看，是不可以每个桶容纳特定元素的
     *
     * 可以借鉴分块的思想，一个桶不止可以容纳某一个值的元素
     * 而是可以容纳一类元素，或者说某个范围内的元素
     *
     * 如果元素的最大间距是d_max，一共有n个元素，元素最大值max_val,最小值min_val
     * 如果从min_val就以最大间距累加，可以累加至 min_val + (n - 1) * d_max
     * 这个值一定 >= max_val
     * min_val + (n - 1) * d_max >= max_val
     * d_max >= (max_val - min_val) / (n - 1) 这是数学形式
     * 但是计算自动向下取证，因此应该写做 d_max >= ceil((max_val - min_val) / (n - 1))
     * ceil表示向上取整
     *
     * 如果桶内的元素集中在长度为d = (max_val - min_val) / (n - 1) + 1的区间内，
     * 就不可能由这些元素算出最大间距d_max
     * 最大间距就只能由相邻桶中的元素算出，就是每个桶的最小元素和上一个桶的最大元素之间的差值
     * 第一个桶要囊括第一个元素，且长度为d，那么它的区间为[min, min + d]或者[min, min + d)
     * 如果取前者，第二个区间就成(mid + d, mid + 2d],左开右闭，与第一个区间就出现了不一致。
     * 因此桶的区间取法应该是左闭右开
     * 桶的范围一定要能够装下所有元素，因此 d * num_bullet >= max - min
     * num_bullet >= (max - min) / d，这也是数学形式，计算机中向下取整
     * 因此桶的数量应该是 (max - min) / d + 1，桶的数量多了1无关紧要，所以直接+1
     */
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return 0;
        int min_val = INT_MAX, max_val = INT_MIN;
        for(int num : nums)
            min_val = min(num, min_val), max_val = max(num, max_val);
        if(min_val == max_val) return 0;
        int d = ceil((max_val - min_val) * 1.0 / (n - 1)), num_bullet = (max_val - min_val) / d + 1;
        vector<vector<int>> bullets(num_bullet, vector(3, 0));
        for(int num : nums){
            vector<int>& bul = bullets[(num - min_val) / d];
            if(bul[2] == 0){
                bul[0] = bul[1] = num;
                bul[2] = 1;
            }
            else
                bul[0] = min(bul[0], num), bul[1] = max(bul[1], num);
        }
        int res = 0;
        for(int i = 0, pre = min_val; i < num_bullet; i++){
            if(bullets[i][2]){
                res = max(res, bullets[i][0] - pre);
                pre = bullets[i][1];
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {1, 10000000};
    s.maximumGap(arr);
    cout << 0 << endl;
}
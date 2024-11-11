/**
 * @Time : 2022/9/3-3:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

算法的时间复杂度应该为 O(log (m+n)) 。

 

示例 1：

输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2
示例 2：

输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 

 

提示：

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/median-of-two-sorted-arrays
 */
class Solution {
public:
    /**
     * 一维情况下，中位数就是找到一条分割线
     * 使分割线的左边有n/2个元素，中位数就是分割线两边元素的平均值（元素个数为偶数的情况）
     * 或者分割线的左边有n/2+1个元素，中位数就是分割线左边的元素
     *
     * 二维情况下
     * 两个数组的元素个数分别为n和m
     * 假设分割线用i表示，将数组分割为[0,i-1]和[i,n-1]两个部分，左边刚好有i个元素
     * 我们也可以找到一对分割线 i,j 使得分割线左边的元素<=右边的元素
     * 偶数：左边有(m + n) / 2个元素，因为整数向下取整，m + n为偶数，所以(m + n) / 2 = (m + n + 1) / 2
     * 奇数：左边有(m + n) / 2 + 1个元素，同样等于有(m + n) / 2 + 1 = (m + n + 1) / 2
     * 因此都是使左边有 (m + n + 1) / 2 个元素，记为 size = (m + n + 1) / 2
     *
     * 假定第一个数组的分割线为i，那么其左边有i个元素
     * 第二个数组的分割线为j，左边有j个元素
     * 所以 i + j = size --> j = size - i
     * 如果是枚举i，i最大为n j = size - i = (m - n + 1) / 2
     * 如果n会大于m，j可能为负，不方便处理边界，所以我们假设 n <= m，这样j就非负了
     *
     * 分割线左边的元素<=右边的元素，这个条件成立，才说明这组分割有效
     * 左边元素的最大值是i和j左边的元素 nums1[i-1],nums2[j-1]分别记为l1,l2
     * 右边元素的最小值是i和j右边的元素 nums1[i],nums2[j]分别记为r1,r2
     * max(l1,l2) <= min(r1,r2)
     * 等价于四个不等式
     * l1 <= r1 , l2 <= r2 (这两个不等式天然满足，因为两个原数组本身有序)
     * l1 <= r2 , l2 <= r1
     * 因此关注后两个不等式即可
     * 如果不满足l1 <= r2，也就是l1 > r2，说明i取的太大了
     * i应该左移动让l1减小，r2增大
     * 如果满足了l1 <= r2，但还不确定是否同时满足l2 <= r1
     * 此时让i左移动r1更小，更不容易满足l2 <= r1，因此应该尝试让i右移
     * 在保证l1 <= r2成立的条件下，尽可能l2 <= r1
     *
     * 因此我们要找的是保证l1 <= r2成立的条件下，最大的i
     * 因为中位数是唯一的，只有那个最大的i能保证l1 <= r2 , l2 <= r1同时成立
     */
    int max_val = 1e7, min_val = -1e7;
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);
        int n = nums1.size(), m = nums2.size(), size = (n + m + 1) / 2;
        int lo = 0, hi = n;
        while (lo < hi){ // 二分第一个数组的分割线
            int i = (lo + hi + 1) >> 1, j = size - i;
            int l1 = i == 0 ? min_val : nums1[i - 1], r2 = nums2[j];
            if(l1 > r2) hi = i - 1;
            else lo = i;
        }
        // 二分结束后lo就是第一个数组的分割线i
        int i = lo, j = size - i;
        // 综合后面的取max和取min来处理边界。
        // 比如i=0时，数组1分割线左边的元素l1不存在，因此要让max(l1,l2) = l2，所以设定此时l1 = min_val
        int l1 = i == 0 ? min_val : nums1[i - 1], r1 = i == n ? max_val : nums1[i];
        int l2 = j == 0 ? min_val : nums2[j - 1], r2 = j == m ? max_val : nums2[j];
        if((m + n) % 2 == 1)
            return max(l1, l2);
        return (max(l1, l2) + min(r1, r2)) * 1.0 / 2;
    }
};

int main(){
    Solution s;
    vector<int> arr1 = {}, arr2 = {1};
    s.findMedianSortedArrays(arr1, arr2);
    cout << 0 << endl;
}
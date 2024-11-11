/**
 * @Time : 2022/9/12-12:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 *
Winston 构造了一个如上所示的函数 func 。他有一个整数数组 arr 和一个整数 target ，他想找到让 |func(arr, l, r) - target| 最小的 l 和 r 。

请你返回 |func(arr, l, r) - target| 的最小值。

请注意， func 的输入参数 l 和 r 需要满足 0 <= l, r < arr.length 。

 

示例 1：

输入：arr = [9,12,3,7,15], target = 5
输出：2
解释：所有可能的 [l,r] 数对包括 [[0,0],[1,1],[2,2],[3,3],[4,4],[0,1],[1,2],[2,3],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[0,4]]， Winston 得到的相应结果为 [9,12,3,7,15,8,0,3,7,0,0,3,0,0,0] 。最接近 5 的值是 7 和 3，所以最小差值为 2 。
示例 2：

输入：arr = [1000000,1000000,1000000], target = 1
输出：999999
解释：Winston 输入函数的所有可能 [l,r] 数对得到的函数值都为 1000000 ，所以最小差值为 999999 。
示例 3：

输入：arr = [1,2,4,8,16], target = 0
输出：0
 

提示：

1 <= arr.length <= 10^5
1 <= arr[i] <= 10^6
0 <= target <= 10^7

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target
 */
class Solution {
public:
    /**
     * 一种 n(logn)^2的解 使用了线段树
     * 在枚举边界的时候，固定一边，另一边在扩展的时候
     * 区间上的与都是单调降低或者不变。
     * 我们记区间上的与为t[i,j]
     *
     * 假设固定住右边界r,左边界从l=r开始向左扩展
     * 由于与操作中0不会恢复，因此arr[r]中有n个1，那么固定r的所有子区间中
     * 最多有c个不同的值（要么没消除任何一个1，值不变；要么消除至少一个1）
     * 这些值分别设为 t[r,r], t[i_1, r], t[i_2, r] ... t[i_n-1, r]
     * 其余区间与都无效，就是那些l左移动，没有消除任何1的情况，值都合并到这n个中了
     *
     * 然后r右移动
     * 区间与具有交换律和结合律，因此所有右边界为r+1的子区间上的与
     * 都只会从上述n个值中与arr[r + 1]得出，或者arr[r + 1]本身
     * 那么就是 t[r,r+1] = t[r,r] & arr[r + 1], t[i_n-1, r + 1] = t[i_n-1, r] & arr[r + 1]
     * 继续将重复的进行合并，就得到了所有右边界为r+1的子区间上的与
     *
     * 在r右移的过程中，将所有子区间上的与 减去 target，取绝对值，就枚举完所有的情况了
     */
    int closestToTarget(vector<int>& arr, int target){
        int n = arr.size(), res = abs(arr[0] - target);
        unordered_set<int> pre;
        pre.insert(arr[0]);
        for(int i = 1; i < n; i++){
            unordered_set<int> cur;
            cur.insert(arr[i]);
            for(int num : pre)
                cur.insert(num & arr[i]);
            for(int num : cur)
                res = min(res, abs(num - target));
            pre = cur;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
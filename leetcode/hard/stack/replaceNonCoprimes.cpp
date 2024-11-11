/**
 * @Time : 2022/8/11-3:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 nums 。请你对数组执行下述操作：

从 nums 中找出 任意 两个 相邻 的 非互质 数。
如果不存在这样的数，终止 这一过程。
否则，删除这两个数，并 替换 为它们的 最小公倍数（Least Common Multiple，LCM）。
只要还能找出两个相邻的非互质数就继续 重复 这一过程。
返回修改后得到的 最终 数组。可以证明的是，以 任意 顺序替换相邻的非互质数都可以得到相同的结果。

生成的测试用例可以保证最终数组中的值 小于或者等于 108 。

两个数字 x 和 y 满足 非互质数 的条件是：GCD(x, y) > 1 ，其中 GCD(x, y) 是 x 和 y 的 最大公约数 。

 

示例 1 ：

输入：nums = [6,4,3,2,7,6,2]
输出：[12,7,6]
解释：
- (6, 4) 是一组非互质数，且 LCM(6, 4) = 12 。得到 nums = [12,3,2,7,6,2] 。
- (12, 3) 是一组非互质数，且 LCM(12, 3) = 12 。得到 nums = [12,2,7,6,2] 。
- (12, 2) 是一组非互质数，且 LCM(12, 2) = 12 。得到 nums = [12,7,6,2] 。
- (6, 2) 是一组非互质数，且 LCM(6, 2) = 6 。得到 nums = [12,7,6] 。
现在，nums 中不存在相邻的非互质数。
因此，修改后得到的最终数组是 [12,7,6] 。
注意，存在其他方法可以获得相同的最终数组。
示例 2 ：

输入：nums = [2,2,1,1,3,3,3]
输出：[2,1,1,3]
解释：
- (3, 3) 是一组非互质数，且 LCM(3, 3) = 3 。得到 nums = [2,2,1,1,3,3] 。
- (3, 3) 是一组非互质数，且 LCM(3, 3) = 3 。得到 nums = [2,2,1,1,3] 。
- (2, 2) 是一组非互质数，且 LCM(2, 2) = 2 。得到 nums = [2,1,1,3] 。
现在，nums 中不存在相邻的非互质数。
因此，修改后得到的最终数组是 [2,1,1,3] 。
注意，存在其他方法可以获得相同的最终数组。
 

提示：

1 <= nums.length <= 105
1 <= nums[i] <= 105
生成的测试用例可以保证最终数组中的值 小于或者等于 108 。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/replace-non-coprime-numbers-in-array
 */
class Solution {
public:
    /**
     * 执行用时：160 ms, 在所有 C++ 提交中击败了56.30%的用户
     * 内存消耗：118 MB, 在所有 C++ 提交中击败了55.46%的用户
     */
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        int n = nums.size(), pre = nums[0];
        if(n == 1) return nums;
        vector<int> res;
        for(int i = 1; i < n; i++){
            int gcd = get_gcd(pre, nums[i]);
            if(gcd > 1) pre = (int)((long)pre * nums[i] / gcd);
            else {
                add(res, pre);
                pre = nums[i];
            }
        }
        add(res, pre);
        return res;
    }

    // 向结果集合中添加一个数，这个数可能会导致合并，因此要从数组的后向前看是否会合并
    // 所以正解使用栈模拟最好
    void add(vector<int>& res, int num){
        while (!res.empty()){
            int gcd = get_gcd(num, res.back());
            if(gcd == 1) break;
            num = (int)((long)num * res.back() / gcd);
            res.pop_back();
        }
        res.push_back(num);
    }

    int get_gcd(int a, int b){
        if(a < b) return gcd(b, a);
        if(b == 0) return a;
        return gcd(b, a % b);
    }

};

int main(){
    Solution s;
    vector<int> nums = {6,4,3,2,7,6,2};
    cout << nums.back() << endl;
    s.replaceNonCoprimes(nums);
    cout << s.get_gcd(899,20677) << endl;
    cout << 0 << endl;
}
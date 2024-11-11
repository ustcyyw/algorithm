/**
 * @Time : 2022/9/2-8:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

/**
 * 存在一个未知数组需要你进行还原，给你一个整数 n 表示该数组的长度。另给你一个数组 sums ，由未知数组中全部 2n 个 子集的和 组成（子集中的元素没有特定的顺序）。

返回一个长度为 n 的数组 ans 表示还原得到的未知数组。如果存在 多种 答案，只需返回其中 任意一个 。

如果可以由数组 arr 删除部分元素（也可能不删除或全删除）得到数组 sub ，那么数组 sub 就是数组 arr 的一个 子集 。sub 的元素之和就是 arr 的一个 子集的和 。一个空数组的元素之和为 0 。

注意：生成的测试用例将保证至少存在一个正确答案。

 

示例 1：

输入：n = 3, sums = [-3,-2,-1,0,0,1,2,3]
输出：[1,2,-3]
解释：[1,2,-3] 能够满足给出的子集的和：
- []：和是 0
- [1]：和是 1
- [2]：和是 2
- [1,2]：和是 3
- [-3]：和是 -3
- [1,-3]：和是 -2
- [2,-3]：和是 -1
- [1,2,-3]：和是 0
注意，[1,2,-3] 的任何排列和 [-1,-2,3] 的任何排列都会被视作正确答案。
示例 2：

输入：n = 2, sums = [0,0,0,0]
输出：[0,0]
解释：唯一的正确答案是 [0,0] 。
示例 3：

输入：n = 4, sums = [0,0,5,5,4,-1,4,9,9,-1,4,3,4,8,3,8]
输出：[0,-1,4,5]
解释：[0,-1,4,5] 能够满足给出的子集的和。
 

提示：

1 <= n <= 15
sums.length == 2n
-104 <= sums[i] <= 104

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/find-array-given-subset-sums
 */
class Solution {
public:
    /**
     * 如果原数组中的所有元素都是非负的
     * 1.<关键1>：在sums中除去0之后最小的元素就原数组中最小的数
     * 除去0的意思是，除去一个元素都不选的case
     * 然后就剩下两类sum：
     * a.单个数构成的sum, 对应state中有仅有1个二进制的1
     * b.至少两个数构成的sum，对应的state中有2个以上的二进制的1
     * 显然是a类 < b类，a类中最小的那个（也是全局最小）就是最小元素
     *
     * 2.在sums中除去最小数之后, sums中还剩两类sum：
     * a.除最小数之外，单个数构成的sum
     * b.至少两个数构成的sum（可能还有最小数在）
     * 显然还剩a类 < b类，a类中最小的那个（也是全局最小）就是未确定的最小元素
     *
     * 3.在sums继续除去刚才确定的次小元素
     * a.除最小的两个数之外，单个数构成的sum
     * b.至少两个数构成的sum，但注意这样的剔除方式，还会有最小的两个数组合成的sum存在
     * 此时无法确定 a类 < b类，因为有可能两个最小元素只和 < 第3小的元素
     * <关键2>：所以sums中的剔除元素方式应该改为剔除 <已经确定了的元素> 的所有子集的和
     * 这样剔除之后
     * a.还是除最小的两个数之外，单个数构成的sum
     * b.变为 单个元素 + 至少一个其它元素构成的sum
     * 并且单个元素虽然可以取最小的两个，但是其它元素至少要取到第三小的元素，因为最小的两个元素之和已经被删除了
     * 这种情况下就能确定 a类 < b类，a类中最小的那个（也是全局最小）就是未确定的最小元素
     *
     * 4.同3，将sums中剔除 <已经确定了的元素> 即最小三个数的所有子集的和
     * a.除最小的3个数之外，单个数构成的sum
     * b.单个元素 + 至少一个其它元素构成的sum
     * 单个元素虽然可以取最小的3个，但是和他们3搭配的，至少是第四小的元素
     * 注意最小三数之和也被剔除了
     *  a类 < b类，确定了第四小的元素
     *
     * <关键3>：以此类推，每次剔除以知元素的子序和，剩余sums中最小值，就是未确定元素中最小的那个
     */
    vector<int> recoverNoneNegArray(int n, vector<int> &sums) {
        multiset<int> set;
        for (int sum: sums)
            set.insert(sum);
        set.erase(set.begin());
        vector<int> res;
        while (res.size() < n)
            res.push_back(remove(set, res));
        return res;
    }

    int remove(multiset<int> &set, vector<int> &arr) {
        int n = arr.size(), u = (1 << n) - 1;
        for (int s = u; s; s = u & (s - 1)) {
            // 如果最高位为0，表示不选最新被确定的元素，那么这个子集就是在上一轮中已经被删除的了
            // 因此必须是最高位为1的时候，才是没有被删除过的子集
            if(!((1 << (n - 1)) & s)) continue;
            int sum = 0;
            for (int j = 0; j < n; j++)
                if ((1 << j) & s)
                    sum += arr[j];
            set.erase(set.find(sum));
        }
        return *set.begin();
    }

    /**
     * 但本题中，元素还有负数
     * <关键4> sums中的最小值 t，是所有负数之和
     * 如果sums中的所有元素加上 -t，相当于每一个子数组和中选了负数的，变为不选
     * 没有选负数的，变为选其相反数
     * 从子序列状态的角度，就是负数对应位置，原本是1表示选择负数的，现在变为0，表示不选
     * 原本是0表示不选负数的，现在变为1，表示选其相反数
     * <关键5> 于是整个状态集合就表示 <原数组绝对值的子序列>
     * 因此用刚才的方式求出 原数组的绝对值数组
     *
     * 绝对值数组选择一些元素变为负数，同样用状态压缩来实现
     * 如果某一个状态对应的情况下，负数之和刚好为最小值 t，就找到了答案
     */
    vector<int> recoverArray(int n, vector<int> &sums) {
        int t = 1e5;
        for (int num: sums)
            t = min(t, num);
        if (t >= 0) return recoverNoneNegArray(n, sums);
        for (int & sum : sums)
            sum -= t;
        vector<int> res = recoverNoneNegArray(n, sums);
        int u = (1 << n) - 1, s = u;
        for (; s; s = u & (s - 1)) {
            int sum = 0;
            for (int j = 0; j < n; j++)
                if ((1 << j) & s) sum -= res[j]; // 负数求和
            if (sum == t) break;
        }
        for (int j = 0; j < n; j++)
            if ((1 << j) & s)
                res[j] = -res[j];
        return res;
    }
};

int main() {
    Solution s;
    vector<int> arr = {-3, -2, -1, 0, 0, 1, 2, 3};
    s.recoverArray(3, arr);
    cout << 0 << endl;
}
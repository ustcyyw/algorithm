/**
 * @Time : 2022/12/6-4:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 给你两个长度相等的整数数组，返回下面表达式的最大值：

|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|

其中下标 i，j 满足 0 <= i, j < arr1.length。

 

示例 1：

输入：arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
输出：13
示例 2：

输入：arr1 = [1,-2,-5,0,10], arr2 = [0,-2,-1,-7,-4]
输出：20
 

提示：

2 <= arr1.length == arr2.length <= 40000
-10^6 <= arr1[i], arr2[i] <= 10^6

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-of-absolute-value-expression
 */
class Solution {
public:
    /**
     * f(i,j) = |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
     * i和j是完全对称的，因此只考虑i < j的情况即可
     * 将这个式子去绝对值
     * 1.ai >= aj, bi >= bj时
     * = ai - aj + bi - bj + j - i = (ai + bi - i) - (aj + bj - j)
     * 2.ai >= aj, bi < bj时
     * = ai - aj + bj - bi + j - i = (ai - bi - i) - (aj - bj - j)
     * 3. ai < aj, bi >= bj
     * = (bi - ai - i) - (bj - aj - j)
     * 4. ai < aj, bi < bj
     * = (aj + bj + j) - (ai + bi + i)
     * 因此f(i,j)是一个分段函数，应该在每个解析式的定义域求出其解析式的最大值，最后再取最大
     * 但是因为这是个绝对值函数，在不满足定义域的情况下，代入解析式，求值，不满足的那一项会为负数
     * 直接导致算出来的值更小了。
     * 因此 分段函数各个段的最大值 刚好出现在它的定义域上了
     * 也就是说全局计算出的最大值与严格在定义域上算出的最大值是同一个
     *
     * 这类绝对值函数的，都可以分情况拆解 合并项之后找最大最小值
     */
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size(), res = 0;
        int max1, max2, max3, max4, min1, min2, min3, min4;
        max1 = max2 = max3 = max4 = INT_MIN;
        min1 = min2 = min3 = min4 = INT_MAX;
        for(int i = 0; i < n; i++){
            int t1 = arr1[i] + arr2[i] - i, t2 = arr1[i] - arr2[i] - i;
            int t3 = arr2[i] - arr1[i] - i, t4 = arr1[i] + arr2[i] + i;
            max1 = max(max1, t1), min1 = min(min1, t1);
            max2 = max(max2, t2), min2 = min(min2, t2);
            max3 = max(max3, t3), min3 = min(min3, t3);
            max4 = max(max4, t4), min4 = min(min4, t4);
        }
        return max(max(max1 - min1, max2 - min2), max(max3 - min3, max4 - min4));
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
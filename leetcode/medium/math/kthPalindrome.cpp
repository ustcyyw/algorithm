/**
 * @Time : 2022/7/12-7:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 queries 和一个 正 整数 intLength ，请你返回一个数组 answer ，其中 answer[i] 是长度为 intLength 的 正回文数 中第 queries[i] 小的数字，如果不存在这样的回文数，则为 -1 。

回文数 指的是从前往后和从后往前读一模一样的数字。回文数不能有前导 0 。

 

示例 1：

输入：queries = [1,2,3,4,5,90], intLength = 3
输出：[101,111,121,131,141,999]
解释：
长度为 3 的最小回文数依次是：
101, 111, 121, 131, 141, 151, 161, 171, 181, 191, 202, ...
第 90 个长度为 3 的回文数是 999 。
示例 2：

输入：queries = [2,4,6], intLength = 4
输出：[1111,1331,1551]
解释：
长度为 4 的前 6 个回文数是：
1001, 1111, 1221, 1331, 1441 和 1551 。
 

提示：

1 <= queries.length <= 5 * 104
1 <= queries[i] <= 109
1 <= intLength <= 15

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/find-palindrome-with-fixed-length
 */
class Solution {
public:
    /**
     * 数学找规律题
     */
    vector<long long> kthPalindrome(vector<int>& queries, int intLength) {
        int max_q = pow(10, (intLength + 1) / 2 - 1) * 9;
        vector<long long> res;
        for(int num : queries){
            if(num > max_q) res.push_back(-1);
            else res.push_back(get_num(num, intLength));
        }
        return res;
    }

    long long get_num(int order, int len){
        string str = string(len, ' ');
        int temp = pow(10, (len - 1) / 2);
        for(int lo = 0, hi = len - 1; lo <= hi && order != 0; lo++, hi--){
            int a = order / temp;
            if(lo == 0)// 第一位要特殊处理，因为不能以0开头
                a = order % temp == 0 ? a : a + 1;
            else
                a = order % temp == 0 ? a - 1 : a;
            str[lo] = str[hi]= (char)(a + '0');
            order %= temp;
            temp /= 10;
        }
        for(int i = 0; i < len; i++)
            if(str[i] == ' ') str[i] = '9';
        return stoll(str);
    }
};

int main(){
    Solution s;
    vector<int> arr = {970,900,101,899,856,764,9001};
    s.kthPalindrome(arr, 5);
    cout << 0 << endl;
}
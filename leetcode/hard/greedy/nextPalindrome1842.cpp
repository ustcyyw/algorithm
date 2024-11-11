/**
 * @Time : 2023/11/3-12:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 你一个很长的数字回文串 num ，返回 大于 num、由相同数字重新组合而成的最小 回文串。

如果不存在这样的回文串，则返回空串 ""。

回文串 是正读和反读都一样的字符串。



示例 1：

输入：num = "1221"
输出："2112"
解释：下个比 "1221" 大的回文串是 "2112"。
示例 2：

输入：num = "32123"
输出：""
解释：不存在通过重组 "32123" 的数字可得、比 "32123" 还大的回文串。
示例 3：

输入：num = "45544554"
输出："54455445"
解释：下个比 "45544554" 还要大的回文串是 "54455445"。


提示：

1 <= num.length <= 105
num 是回文串。
 */
class Solution {
public:
    /*
     * 回文串 只要重排了前一半 后一半也就确定了
     * 要找到大于当前字符串且字典序最小的 其实就是找下一个排列
     * 参考leetcode 31题
     * 要找到一个字符能和前面一个更小的字符交换，这样字典序会变大，但是要找其中字典序最小的
     * 就应该和最靠近右边的字符交换 假定可以交换的最右边的位置是i
     * 如果交换位置相同 就交换尽可能小的数到前面 且满足nums[j] > nums[i]。
     * 并且交换后，i右边的所有元素应该重排列
     */
    string nextPalindrome(string num){
        int n = num.size();
        if(n == 1) return "";
        string half = num.substr(0, n / 2);
        half = next_per(half);
        if(half.empty()) return "";
        string temp = half;
        reverse(temp.begin(), temp.end());
        if(n % 2 != 0) half.push_back(num[n / 2]);
        return half + temp;
    }

    string next_per(string& s) {
        int lo = -1, hi = -1, n = s.size();
        stack<int> stack;
        stack.push(0);
        for(int i = 1; i < n; i++) {
            while(!stack.empty() && s[stack.top()] >= s[i])
                stack.pop();
            int t = stack.empty() ? -1 : stack.top();
            if(t > lo) lo = t, hi = i;
            else if(t == lo && t != -1 && s[i] < s[hi]) hi = i;
            stack.push(i);
        }
        if(lo == -1) return "";
        swap(s[lo], s[hi]);
        sort(s.begin() + lo + 1, s.end());
        return s;
    }
};

int main(){
    Solution s;

    cout << 0 << endl;
}
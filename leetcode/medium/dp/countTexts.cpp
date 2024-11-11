/**
 * @Time : 2022/7/29-11:35 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * Alice 在给 Bob 用手机打字。数字到字母的 对应 如下图所示。



为了 打出 一个字母，Alice 需要 按 对应字母 i 次，i 是该字母在这个按键上所处的位置。

比方说，为了按出字母 's' ，Alice 需要按 '7' 四次。类似的， Alice 需要按 '5' 两次得到字母  'k' 。
注意，数字 '0' 和 '1' 不映射到任何字母，所以 Alice 不 使用它们。
但是，由于传输的错误，Bob 没有收到 Alice 打字的字母信息，反而收到了 按键的字符串信息 。

比方说，Alice 发出的信息为 "bob" ，Bob 将收到字符串 "2266622" 。
给你一个字符串 pressedKeys ，表示 Bob 收到的字符串，请你返回 Alice 总共可能发出多少种文字信息 。

由于答案可能很大，将它对 109 + 7 取余 后返回。

 

示例 1：

输入：pressedKeys = "22233"
输出：8
解释：
Alice 可能发出的文字信息包括：
"aaadd", "abdd", "badd", "cdd", "aaae", "abe", "bae" 和 "ce" 。
由于总共有 8 种可能的信息，所以我们返回 8 。
示例 2：

输入：pressedKeys = "222222222222222222222222222222222222"
输出：82876089
解释：
总共有 2082876103 种 Alice 可能发出的文字信息。
由于我们需要将答案对 109 + 7 取余，所以我们返回 2082876103 % (109 + 7) = 82876089 。
 

提示：

1 <= pressedKeys.length <= 105
pressedKeys 只包含数字 '2' 到 '9' 。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/count-number-of-texts
 */
class Solution {
public:
    /**
     * 执行用时：48 ms, 在所有 C++ 提交中击败了53.25%的用户
     * 内存消耗：19.5 MB, 在所有 C++ 提交中击败了33.18%的用户
     */
    int countTexts(string s) {
        s = '1' + s; // 设置哨兵
        int n = s.size(), mod = 1e9 + 7;
        vector<long> dp = vector(n, 0l);
        dp[0] = 1;
        for(int i = 1; i < n; i++){
            char cur = s[i];
            int t = cur == '7' || cur == '9' ? 3 : 2;
            for(int j = i - 1; j >= 0 && t >= 0; j--, t--){
                dp[i] = (dp[i] + dp[j]) % mod;
                if(s[j] != cur) // 当前数字序列可以接在不同数字的后面，要先统计数量，然后才停止向前找相同的数字
                    break;
            }
        }
        return (int)dp[n - 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
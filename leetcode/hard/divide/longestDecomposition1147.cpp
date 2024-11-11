/**
 * @Time : 2022/10/1-3:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 你会得到一个字符串 text 。你应该把它分成 k 个子字符串 (subtext1, subtext2，…， subtextk) ，要求满足:

subtexti 是 非空 字符串
所有子字符串的连接等于 text ( 即subtext1 + subtext2 + ... + subtextk == text )
subtexti == subtextk - i + 1 表示所有 i 的有效值( 即 1 <= i <= k )
返回k可能最大值。

 

示例 1：

输入：text = "ghiabcdefhelloadamhelloabcdefghi"
输出：7
解释：我们可以把字符串拆分成 "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)"。
示例 2：

输入：text = "merchant"
输出：1
解释：我们可以把字符串拆分成 "(merchant)"。
示例 3：

输入：text = "antaprezatepzapreanta"
输出：11
解释：我们可以把字符串拆分成 "(a)(nt)(a)(pre)(za)(tpe)(za)(pre)(a)(nt)(a)"。
 

提示：

1 <= text.length <= 1000
text 仅由小写英文字符组成

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/longest-chunked-palindrome-decomposition
 */
class Solution {
public:
    /**
     * 贪心 + 分治
     */
    int longestDecomposition(string text) {
        return count(text, 0, text.size() - 1);
    }

    int count(string& test, int lo, int hi){
        if(lo > hi) return 0;
        if(lo == hi) return 1;
        int l = hi - lo + 1;
        for(int k = 0; k < l / 2; k++){
            if(check(test, lo, hi, k))
                return 2 + count(test, lo + k + 1, hi - k - 1);
        }
        return 1;
    }

    bool check(string& test, int lo, int hi, int k){
        for(int i = lo, j = hi - k; i <= lo + k; i++, j++)
            if(test[i] != test[j]) return false;
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
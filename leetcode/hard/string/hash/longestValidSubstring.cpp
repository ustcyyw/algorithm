/**
 * @Time : 2023/7/17-8:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个字符串 word 和一个字符串数组 forbidden 。

如果一个字符串不包含 forbidden 中的任何字符串，我们称这个字符串是 合法 的。

请你返回字符串 word 的一个 最长合法子字符串 的长度。

子字符串 指的是一个字符串中一段连续的字符，它可以为空。



示例 1：

输入：word = "cbaaaabc", forbidden = ["aaa","cb"]
输出：4
解释：总共有 9 个合法子字符串："c" ，"b" ，"a" ，"ba" ，"aa" ，"bc" ，"baa" ，"aab" 和 "aabc" 。最长合法子字符串的长度为 4 。
其他子字符串都要么包含 "aaa" ，要么包含 "cb" 。
示例 2：

输入：word = "leetcode", forbidden = ["de","le","e"]
输出：4
解释：总共有 11 个合法子字符串："l" ，"t" ，"c" ，"o" ，"d" ，"tc" ，"co" ，"od" ，"tco" ，"cod" 和 "tcod" 。最长合法子字符串的长度为 4 。
所有其他子字符串都至少包含 "de" ，"le" 和 "e" 之一。


提示：

1 <= word.length <= 105
word 只包含小写英文字母。
1 <= forbidden.length <= 105
1 <= forbidden[i].length <= 10
 */
typedef unsigned long long ull;
const int p = 13331;
class Solution {
public:
    ull str_hash(string &s) {
        int n = s.size();
        ull res = 0, pre = 0;
        for (int i = 1; i <= n; i++) {
            res = pre * p + s[i - 1];
            pre = res;
        }
        return res;
    }

    vector<ull> h, x;
    void init(string &s) {
        int n = s.size();
        h.assign(n + 1, 0ull), x.assign(n + 1, 1ull);
        for(int i = 1; i <= n; i++) {
            h[i] = h[i - 1] * p + s[i - 1];
            x[i] = x[i - 1] * p;
        }
    }

    ull get_hash(int l, int r) {
        return h[r + 1] - h[l] * x[r - l + 1];
    }

    int min_range(unordered_set<ull>& sets, int start) {
        for(int l = 1; l <= 10 && start + l - 1 < n; l++) {
            if(sets.count(get_hash(start, start + l - 1)))
                return l;
        }
        return INT_MAX;
    }

    int n;
    int longestValidSubstring(string word, vector<string>& forbidden) {
        init(word);
        n = word.length();
        unordered_set<ull> sets;
        for(string& temp : forbidden)
            sets.insert(str_hash(temp));
        int res = 0;
        for(int i = n - 1, hi = n; i >= 0; i--) {
            int t = min_range(sets, i);
            if(t == INT_MAX) res = max(res, hi - i);
            else {
                res = max(res, min(t - 1, hi - i));
                hi = min(hi, i + t - 1);
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<string> words = {"bcca","aaa","aabaa","baaac"};
    cout << s.longestValidSubstring("aaaabaaacc", words) << endl;
}
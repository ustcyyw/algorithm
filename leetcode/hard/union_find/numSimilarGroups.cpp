/**
 * @Time : 2022/8/12-9:47 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，那么称 X 和 Y 两个字符串相似。如果这两个字符串本身是相等的，那它们也是相似的。

例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)； "rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。

总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}。注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似。形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。

给你一个字符串列表 strs。列表中的每个字符串都是 strs 中其它所有字符串的一个字母异位词。请问 strs 中有多少个相似字符串组？

 

示例 1：

输入：strs = ["tars","rats","arts","star"]
输出：2
示例 2：

输入：strs = ["omv","ovm"]
输出：1
 

提示：

1 <= strs.length <= 300
1 <= strs[i].length <= 300
strs[i] 只包含小写字母。
strs 中的所有单词都具有相同的长度，且是彼此的字母异位词。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/imitate-string-groups
 */
class Solution {
public:
    /**
     * 执行用时：24 ms, 在所有 C++ 提交中击败了69.57%的用户
     * 内存消耗：9.6 MB, 在所有 C++ 提交中击败了91.06%的用户
     *
     * 并查集
     */
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size(), res = n;
        int id[n];
        for(int i = 0; i < n; i++)
            id[i] = i;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(check(strs[i], strs[j]) && !connect(id, i, j))
                    res--;
            }
        }
        return res;
    }

    int find(int id[], int p){
        if(id[p] == p) return p;
        id[p] = find(id, id[p]);
        return id[p];
    }
    // 已经链接了就返回true
    bool connect(int id[], int p, int q){
        int p_id = find(id, p), q_id = find(id, q);
        if(p_id == q_id) return true;
        id[p_id] = q_id;
        return false;
    }

    bool check(string& s1, string& s2){
        for(int i = 0, count = 0; i < s1.size(); i++){
            if(s1[i] != s2[i])
                if(++count > 2) return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
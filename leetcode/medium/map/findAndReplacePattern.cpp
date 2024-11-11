/**
 * @Time : 2022/6/17-5:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 你有一个单词列表 words 和一个模式  pattern，你想知道 words 中的哪些单词与模式匹配。

如果存在字母的排列 p ，使得将模式中的每个字母 x 替换为 p(x) 之后，我们就得到了所需的单词，那么单词与模式是匹配的。

（回想一下，字母的排列是从字母到字母的双射：每个字母映射到另一个字母，没有两个字母映射到同一个字母。）

返回 words 中与给定模式匹配的单词列表。

你可以按任何顺序返回答案。

 

示例：

输入：words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
输出：["mee","aqq"]
解释：
"mee" 与模式匹配，因为存在排列 {a -> m, b -> e, ...}。
"ccc" 与模式不匹配，因为 {a -> c, b -> c, ...} 不是排列。
因为 a 和 b 映射到同一个字母。
 

提示：

1 <= words.length <= 50
1 <= pattern.length = words[i].length <= 20

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/find-and-replace-pattern
 */
class Solution {
public:
    /**
     * 执行用时：4 ms, 在所有 C++ 提交中击败了73.57%的用户
     * 内存消耗：8.4 MB, 在所有 C++ 提交中击败了25.88%的用户
     */
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> res;
        for(string& word : words)
            if(check(word, pattern)) res.push_back(word);
        return res;
    }

    bool check(string word, string pattern){
        unordered_map<char, char> map1, map2;
        for(int i = 0; i < word.size(); i++){
            char c1 = word[i], c2 = pattern[i];
            bool flag1 = map1.find(c1) == map1.end(), flag2 = map2.find(c2) == map2.end();
            if(flag1 && flag2){ // 两个字符都不存在map中，说明是新的映射关系
                map1[c1] = c2;
                map2[c2] = c1;
            }
            // 一个字符在，另外一个字符不在，或者映射关系与当前对应位置的字符相矛盾
            else if(flag1 || flag2 || map1[c1] != c2 || map2[c2] != c1)
                return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
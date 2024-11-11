/**
 * @Time : 2022/5/11-10:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
//    int numSpecialEquivGroups(vector<string>& words) {
//        unordered_set<string> set;
//        set.insert(words[0]);
//        for(string& word2 : words){
//            bool in = false;
//            for(string word1 : set){
//                if(check(word1, word2)){
//                    in = true;
//                    break;
//                }
//            }
//            if(!in) set.insert(word2);
//        }
//        return set.size();
//    }
//
//    bool check(string& word1, string& word2){
//        if(word1 == word2) return true;
//        int n = word1.size(), lo = 0;
//        while (lo < n){
//            for(int j = lo; j < n; j += 2){
//                if(word1[lo] == word2[j]){
//                    if(lo != j) exch(word2, lo, j);
//                    break;
//                }
//            }
//            if(word1[lo] != word2[lo]) return false;
//            lo++;
//        }
//        return true;
//    }
//
//    void exch(string& word, int i, int j){
//        char temp = word[i];
//        word[i] = word[j];
//        word[j] = temp;
//    }

    /**
     * 只要奇数和偶数位置的元素分别相同
     * 就能通过有限次交换得到奇数，偶数位置相同的字符串。（比如分别排序，就能让两部分分别相同）
     *
     * 题目要求每个容器都是最大容量，所以只需要统计有多少种等价关系即可
     * 用排序后的字符串在set中去重即可
     */

    /**
     * 执行用时：4 ms, 在所有 C++ 提交中击败了97.64%的用户
     * 内存消耗：8.4 MB, 在所有 C++ 提交中击败了76.38%的用户
     */
    int numSpecialEquivGroups(vector<string>& words) {
        unordered_set<string> set;
        for(string& word : words){
            string even, odd;
            for(int i = 0; i < word.size(); i++){
                if(i % 2 == 0) even.push_back(word[i]);
                else odd.push_back(word[i]);
            }
            sort(even.begin(), even.end());
            sort(odd.begin(), odd.end());
            set.insert(even + odd);
        }
        return set.size();
    }
};

int main(){
    Solution s;
    vector<string> arr = {"abc","acb","bac","bca","cab","cba"};
    s.numSpecialEquivGroups(arr);
}
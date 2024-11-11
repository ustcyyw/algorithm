/**
 * @Time : 2023/4/24-10:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 给定一份单词的清单，设计一个算法，创建由字母组成的面积最大的矩形，其中每一行组成一个单词(自左向右)，每一列也组成一个单词(自上而下)。不要求这些单词在清单里连续出现，但要求所有行等长，所有列等高。

如果有多个面积最大的矩形，输出任意一个均可。一个单词可以重复使用。

示例 1:

输入: ["this", "real", "hard", "trh", "hea", "iar", "sld"]
输出:
[
   "this",
   "real",
   "hard"
]
示例 2:

输入: ["aa"]
输出: ["aa","aa"]
说明：

words.length <= 1000
words[i].length <= 100
数据保证单词足够随机


来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/word-rectangle-lcci
 */
class Solution {
public:
    int area = -1;
    vector<string> res, words;
    unordered_map<string, vector<int>> map;
    vector<string> maxRectangle(vector<string>& words) {
        this->words = words;
        for(int i = 0; i < words.size(); i++) {
            string& word = words[i];
            for(int j = 0; j < word.size(); j++){
                string key = word.substr(0, j + 1);
                if(!map.count(key)) map[key] = {};
                map[key].push_back(i);
            }
        }
        for(string& word : words){
            vector<string> aux;
            back_track(word, (int)word.size(), 0, -1, aux);
        }
        return res;
    }

    void back_track(string& first, int n, int cur, int width, vector<string>& aux){
        if(width != -1 && n * width <= area) return;
        if(aux.size() == n) {
            area = n * width;
            res = vector(aux.begin(), aux.end());
            return;
        }
        string key = first.substr(cur, 1);
        for(int index : map[key]) {
            if(!check(width, aux, words[index])) continue;
            aux.push_back(words[index]);
            back_track(first, n, cur + 1, (int) words[index].size(), aux);
            aux.pop_back();
        }
    }

    bool check(int width, vector<string>& aux, string& word){
        if(width != -1 && word.size() != width) return false;
        for(int i = 1; i < width; i++){
            string s;
            for(string& t : aux){
                s.push_back(t[i]);
                if(!map.count(s)) return false;
            }
            s.push_back(word[i]);
            if(!map.count(s)) return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
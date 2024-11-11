/**
 * @Time : 2022/5/14-8:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    unordered_set<string> dict, used;
    deque<vector<string>> queue;
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> res;
        for(string& word : wordList)
            dict.insert(word);
        if(dict.find(endWord) == dict.end()) return res;
        queue.push_back({beginWord, beginWord + ","});
        used.insert(beginWord);
        while (!queue.empty() && res.empty()){
            int size = queue.size();
            unordered_set<string> cur_used;
            for(int i = 0; i < size; i++){
                vector<string> cur = queue.front();
                queue.pop_front();
                if(cur[0] == endWord) res.push_back(split(cur[1]));
                if(res.empty()) addNextStep(cur_used, cur);
            }
        }
        return res;
    }

    void addNextStep(unordered_set<string>& cur_used, vector<string>& cur){
        string word = cur[0], line = cur[1];
        for(int i = 0; i < word.size(); i++){
            char temp = word[i];
            for(char c = 'a'; c <= 'z'; c++){
                word[i] = c;
                if(dict.find(word) != dict.end() &&
                (cur_used.find(word) != cur_used.end() || used.find(word) == used.end())){
                    string next = word;
                    cur_used.insert(word);
                    queue.push_back({next, line + word + ","});
                    used.insert(next);
                }
            }
            word[i] = temp;
        }
    }

    vector<string> split(string line){
        vector<string> words;
        for(int pre = 0, i = 0; i < line.size(); i++){
            if(line[i] == ','){
                words.push_back(line.substr(pre, i - pre));
                pre = i + 1;
            }
        }
        return words;
    }
};

int main(){
    Solution s;
    vector<string> arr = {"hot","dot","dog","lot","log","cog"};
    s.findLadders("hit", "cog", arr);
}
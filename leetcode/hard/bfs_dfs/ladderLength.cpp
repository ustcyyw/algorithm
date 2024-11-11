/**
 * @Time : 2022/12/15-5:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> set;
        for(auto& word : wordList) set.insert(word);
        if(!set.count(endWord)) return 0;
        set.erase(beginWord);
        queue<string> queue;
        queue.push(beginWord);
        int step = 2;
        while (!queue.empty()){
            int size = queue.size();
            for(int k = 0; k < size; k++){
                string word = queue.front(); queue.pop();
                for(int i = 0; i < word.size(); i++){
                    char t = word[i];
                    for(char c = 'a'; c <= 'z'; c++){
                        word[i] = c;
                        if(word == endWord) return step;
                        if(set.count(word)){
                            set.erase(word);
                            queue.push(word);
                        }
                    }
                    word[i] = t;
                }
            }
            step++;
        }
        return 0;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
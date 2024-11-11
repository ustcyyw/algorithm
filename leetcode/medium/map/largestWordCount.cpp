/**
 * @Time : 2022/7/15-9:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string largestWordCount(vector<string>& messages, vector<string>& senders) {
        unordered_map<string, int> map;
        for(int i = 0; i < messages.size(); i++){
            string name = senders[i];
            if(map.count(name)) map[name] += count_word(messages[i]);
            else map[name] =  count_word(messages[i]);
        }
        string name;
        int max_count = -1;
        for(auto pair : map){
            if(pair.second > max_count){
                max_count = pair.second;
                name = pair.first;
            }
            if(pair.second == max_count && pair.first > name){
                max_count = pair.second;
                name = pair.first;
            }
        }
        return name;
    }

    int count_word(string s){
        int count = 0;
        for(char c : s)
            if(c == ' ') count++;
        return count + 1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
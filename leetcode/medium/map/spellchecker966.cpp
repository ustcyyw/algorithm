/**
 * @Time : 2023/3/30-4:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> spellchecker(vector<string>& words, vector<string>& queries) {
        unordered_set<string> sets;
        unordered_map<string, int> lower, rep;
        for(int i = 0; i < words.size(); i++){
            string word = words[i];
            sets.insert(word);
            string temp = to_lower(word);
            if(!lower.count(temp)) lower[temp] = i;
            replace(temp);
            if(!rep.count(temp)) rep[temp] = i;
        }
        vector<string> res;
        for(string& word : queries){
            if(sets.count(word)) res.push_back(word);
            else {
                string temp = to_lower(word);
                if(lower.count(temp)) res.push_back(words[lower[temp]]);
                else {
                    replace(temp);
                    res.push_back(rep.count(temp) ? words[rep[temp]] : "");
                }
            }
        }
        return res;
    }

    void replace(string& word){
        for(char & c : word){
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                c = '*';
        }
    }

    string to_lower(string& word){
        string temp = word;
        for(int j = 0; j < word.length(); j++){
            if(temp[j] >= 'A' && temp[j] <= 'Z')
                temp[j] = (char)(temp[j] - 'A' + 'a');
        }
        return temp;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
/**
 * @Time : 2023/1/10-9:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isItPossible(string word1, string word2) {
        vector<int> counts1 = getCount(word1), counts2 = getCount(word2);
        int num1 = 0, num2 = 0;
        for(int i = 0; i < 26; i++){
            if(counts1[i]) num1++;
            if(counts2[i]) num2++;
        }
        if(abs(num1 - num2) > 2) return false;
        for(int i = 0; i < 26; i++){
            if(counts1[i] == 0) continue;
            for(int j = 0; j < 26; j++){
                if(counts2[j] == 0) continue;
                if(check(counts1, counts2, i, j, num1, num2))
                    return true;
            }
        }
        return false;
    }

    bool check(vector<int>& counts1, vector<int>& counts2, int i, int j, int num1, int num2){
        if(counts1[i] - 1 == 0) num1--;
        if(counts1[j] == 0) num1++;
        if(counts2[i] == 0) num2++;
        if(counts2[j] - 1 == 0) num2--;
        return num1 == num2;
    }

    vector<int> getCount(string& word){
        vector<int> counts(26, 0);
        for(char c : word)
            counts[c - 'a']++;
        return counts;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
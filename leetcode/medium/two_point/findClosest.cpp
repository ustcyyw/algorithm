/**
 * @Time : 2022/5/30-10:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findClosest(vector<string>& words, string word1, string word2) {
        vector<int> index1, index2;
        for(int i = 0; i < words.size(); i++){
            string word = words[i];
            if(word == word1) index1.push_back(i);
            if(word == word2) index2.push_back(i);
        }
        int n1 = index1.size(), n2 = index2.size(), res = abs(index1[n1 - 1] - index2[n2 - 1]);
        for(int i = 0, j = 0; ; ){
            if(i == n1 - 1 && j == n2 - 1) break;
            res = min(res, abs(index1[i] - index2[j]));
            if(i == n1 - 1) j++;
            else if(j == n2 - 1) i++;
            else if(index1[i] < index2[j]) i++;
            else j++;
        }
        return res;
    }
};

int main(){

}
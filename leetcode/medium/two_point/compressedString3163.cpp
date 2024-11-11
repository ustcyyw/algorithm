/**
 * @Time : 2024/5/27-2:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛399 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string compressedString(string word) {
        string res;
        for(int i = 0, n = word.size(), j = 0; i < n; ) {
            while(j < n && word[j] == word[i] && j - i + 1 <= 9)
                j++;
            int cnt = j - i;
            res.push_back((char)(cnt + '0'));
            res.push_back(word[i]);
            i = j;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
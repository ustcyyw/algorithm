/**
 * @Time : 2023/1/4-2:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 每次先从剩余需要添加的字母中找字母序最小的且可以添加的
     * 什么算可以添加的，因为这里是求子序列，且所有出现过的字符都要在子序列中出现一次
     * 就是保证添加这个字母后，其余还剩余的字符在其后面还出现
     *
     * 添加一个字母后，假设其索引在index 其余字母就只能添加index后的了
     */
    string smallestSubsequence(string s) {
        vector<vector<int>> letters(26, vector(0, 0));
        vector<int> point(26, 0);
        vector<bool> need(26, false);
        int cnt = 0, n = s.size();
        for(int i = 0; i < n; i++){
            int index = s[i] - 'a';
            letters[index].push_back(i);
            if(!need[index]) cnt++;
            need[index] = true;
        }
        string res;
        while (res.size() < cnt){
            for(int i = 0; i < 26; i++){
                if(need[i] && check(letters, point, need, i)){
                    need[i] = false;
                    res.push_back((char)(i + 'a'));
                    break;
                }
            }
        }
        return res;
    }

    bool check(vector<vector<int>>& letters, vector<int>& point, vector<bool>& need, int c){
        vector<int> aux = point;
        for(int i = 0; i < 26; i++){
            int n = letters[i].size();
            if(n == 0 || !need[i]) continue;
            while (aux[i] < n && letters[i][aux[i]] < letters[c][point[c]]) aux[i]++;
            if(aux[i] == n) return false;
        }
        for(int i = 0; i < 26; i++)
            point[i] = aux[i];
        return true;
    }
};

int main(){
    Solution s;
    s.smallestSubsequence("cbacdcbc");
    cout << 0 << endl;
}
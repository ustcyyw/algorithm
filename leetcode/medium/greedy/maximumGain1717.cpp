/**
 * @Time : 2022/12/14-3:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumGain(string s, int x, int y) {
        char first, second;
        if(x >= y) first = 'a', second = 'b';
        else first = 'b', second = 'a';
        int res = 0;
        s = get_point(res, s, first, second, max(x, y));
        get_point(res, s, second, first, min(x, y));
        return res;
    }

    string get_point(int& res, string& s, int first, int second, int p){
        string t;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == second && !t.empty() && t.back() == first){
                res += p;
                t.pop_back();
            } else t.push_back(s[i]);
        }
        return t;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
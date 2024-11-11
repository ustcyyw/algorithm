/**
 * @Time : 2022/9/2-10:03 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProduct(string t) {
        int n = t.size(), u = (1 << n) - 1;
        vector<int> states, lens;
        for(int s = u; s ; s = (s - 1) & u){
            string str;
            for(int j = 0; j < n; j++)
                if((1 << j) & s)
                    str.push_back(t[j]);
            if(check(str)){
                states.push_back(s);
                lens.push_back(str.size());
            }
        }
        int res = 0;
        for(int i = 0; i < states.size(); i++){
            for(int j = i + 1; j < states.size(); j++){
                int s1 = states[i], s2 = states[j];
                if(!has_intersect(s1, s2, n))
                    res = max(res, lens[i] * lens[j]);
            }
        }
        return res;
    }

    bool has_intersect(int s1, int s2, int n){
        for(int j = 0; j < n; j++){
            int mask = 1 << j;
            if((mask & s1) && (mask & s2))
                return true;
        }
        return false;
    }

    bool check(string& s){
        int i = 0, j = s.size() - 1;
        while (i < j)
            if(s[i++] != s[j--]) return false;
        return true;
    }
};

int main(){
    Solution s;
    s.maxProduct("bb");
    cout << 0 << endl;
}
/**
 * @Time : 2024/4/7-12:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛392 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string getSmallestString(string s, int k) {
        for(int i = 0; i < s.size() && k; i++) {
            for(int j = 0; j < 26; j++) {
                char c1 = (char)(j + 'a'), c2 = s[i];
                int d = dis(c1, c2);
                if(d <= k) {
                    s[i] = c1, k -= d;
                    break;
                }
            }
        }
        return s;
    }

    int dis(char c1, char c2) {
        if(c1 > c2) swap(c1, c2);
        return min(c2 - c1, c1 - 'a' + 'z' - c2 + 1);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
/**
 * @Time : 2023/2/15-10:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSwaps(string s) {
        int t1 = countBadPos(s, '0'), t2 = countBadPos(s, '1');
        if(t1 == -1 && t2 == -1) return -1;
        if(t1 != -1 && t2 != -1) return min(t1, t2);
        return t1 == -1 ? t2 : t1;
    }
    // 假设s应该以c开头，计算交替字符串中，c和另外一个字符错误的位置数量
    int countBadPos(string& s, char c){
        int n = s.size(), cnt1 = 0, cnt2 = 0;
        for(int i = 0; i < n; i++){
            if(i % 2 == 0 && s[i] != c) cnt1++;
            if(i % 2 == 1 && s[i] == c) cnt2++;
        }
        if(cnt1 != cnt2) return -1;
        return cnt1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
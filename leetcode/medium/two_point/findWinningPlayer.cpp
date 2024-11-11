/**
 * @Time : 2024/6/9-9:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛132 t2 双指针
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k) {
        int n = skills.size();
        for(int i = 0, j; i < n; ) {
            j = i + 1;
            while(j < n && skills[j] < skills[i]) j++;
            if(j - i - 1 + (i != 0) >= k) return i;
            i = j;
        }
        int mv = 0, idx = -1;
        for(int i = 0; i < n; i++) {
            mv = max(mv, skills[i]);
            if(skills[i] == mv) idx = i;
        }
        return idx;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
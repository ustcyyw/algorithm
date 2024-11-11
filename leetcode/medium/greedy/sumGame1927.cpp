/**
 * @Time : 2022/11/8-12:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        vector<int> info1 = get_info(num, 0, n / 2 - 1);
        vector<int> info2 = get_info(num, n / 2, n - 1);
        return check(info1, info2) || check(info2, info1);
    }

    // alice 尽可能的让sum1大，sum2尽可能小
    bool check(vector<int>& info1, vector<int>& info2){
        int sum1 = info1[0], cnt1 = info1[1], t1 = cnt1 % 2 == 1 ? 1 : 0;
        int sum2 = info2[0], cnt2 = info2[1];
        sum1 += (cnt1 / 2 + t1) * 9;
        if(cnt2 != 0)
            sum2 += (cnt2 / 2 + t1) * 9;
        return sum1 > sum2;
    }

    vector<int> get_info(string& s, int lo, int hi){
        int sum = 0, cnt = 0;
        for(int i = lo; i <= hi; i++){
            if(s[i] == '?') cnt++;
            else sum += s[i] - '0';
        }
        return {sum, cnt};
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
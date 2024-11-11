/**
 * @Time : 2023/7/26-9:11 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 直接限制好上下限的做法
     */
//    int n1, n2, mod = 1e9 + 7, min_sum, max_sum;
//    string s1, s2;
//    vector<vector<int>> cache;
//    int count(string num1, string num2, int min_sum, int max_sum) {
//        s1 = num1, s2 = num2;
//        n1 = num1.size(), n2 = num2.size();
//        this->min_sum = min_sum, this->max_sum = max_sum;
//        cache = vector(n2, vector(max_sum + 1, -1));
//        return count(0, 0, false, true, false);
//    }
//
//    long count(int sum, int i, bool is_num, bool up, bool down) {
//        if(sum > max_sum) return 0;
//        if(i == n2) return sum >= min_sum;
//        if(!up && !down && is_num && cache[i][sum] != -1) return cache[i][sum];
//        long cnt = 0;
//        // 当前位置不选数的情况 要保证前面没有选数，并且剩余位置选数还可以大于num1
//        // 此时 候选选则数字的上下限都没有限制
//        if(!is_num && i < n2 - n1) cnt = count(0, i + 1, false, false, false);
//        // 当前位置选数的下限 前置位置未选数，且到了必须选数的那一位，那么当前位置必须选数，且有下限，下限标识改为真
//        if(!is_num && n2 - n1 == i) down = true;
//        int a = down ? s1[n1 - (n2 - i)] - '0' : is_num ? 0 : 1;
//        // 当前位置选数的上限
//        int b = up ? s2[i] - '0' : 9;
//        for(int num = a; num <= b; num++) {
//            cnt += count(sum + num, i + 1, true, up && num == b, down && num == a);
//        }
//        cnt %= mod;
//        if(!up && !down && is_num) cache[i][sum] = cnt;
//        return cnt;
//    }

    /*
     * 转换一下 可以先求出小于等于 num1 的所有满足题意的数目 a
     * 再用同样的方法求出小于等于 num2 的所有满足题意的数目 b
     * a - b 就得到了 (num1, num2] 上的所有满足题意的数目 num1 就可以得出答案
     */
    int mod = 1e9 + 7, min_sum, max_sum;
    int count(string num1, string num2, int min_sum, int max_sum) {
        this->min_sum = min_sum, this->max_sum = max_sum;
        long res = count(num2) - count(num1);
        int sum = 0;
        for(char c : num1) sum += c - '0';
        if(sum >= min_sum && sum <= max_sum)
            res++;
        return (res + mod) % mod;
    }

    long count(string& s) {
        int n = s.size();
        vector<vector<int>> cache = vector(n, vector(max_sum + 1, -1));
        function<long(int, int, bool, bool)> count = [&](int i, int sum, bool limit, bool is_num) -> long {
            if (sum > max_sum) return 0;
            if (i == (int) s.size()) return sum >= min_sum;
            if (!limit && is_num && cache[i][sum] != -1) return cache[i][sum];
            long cnt = 0;
            if (!is_num) cnt = count(i + 1, sum, false, false);
            int up = limit ? s[i] - '0' : 9, down = is_num ? 0 : 1;
            for (int j = down; j <= up; j++)
                cnt += count(i + 1, sum + j, limit && j == up, true);
            cnt %= mod;
            if (!limit && is_num) cache[i][sum] = cnt;
            return cnt;
        };
        return count(0, 0, true, false);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
/**
 * @Time : 2024/1/9-12:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int T, string s) {
        function<long long(string)> count = [&](string num) -> long long {
            int n = num.size(), m = s.size();
            if(n < m) return 0;
            long long nt = stol(num.substr(n - m, m)), st = stol(s);
            if(n == m && nt < st) return 0;
            vector<long long> cache(n, -1);
            function<long long(int, bool, bool)> dfs = [&](int i, bool limit, bool is_num) -> long long {
                if(i == n - m) // 前面没有取到上限 或者 前面取了上限+后缀取st 还比 num小
                    return !limit || nt >= st;
                if(!limit && is_num && cache[i] != -1) return cache[i];
                long long cnt = 0;
                if(!is_num) cnt = dfs(i + 1, false, false);
                int up = limit ? num[i] - '0' : 9, down = is_num ? 0 : 1;
                for(int j = down; j <= min(up, T); j++){
                    cnt += dfs(i + 1, limit && j == up, true);
                }
                if(!limit && is_num) cache[i] = cnt;
                return cnt;
            };
            return dfs(0, true, false);
        };
        return count(to_string(finish)) - count(to_string(start - 1));
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
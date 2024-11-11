/**
 * @Time : 2023/4/27-3:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int base = (int)1e9;
    vector<vector<vector<int>>> cache;
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        cache = vector(n + 1, vector(n, vector(n, base)));
        int min_step = steps(n, firstPlayer - 1, secondPlayer - 1, 1);
        cache = vector(n + 1, vector(n, vector(n, base)));
        int max_step = steps(n, firstPlayer - 1, secondPlayer - 1, -1);
        return {min_step, -max_step};
    }

    int steps(int n, int f, int s, int flag) {
        if(f == n - s - 1) return flag;
        if(cache[n][f][s] != base) return cache[n][f][s];
        int step = base, m = n % 2 == 0 ? n / 2 : n / 2 + 1;
        vector<int> status = next_status(n, f, s);
        for(int u : status) {
            int nf = -1, ns = -1;
            for(int i = 0, cnt = 0; i < n; i++) {
                if(i == f) nf = cnt;
                if(i == s) ns = cnt;
                if((1 << i) & u) cnt++;
            }
            step = min(step, flag + steps(m, nf, ns, flag));
        }
        cache[n][f][s] = step;
        return step;
    }

    vector<int> next_status(int n, int f, int s){
        vector<int> ans;
        function<void(int, int, int)> back_track = [&](int status, int i, int j){
            if(j <= i) {
                ans.push_back(status);
                return;
            }
            int t1 = 1 << i, t2 = 1 << j;
            if(i == f || i == s) back_track(status ^ t2, i + 1, j - 1);
            else if(j == f || j == s) back_track(status ^ t1, i + 1, j - 1);
            else {
                back_track(status ^ t2, i + 1, j - 1);
                back_track(status ^ t1, i + 1, j - 1);
            }
        };
        back_track((1 << n) - 1, 0, n - 1);
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
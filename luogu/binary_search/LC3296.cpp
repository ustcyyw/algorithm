/**
 * @Time : 2024/12/13-2:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3296 二分答案
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    long long minNumberOfSeconds(int height, vector<int>& work) {
        ll lo = 1, hi = 1e18;

        function<bool(ll)> check = [&](ll t) -> bool {
            int cnt = 0;
            for(int num : work) {
                ll c = (ll)sqrt(2 * t / num);
                if(c * (c + 1) / 2 * num > t) c--;
                cnt += c;
                if(cnt >= height) return true;
            }
            return false;
        };

        while(lo < hi) {
            ll mid = (lo + hi) >> 1;
            if(check(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
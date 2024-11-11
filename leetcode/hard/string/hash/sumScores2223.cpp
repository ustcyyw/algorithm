/**
 * @Time : 2023/3/1-9:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int p = 13331;
class Solution {
public:
    /*
     * 字符串hash + 二分 确定最长前缀
     */
    vector<ull> h, x;
    long long sumScores(string s) {
        int n = s.size();
        h = vector(n + 1, 0ull), x = vector(n + 1, 1ull);
        for(int i = 1; i <= n; i++){
            h[i] = p * h[i - 1] + s[i - 1];
            x[i] = p * x[i - 1];
        }
        long long res = n;
        for(int i = n - 1; i > 0; i--){
            int lo = -1, hi = n - i - 1;
            while (lo < hi){
                int mid = (lo + hi + 1) >> 1;
                if(get_hash(0, mid) == get_hash(i, i + mid)) lo = mid;
                else hi = mid - 1;
            }
            res += lo + 1;
        }
        return res;
    }

    ull get_hash(int l, int r){
        return h[r + 1] - h[l] * x[r - l + 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
/**
 * @Time : 2023/2/25-6:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int p = 13331;
typedef unsigned long long ull;
class Solution {
public:
    int n;
    vector<ull> h, x;
    string longestDupSubstring(string s) {
        n = s.size();
        h = vector(n + 1, 0ull), x = vector(n + 1, 1ull);
        for(int i = 1; i <= n; i++){
            h[i] = h[i - 1] * p + s[i];
            x[i] = x[i - 1] * p;
        }
        int lo = 0, hi = n - 1;
        while (lo < hi){
            int mid = (lo + hi + 1) >> 1, t = check(mid);
            if(t == -1) hi = mid - 1;
            else lo = mid;
        }
        if(lo == 0) return "";
        return s.substr(check(lo), lo);
    }

    ull hash_code(int l, int r){
        return h[r + 1] - h[l] * x[r - l + 1];
    }

    int check(int len){
        unordered_set<ull> set;
        for(int i = 0, j = i + len - 1; j < n; i++, j++){
            ull code = hash_code(i, j);
            if(set.count(code)) return i;
            set.insert(code);
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
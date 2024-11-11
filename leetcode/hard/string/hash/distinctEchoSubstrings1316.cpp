/**
 * @Time : 2023/2/25-3:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int P = 13331;
class Solution {
public:
    vector<ull> h, x;
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        h = vector(n + 1, 0ull), x = vector(n + 1, 1ull);
        for(int i = 1; i <= n; i++){
            h[i] = h[i - 1] * P + text[i - 1];
            x[i] = x[i - 1] * P;
        }
        unordered_set<int> set;
        for(int i = 0; i < n; i++){
            for(int j = i; 2 * j - i + 1 < n; j++){
                ull h1 = hash_code(i, j), h2 = hash_code(j + 1, 2 * j - i + 1);
                if(h1 == h2) set.insert(h1);
            }
        }
        return set.size();
    }

    ull hash_code(int l, int r){
        return h[r + 1] - h[l] * x[r - l + 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
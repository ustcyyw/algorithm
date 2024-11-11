/**
 * @Time : 2023/2/21-5:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
//    int numSplits(string s) {
//        int n = s.size(), res = 0;
//        vector<vector<int>> sum(26, vector(n + 1, 0));
//        for(int i = 1; i <= n; i++){
//            for(int j = 0; j < 26; j++)
//                sum[j][i] = sum[j][i - 1];
//            sum[s[i - 1] - 'a'][i]++;
//        }
//        for(int i = 1; i < n; i++){
//            int left = 0, right = 0;
//            for(int j = 0; j < 26; j++){
//                if(sum[j][i]) left++;
//                if(sum[j][n] - sum[j][i]) right++;
//            }
//            if(left == right) res++;
//        }
//        return res;
//    }

    int numSplits(string s) {
        int n = s.size(), res = 0;
        unordered_set<char> set;
        vector<int> counts(n, 0);
        for(int i = 0; i < n; i++){
            set.insert(s[i]);
            counts[i] = set.size();
        }
        set.clear();
        for(int i = n - 1; i > 0; i--){
            set.insert(s[i]);
            if(set.size() == counts[i - 1]) res++;
        }
        return res;
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}
/**
 * @Time : 2023/2/20-11:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> numSmallerByFrequency(vector<string> &queries, vector<string> &words) {
        vector<int> counts, res;
        for (string &word: words)
            counts.push_back(f(word));
        sort(counts.begin(), counts.end());
        for (string &word: queries) {
            int cnt = f(word);
            res.push_back(counts.end() - upper_bound(counts.begin(), counts.end(), cnt));
        }
        return res;
    }

    int f(string &word) {
        int cnt[26] = {0};
        for (char c: word)
            cnt[c - 'a']++;
        for (int i = 0; i < 26; i++)
            if (cnt[i] > 0) return cnt[i];
        return -1;
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}
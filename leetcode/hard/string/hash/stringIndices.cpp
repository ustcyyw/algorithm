/**
 * @Time : 2024/3/24-1:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛390 t4
 */
 /*
  * 注意到 wordsContainer 和 wordsQuery中所有字符串的长度和 <= 5e5
  * 所以枚举每一个后缀 使用字符串hash 就可以将每个后缀o1地表示为hash值
  * 相同的hash值就代表相同的后缀 再按照题目要求取原字符串最短 下标最小的即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 5e5 + 5, P = 13331;
vector<ull> x(N + 1, 1);

int init = []() -> int {
    for (int i = 1; i <= N; i++) {
        x[i] = x[i - 1] * P;
    }
    return 0;
}();

class Solution {
public:
    vector<ull> str_hash(string &s) {
        int n = s.size();
        vector<ull> h(n + 1, 0);
        for (int i = 1; i <= n; i++)
            h[i] = h[i - 1] * P + s[i - 1];
        return h;
    }

    ull get_hash(vector<ull> &h, int l, int r) {
        return h[r + 1] - h[l] * x[r - l + 1];
    }

    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        int min_v = -1, len = INT_MAX;
        unordered_map<ull, pair<int, int>> map;
        for(int i = 0; i < wordsContainer.size(); i++) {
            vector<ull> h = str_hash(wordsContainer[i]);
            int n = wordsContainer[i].size();
            if(n < len) len = n, min_v = i;
            for(int j = 0; j < n; j++) {
                ull hash = get_hash(h, j, n - 1);
                if(!map.count(hash) || map[hash].first > n) map[hash] = {n, i};
            }
        }
        function<int(string&)> find = [&](string& word) -> int {
            vector<ull> h = str_hash(word);
            int n = word.size();
            for(int j = 0; j < n; j++) {
                ull hash = get_hash(h, j, n - 1);
                if(map.count(hash)) return map[hash].second;
            }
            return min_v;
        };
        vector<int> res;
        for(string& word : wordsQuery)
            res.push_back(find(word));
        return res;
    }
};
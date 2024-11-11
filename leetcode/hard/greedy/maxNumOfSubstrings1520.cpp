/**
 * @Time : 2023/4/12-12:43 PM
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
     * 没想到贪心的记忆化搜索
     */
//    int n;
//    vector<vector<int>> sums;
//    vector<vector<int>> infos = vector(26, vector(0, 0)); // 存储各个字符的索引
//    vector<vector<int>> range = vector(26, vector(0, 0)); // 以某个字符为起点的特殊子串的范围
//    unordered_map<int, vector<vector<int>>> cache;
//    vector<string> maxNumOfSubstrings(string s) {
//        n = s.size();
//        for(int i = 0; i < n; i++)
//            infos[s[i] - 'a'].push_back(i);
//        sums.assign(26, vector(n + 1, 0));
//        for(int i = 1; i <= n; i++){
//            for(int j = 0; j < 26; j++)
//                sums[j][i] = sums[j][i - 1];
//            sums[s[i - 1] - 'a'][i]++;
//        }
//        for(int i = 0; i < 26; i++) {
//            int r = right_border(i);
//            if(r != -1) range[i] = {infos[i][0], r - infos[i][0] + 1};
//        }
//        vector<string> res;
//        for(auto& p : dfs(0))
//            res.push_back(s.substr(p[0], p[1]));
//        return res;
//    }
//
//    vector<vector<int>> dfs(int i){
//        if(i >= n) return {};
//        if(cache.count(i)) return cache[i];
//        vector<vector<int>> res;
//        for(int c = 0; c < 26; c++){
//            if(range[c].empty() || range[c][0] < i) continue;
//            vector<vector<int>> t = dfs(range[c][0] + range[c][1]);
//            if(t.size() + 1 < res.size()) continue;
//            if(res.empty() || res.size() < t.size() + 1
//               || total_len(res) > total_len(t) + range[c][1]) {
//                res = t;
//                res.push_back(range[c]);
//            }
//        }
//        cache[i] = res;
//        return res;
//    }
//
//    int total_len(vector<vector<int>>& arr){
//        int cnt = 0;
//        for(auto& p : arr)
//            cnt += p[1];
//        return cnt;
//    }
//
//    int right_border(int c){
//        if(infos[c].empty()) return -1;
//        int first = infos[c][0], last = infos[c].back();
//        if(last - first + 1 == infos[c].size()) return last;
//        for(int i = last; i < n; i++)
//            if(check(first, i)) return i;
//        return -1;
//    }
//
//    bool check(int l, int r){
//        for(int i = 0; i < 26; i++){
//            if(infos[i].empty()) continue;
//            int first = infos[i][0], last = infos[i].back();
//            if(last < l || first > r || (first >= l && last <= r)) continue;
//            if(sums[i][r + 1] - sums[i][l]) return false;
//        }
//        return true;
//    }

/*
 * 与方法1一致的预处理。但贪心地选取区间
 *
 * 本题最多有26个满足条件的子串，也就是每个字母一个子串
 * 将各种可能的子串处理完成后，他们是相互独立的区间 但可能有嵌套
 * 比如 abba 处理出来的区间[0,3]和[1,2]
 * 从子串个数的角度说，选择内区间=选外区间；但是从总长度的角度说，选择内区间 好于 选外区间
 * 因此对于嵌套的情况，应该选择内区间。
 *
 * 问题转化为排除外区间的情况下，将独立的区间都拿出来
 * 要优先选到内区间且排除外区间，就按右端点排序，然后有区间重叠就跳过即可。
 */
    int n;
    vector<vector<int>> sums;
    vector<vector<int>> infos = vector(26, vector(0, 0)); // 存储各个字符的索引
    vector<vector<int>> range = vector(26, vector(2, -1)); // 以某个字符为起点的特殊子串的范围
    vector<string> maxNumOfSubstrings(string s) {
        n = s.size();
        for(int i = 0; i < n; i++)
            infos[s[i] - 'a'].push_back(i);
        sums.assign(26, vector(n + 1, 0));
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < 26; j++)
                sums[j][i] = sums[j][i - 1];
            sums[s[i - 1] - 'a'][i]++;
        }
        for(int i = 0; i < 26; i++) {
            int r = right_border(i);
            if(r != -1) range[i] = {infos[i][0], r};
        }
        sort(range.begin(), range.end(),
             [](auto& a, auto& b) -> bool {return a[1] < b[1];});
        vector<string> res;
        for(int i = 0, pre = -1; i < 26; i++){
            vector<int>& p = range[i];
            if(p[0] <= pre) continue;
            pre = p[1];
            res.push_back(s.substr(p[0], p[1] - p[0] + 1));
        }
        return res;
    }

    int right_border(int c){
        if(infos[c].empty()) return -1;
        int first = infos[c][0], last = infos[c].back();
        if(last - first + 1 == infos[c].size()) return last;
        for(int i = last; i < n; i++)
            if(check(first, i)) return i;
        return -1;
    }

    bool check(int l, int r){
        for(int i = 0; i < 26; i++){
            if(infos[i].empty()) continue;
            int first = infos[i][0], last = infos[i].back();
            if(last < l || first > r || (first >= l && last <= r)) continue;
            if(sums[i][r + 1] - sums[i][l]) return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
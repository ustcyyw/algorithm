/**
 * @Time : 2022/11/3-8:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int m;
    int minimumTeachings(int n, vector<vector<int>> &languages, vector<vector<int>> &friendships) {
        m = languages.size();
        vector<unordered_set<int>> sets; // language -> set of people
        sets.assign(n + 1, {});
        for (int i = 1; i <= m; i++) {
            for (int l: languages[i - 1])
                sets[l].insert(i);
        }
        vector<vector<int>> aux;
        for (vector<int> &f: friendships)
            if(!check(f, sets)) aux.push_back(f);
        int res = INT_MAX;
        for(int l = 1; l <= n; l++)
            res = min(res, count_learn(aux, sets[l]));
        return res;
    }

    int count_learn(vector<vector<int>>& aux, unordered_set<int> & set){
        int cnt = 0;
        vector<bool> marked(m, false);
        for(vector<int>& f : aux){
            int v = f[0], w = f[1];
            if(!marked[v] && !set.count(v)) cnt++;
            if(!marked[w] && !set.count(w)) cnt++;
            marked[v] = marked[w] = true;
        }
        return cnt;
    }

    // 检查某一对朋友是否已经有共同语言
    bool check(vector<int> &f, vector<unordered_set<int>> & sets) {
        int v = f[0], w = f[1];
        for (int l = 1; l < sets.size(); l++) {
            if (sets[l].count(v) && sets[l].count(w))
                return true;
        }
        return false;
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}
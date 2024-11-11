/**
 * @Time : 2022/12/15-5:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int cnt;
    vector<int> id;
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        cnt = n;
        for(int i = 0; i < n; i++) id.push_back(i);
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(check(strs[i], strs[j]))
                    connect(i, j);
            }
        }
        return cnt;
    }

    int find(int p){
        if(id[p] == p) return p;
        id[p] = find(id[p]);
        return id[p];
    }

    void connect(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return;
        cnt--;
        id[p] = q;
    }

    bool check(string& word1, string& word2){
        int n = word1.size(), i = 0;
        while (i < n && word1[i] == word2[i]) i++;
        if(i == n) return true;
        int j = i + 1;
        while (j < n && word1[j] == word2[j]) j++;
        int k = j + 1;
        while (k < n && word1[k] == word2[k]) k++;
        if(k < n) return false;
        return j < n && word1[j] == word2[i] && word1[i] == word2[j];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
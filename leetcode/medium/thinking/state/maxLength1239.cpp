/**
 * @Time : 2023/4/19-4:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxLength(vector<string> &arr) {
        filter(arr);
        int n = arr.size(), res = 0;
        function<bool(int, int)> check = [&](int i, int j) {
            vector<bool> chars(26, false);
            for (char c: arr[i])
                chars[c - 'a'] = true;
            for (char c: arr[j])
                if (chars[c - 'a']) return false;
            return true;
        };
        vector<vector<bool>> valid(n, vector(n, false));
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++)
                valid[i][j] = check(i, j);
        }
        function<int(int, int)> get_len = [&](int status, int i) {
            int len = 0;
            for (int j = 0; j < i; j++) {
                if ((1 << j) & status) {
                    if (valid[j][i]) len += arr[j].size();
                    else return -1;
                }
            }
            return len + (int)arr[i].size();
        };
        unordered_set<int> set, aux;
        set.insert(0);
        for (int i = 0; i < n; i++) {
            for (int status: set) {
                aux.insert(status);
                int len = get_len(status, i);
                res = max(res, len);
                if(len != -1) aux.insert((1 << i) | status);
            }
            swap(aux, set);
            aux.clear();
        }
        return res;
    }

    void filter(vector<string>& arr){
        vector<string> aux;
        for(string& s : arr) {
            vector<int> count(26, 0);
            bool flag = true;
            for (char c: s)
                if(++count[c - 'a'] > 1) flag = false;
            if(flag) aux.push_back(s);
        }
        swap(aux, arr);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
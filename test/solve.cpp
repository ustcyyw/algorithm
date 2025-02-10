#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 3e4 + 5, P = 13331;

class Solution {
public:
    string s;
    int n, k;
    vector<vector<int>> pre;
    int maxDifference(string s, int k) {
        this->n = s.size(), this->k = k;
        s = '.' + s;
        this->s = s;
        pre = vector(n + 1, vector(5, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < 5; j++)
                pre[i][j] = pre[i - 1][j];
            pre[i][s[i] -'0'] = i;
        }
        int ans = INT_MIN;
        for(int i = 0; i < 5; i++) {
            for(int j  = 0; j < 5; j++) {
                if(i == j) continue;
                ans = max(ans, cal(i, j));
            }
        }
        return ans;
    }

    int cal(int num1, int num2) {
        int ans = INT_MIN;
        vector<vector<int>> val(4, vector(n + 1, n + 1));
        val[0][0] = 0;
        for(int i = 1, s1 = 0, s2 = 0, c1 = 0, c2 = 0; i <= n; i++) {
            int num = s[i] - '0';
            if(num == num1) s1 ^= 1, c1++;
            else if(num == num2) s2 ^= 1, c2++;
            int status = (s1 << 1) | s2, c = c1 - c2;
            int ps = status ^ 2;
            int j = min(i - k, pre[i][num2] - 1); // 保证子区间长度>=k并且存在nums2
            if(j >= 0) ans = max(ans, c - val[ps][j]);
            for(int u = 0; u < 4; u++)
                val[u][i] = val[u][i - 1];
            val[status][i] = min(val[status][i - 1], c);
        }
        return ans;
    }
};

int main() {
    vector<int> arr1 = {8,10,9};
    vector<int> arr2 = {10,6,6};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa","ac"};
    vector<vector<int>> arr4 = {{3,0,5},{3,1,6},{2,3,5}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
    s.maxDifference("1122211", 3);
}

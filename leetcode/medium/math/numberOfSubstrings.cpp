/**
 * @Time : 2024/7/28-1:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛408 t3
 */
 /*
  * 注意到 0的数量是带平方的 1的数量还要超过他
  * 那0的数量就最多是 sqrt(n)。
  * 于是我们可以枚举0的数量，靠得最近的cnt个0，其左边和右边可以怎么样取1 算一算即可。
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> arr;
    int numberOfSubstrings(string s) {
        arr.push_back(-1);
        int n = s.size();
        for(int i = 0; i < n; i++)
            if(s[i] == '0') arr.push_back(i);
        arr.push_back(n);
        int ans = 0;
        // 子数组中没有0的情况
        for(int i = 1; i < arr.size(); i++) {
            int m = arr[i] - arr[i - 1] - 1;
            ans += m * (m + 1) / 2;
        }
        // 枚举子数组中0的数量
        for(int i = 1; i <= sqrt(n); i++)
            cal(ans, i);
        return ans;
    }

    void cal(int& ans, int cnt0) {
        int s = cnt0 * cnt0;
        for(int i = 1, j = i + cnt0 - 1; j < arr.size() - 1; i++, j++) {
            int lo = arr[i - 1] + 1, hi = arr[j], rb = arr[j + 1] - 1;
            while(lo <= arr[i] && rb - lo + 1 - cnt0 >= s) {
                while(hi - lo + 1 - cnt0 < s && hi <= rb) hi++;
                ans += rb - hi + 1;
                lo++;
            }
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
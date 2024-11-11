/**
 * @Time : 2023/12/3-2:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛374 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
//    int countCompleteSubstrings(string s, int k) {
//        int n = s.length();
//        vector<int> split;
//        vector<vector<int>> sum(n + 1, vector(26, 0));
//        for(int i = 1; i <= n; i++) {
//            for(int j = 0; j < 26; j++)
//                sum[i][j] = sum[i - 1][j];
//            sum[i][s[i - 1] - 'a']++;
//            if(i < n && abs(s[i - 1] - s[i]) > 2)
//                split.push_back(i);
//        }
//        int m = split.size(), cnt = 0;
//        for(int i = 0, j = 0; i < n; i++) {
//            while(j < m && split[j] <= i) j++; // 让分割标识在左端点的右边
//            for(int t = 1; t <= 26; t++) {
//                int hi = i + t * k; // hi - 1是当前的子区间
//                if(hi > n) break;
//                if(j < m && split[j] <= hi - 1) break;
//                int flag = check(sum, i, hi, k);
//                if(flag == -1) break;
//                cnt += flag;
//            }
//        }
//        return cnt;
//    }
//
//    int check(vector<vector<int>>& sum, int lo, int hi, int k) {
//        for(int i = 0; i < 26; i++) {
//            int d = sum[hi][i] - sum[lo][i];
//            if(d > k) return -1;
//            if(d < k && d != 0)
//                return 0;
//        }
//        return 1;
//    }

    int countCompleteSubstrings(string s, int k) {
        int n = s.size(), res = 0;
        // m表示子串中的字符种数，那么子串的长度就是m * k
        function<void (int)> window = [&](int m) -> void {
            vector<int> arr(26, 0);
            for(int lo = 0, hi = 0, cnt = 0, len = m * k; hi < n && n - lo >= len; hi++) {
                if(hi > 0 && abs(s[hi] - s[hi - 1]) > 2) // 出现相邻字母相差大于2的情况 此时要以当前字母为左端点
                    arr.assign(26, 0), cnt = 0, lo = hi;
                char rc = s[hi] - 'a';
                arr[rc]++;
                if(arr[rc] == k) cnt++;
                if(arr[rc] == k + 1) cnt--;
                if(hi - lo + 1 > len) {
                    char lc = s[lo++] - 'a';
                    arr[lc]--;
                    if(arr[lc] == k) cnt++;
                    if(arr[lc] == k - 1) cnt--;
                }
                if(cnt == m) res++; // cnt == m 时 子串长度一定为len
            }
        };
        for(int i = 1; i <= 26; i++)
            window(i);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
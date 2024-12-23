/**
 * @Time : 2024/12/22-4:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3399 二分答案 双指针 贪心
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 显然要将连续相同的1和0通过操作拆散
     * 所以先通过双指针处理出所有元算相同的子串的长度 然后考虑怎么拆分
     * 注意长度为1子串的特殊之处
     * 其它所有长度v > 1的子串 在修改的时候
     * 总能通过合理的安排保证当前段的最后一个元素不变 这样就不会影响下一段
     * （具体就是每隔v个相同元素进行一次变换，但是如果要变换的元素刚好是当前段最后一个元素
     * 那么就在倒数第二个元素处进行操作，操作次数都是一样的）
     * 但是要求子串长度为1时，是可能改变当前段的第一个元素或最后一个元素
     * 导致相邻段相互影响 因此先对长度1特判即可
     */
    int minLength(string s, int numOps) {
        vector<int> arr;
        int n = s.size();
        for(int i = 0, j; i < n; i = j) {
            j = i + 1;
            while(j < n && s[j] == s[i]) j++;
            arr.push_back(j - i);
        }
        if(checkOne(s, numOps)) return 1;
        int lo = 2, hi = n;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(check(arr, mid, numOps)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    bool checkOne(string& s, int total) {
        int n = s.size();
        vector<vector<int>> dp(n, vector(2, 0));
        if(s[0] == '1') dp[0][0] = 1;
        else dp[0][1] = 1;
        for(int i = 1; i < n; i++) {
            int c1 = s[i] == '1' ? 0 : 1, c0 = s[i] == '0' ? 0 : 1;
            dp[i][0] = dp[i - 1][1] + c0;
            dp[i][1] = dp[i - 1][0] + c1;
        }
        return dp[n - 1][0] <= total || dp[n - 1][1] <= total;
    }

    bool check(vector<int>& arr, int v, int total) {
        int cnt = 0;
        for(int num : arr) {
            if(num <= v) continue;
            int temp = (num - v) / (v + 1);
            cnt += (num - v) % (v + 1) == 0 ? temp : temp + 1;
            if(cnt > total) return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
/**
 * @Time : 2022/8/16-7:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 *
 */
class Solution {
public:
    /**
     * dp[i] 组合之和为i的最大数字的组成情况：数字共几位(dp[i][10])，每一个数字的出现次数(dp[i][1]~dp[i][9])
     * dp[i] 与 dp[j] 之间的比较，首先是数位多的大，然后依次比较9到1出现的次数
     *
     * 1～9的数字可能会有相同的cost，从贪心的角度，我们只需要知道相同cost中最大的数字即可
     *
     * 执行用时：108 ms, 在所有 C++ 提交中击败了45.98%的用户
     * 内存消耗：40.7 MB, 在所有 C++ 提交中击败了47.13%的用户
     */
    string largestNumber(vector<int>& cost, int target) {
        unordered_map<int, int> map; // cost -> num
        for(int i = 1; i < 10; i++)
            map[cost[i - 1]] = i;
        vector<vector<int>> dp;
        dp.assign(target + 1, {});
        for(auto& p : map){
            int c = p.first;
            if(c > target) continue;
            dp[c] = vector(11, 0);
            dp[c][10] = 1;
            dp[c][p.second] = 1;
        }
        for(int i = 1; i <= target; i++){
            for(auto& p : map){
                int c = p.first;
                if(i - c < 0 || dp[i - c].empty()) continue;
                vector<int> temp = dp[i - c];
                temp[10]++, temp[p.second]++;
                if(dp[i].empty() || less(dp[i], temp))
                    dp[i] = temp;
            }
        }
        vector<int>& t = dp[target];
        if(t.empty()) return "0";
        string res;
        for(int i = 9; i > 0; i--){
            for(int j = 0; j < dp[target][i]; j++)
                res.push_back(char(i + '0'));
        }
        return res;
    }

    bool less(vector<int>& a, vector<int>& b){
        for(int i = 10; i > 0; i--){
            if(a[i] < b[i]) return true;
            if(a[i] > b[i]) return false;
        }
        return false;
    }
};

int main(){
    Solution s;
    vector<int> cost = {2,4,6,2,4,6,4,4,4};
    s.largestNumber(cost, 5);
    cout << 0 << endl;
}
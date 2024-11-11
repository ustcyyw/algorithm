/**
 * @Time : 2023/2/16-10:00 PM
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
     * dp[i][j] 表示截止arr[1,i]，以大小排序号为j的数字结尾能得到的严格递增序列的最小交换次数
     * val[i][j] 截止arr[1,i],最大数小于等与序号j的数字能得到的严格递增序列的最小交换次数
     * 大小排序序号从1开始
     *
     * dp[0][j]: 空序列，以任何大小的数字结尾的最小交换次数都是0
     * val[0][j] = min{dp[0][k]} = 0
     *
     * 计算中 i个数的序列，至少得用到排序为j的数  j >= i
     * 当前arr1中已经排了i个数，后续还有n-i个数，当前以第j个数字结尾，后续还有m-j个数字
     * m - j >= n - i 推出 j <= m - n - i
     */
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        vector<int> aux = scatter(arr1, arr2);
        unordered_set<int> set;
        for(int num : arr2)
            set.insert(num);
        int n = arr1.size(), m = aux.size();
        vector<vector<int>> dp(n + 1, vector(m + 1, -1)), val(n + 1, vector(m + 1, -1));
        dp[0].assign(m + 1, 0), val[0].assign(m + 1, 0);
        for(int i = 1; i <= n; i++){
            for(int j = i; j <= m - n + i; j++){
                int num = aux[j - 1]; // 排名为j的数
                // 如果num在arr2中或者本身就是当前arr1对应的数，才可能让arr1以排序为j的数num为结尾
                if(set.count(num) || arr1[i - 1] == num) {
                    if(val[i - 1][j - 1] == -1) dp[i][j] = -1;
                    else dp[i][j] = val[i - 1][j - 1] + (arr1[i - 1] == num ? 0 : 1);
                }
                if(dp[i][j] != -1)
                    val[i][j] = val[i][j - 1] != -1 ? min(val[i][j - 1], dp[i][j]) : dp[i][j];
                else val[i][j] = val[i][j - 1];
            }
        }
        return val[n][m];
    }

    vector<int> scatter(vector<int>& arr1, vector<int>& arr2){
        vector<int> aux;
        unordered_set<int> set;
        filter(set, arr1, aux), filter(set, arr2, aux);
        sort(aux.begin(), aux.end());
        return aux;
    }

    void filter(unordered_set<int>& set, vector<int>& arr, vector<int>& aux){
        for(int num : arr){
            if(set.count(num)) continue;
            set.insert(num);
            aux.push_back(num);
        }
    }
};

int main(){
    Solution s;
    vector<int> arr1 = {1,5,3,6,7}; vector<int> arr2 = {1,3,2,4};
    s.makeArrayIncreasing(arr1, arr2);
    cout << 0 << endl;
}
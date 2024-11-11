/**
 * @Time : 2022/8/13-10:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        arr.push_back(1e9); // 哨兵
        int n = arr.size();
        int max_val[n][n], min_val[n][n];
        for(int i = 0; i < n; i++){
            int cur_max = arr[i], cur_min = arr[i];
            for(int j = i; j < n; j++){
                cur_max = max(arr[j], cur_max); max_val[i][j] = cur_max;
                cur_min = min(arr[j], cur_min); min_val[i][j] = cur_min;
            }
        }
        int res = 0;
        for(int pre = -1, i = 0; i < n - 1; i++){
            if(max_val[pre + 1][i] <= min_val[i + 1][n - 1]){
                res++;
                pre = i;
            }
        }
        return res;
    }

    /**
     * 贪心的思路就是
     * 假定当前还没有划分的区间是[j, n - 1]
     * 这句话的一个含义就是max[0,j - 1] <= min[j, n - 1]，否则将arr[0,j - 1]划分出去，整个数组最终不会有序
     * 要尽可能的划分[j, n - 1],就要找到一个最小的k，让max[j, k] <= min[k + 1, n - 1]
     * 由于max[0,j - 1] <= min[j, n - 1]，那么一定有max[0,j - 1] <= min[j, k] <= max[j, k]
     * 因此max[0,k] = max{max[0, j - 1], max[j,k]} = max[j,k]
     *
     * 在方法1中需要用到max[j,k]
     * 我们发现在这种特殊要求的划分方式下，一定有max[j,k]=max[0,k]，
     * 因此只需要维持max_val[k]表示区间[0,k]上的最大值
     *
     * 而方法1中对于 min_val[i + 1][n - 1]，右端点一直固定是n - 1，
     * 因此只要维护min_val[k]表示[k,n-1]上的最小值即可
     *
     * 执行用时：4 ms, 在所有 C++ 提交中击败了97.38%的用户
     * 内存消耗：11.6 MB, 在所有 C++ 提交中击败了99.56%的用户
     */
    int maxChunksToSorted2(vector<int>& arr) {
        arr.push_back(1e9); // 哨兵
        int n = arr.size();
        int max_val[n], min_val[n];
        max_val[0] = arr[0], min_val[n - 1] = arr[n - 1];
        for(int i = 1; i < n; i++)
            max_val[i] = max(max_val[i - 1], arr[i]);
        for(int i = n - 2; i >= 0; i--)
            min_val[i] = min(min_val[i + 1], arr[i]);

        int res = 0;
        for(int i = 0; i < n - 1; i++){
            if(max_val[i] <= min_val[i + 1]){
                res++;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
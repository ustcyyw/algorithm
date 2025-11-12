/**
 * @Time : 2023/10/18-12:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 降低维度
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 305;
int n, m, matrix[N][N];

long long sub_arr(vector<int> vals, vector<int>& nums) {
    int k = nums.size();
    vector<int> next(k, k), sum(k + 1, 0);
    for(int i = 1; i <= k; i++)
        sum[i] = sum[i - 1] + nums[i - 1];
    stack<int> stack;
    for(int i = k - 1; i >= 0; i--) {
        while (!stack.empty() && vals[stack.top()] >= vals[i])
            stack.pop();
        if(!stack.empty()) next[i] = stack.top();
        stack.push(i);
    }
    long long res = 0;
    stack = {};
    for(int i = 0; i < k; i++) {
        while (!stack.empty() && vals[stack.top()] >= vals[i])
            stack.pop();
        int l = !stack.empty() ? stack.top() + 1 : 0;
        res = max(res, (long long)vals[i] * (sum[next[i]] - sum[l]));
        stack.push(i);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cin >> matrix[i][j];
    }
    // 枚举矩阵上面一条边的范围 在这个范围内确定哪些连续的行能构成值最大的矩阵
    // 这些行的范围就是矩阵左面一条边的范围
    // 参与计算的是最小元素 那么每一行可能参与计算的就是该行此范围内的最小值
    // 参与计算的另外一个值是矩阵元素和，要求矩阵元素和 相当于将行内元素之和再求和 所以还要求行之和
    // 如同一维问题一样，枚举每一个行的和 看看这个值在尽可能大的范围内是最小的 就得到一个可能的答案
    vector<vector<vector<int>>> sums(n, vector(m, vector(m, 0))), vals(n, vector(m, vector(m, 0)));
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < m; i++) {
            int sum = 0, val = matrix[k][i];
            for(int j = i; j < m; j++) {
                val = min(val, matrix[k][j]);
                vals[k][i][j] = val;
                sum += matrix[k][j];
                sums[k][i][j] = sum;
            }
        }
    }
    long long res = 0;
    for(int i = 0; i < m; i++) {
        for(int j = i; j < m; j++) {
            vector<int> nums, min;
            for(int k = 0; k < n; k++) {
                nums.push_back(sums[k][i][j]);
                min.push_back(vals[k][i][j]);
            }
            res = max(res, sub_arr(min, nums));
        }
    }
    cout << res << endl;
}
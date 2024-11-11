/**
 * @Time : 2023/4/19-4:13 PM
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
     * 找规律
     * 因为这是一个循环的序列，所以在已知答案的情况下，将数组进行轮转，都是满足相邻二进制仅一位不同的要求
     * 那么我们可以将0轮转到第一个位置（考虑到0的特殊性），然后再观察规律
     *
     * 当小于等于2 ^ k - 1的数都已经排序后 arr[0]....arr[t]
     * 注意：这些数二进制位最高是 1 << (k - 1)
     * 接着要排的数 二进制最高位比之前的数左移一位 为 1 << k
     * 要保证arr[t + 1]和arr[t]只差一位，就需要使arr[t + 1] = 1 << k + arr[t]
     * 要保证 arr[t + 2]和arr[t + 1] = 1 << k + arr[t]只差一位
     * 且已知arr[t - 1]和arr[t]只差一位，那么令 arr[t + 2] = 1 << k + arr[t - 1]
     * 就保证了 arr[t + 1] 和 arr[t + 2] 最高二进制位都是1
     * 剩余差异体现在 arr[t] 和 arr[t - 1]，只差一位
     * 以此类推
     */
    vector<int> circularPermutation(int n, int start) {
        vector<int> aux(1, 0), res;
        for(int m = 1 << n, k = 0; (int)aux.size() < m; k++){
            for(int i = aux.size() - 1, d = 1 << k; i >= 0; i--)
                aux.push_back(d + aux[i]);
        }
        int i = 0, m = aux.size();
        while (aux[i] != start) i++;
        for(;res.size() < m; i = (i + 1) % m)
            res.push_back(aux[i]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
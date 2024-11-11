/**
 * @Time : 2023/4/5-5:04 PM
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
     * 长度为k的子数组和相同
     * 两个相邻的子数组
     * arr[0] + arr[1] + ... + arr[k - 1]
     * = arr[1] + arr[2] + ... + arr[k]
     * 推出 arr[0] = arr[k]
     * 同理可以得到 arr[k] = arr[2 * k], arr[2 * k] = arr[3 * k]
     * arr[1] = arr[1 + k] = arr[1 + 2 * k] = ...
     * 于是发现arr具有周期k
     * arr[i] = arr[i + j * k]
     *
     * 并且arr是循环数组，它还具有周期n
     * arr[i] = arr[i + j * n]
     *
     * arr[i] = arr[i + j1 * n] = arr[(i + j1 * n) + j2 * k]
     *
     * 裴蜀定理：
     * 设a，b是不全为0的整数，则存在整数x和y 使得ax + by = gcd(a,b)
     *
     * 所以 arr[i] = arr[i + gcd(n, k)]
     * 也就是说 arr 具有周期gcd(n, k)，这也是最小周期
     *
     * 于是我们将arr进行分组，共分为 gcd(n, k) 这么多组
     * 每一组中的元素都需要变为相等。
     *
     * 使每一个元素相等：中位数贪心，将元素都变为中位数
     * 假定变为数字 num，且 num < 中位数，小于等于num的数字共有cnt1个，大于num的数字共cnt2个
     * 如果变为数字 num + 1，cnt1个数字贡献的距离要+1，cnt2个数字贡献的距离-1
     * 距离变化量为 cnt1 - cnt2。因为num < 中位数，那么cnt1 < n / 2, cnt2 = n - cnt1 > n / 2 > cnt1
     * 所以距离变小了，因此变为num + 1更好
     *
     * 如果数字 num > 中位数， 类似可以推出变为 num - 1 更好
     * 因此变为相同的数，应该变为中位数 这样总距离最小（操作次数最小）
     */
    long long makeSubKSumEqual(vector<int>& arr, int k) {
        int n = arr.size(), t = gcd(n, k);
        vector<vector<int>> aux(t);
        for(int i = 0; i < n; i++)
            aux[i % t].push_back(arr[i]);
        long long res = 0;
        for(auto& a : aux)
            res += min_step(a);
        return res;
    }

    long long min_step(vector<int>& arr){
        sort(arr.begin(), arr.end());
        int mid = arr[arr.size() / 2];
        long long ans = 0;
        for(int num : arr)
            ans += abs(num - mid);
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
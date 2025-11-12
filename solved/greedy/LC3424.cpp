/**
 * @Time : 2025/1/20-10:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3424 贪心
 */
 /*
  * 操作1如果要使用 就只用一次 将brr拆成n个单独数组 然后将其放在最合理的位置
  * 最合理就是指arr和brr都排序后 按次序对应
  * 然后使用操作2调整每个元素
  *
  * 当然也能直接使用操作2
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    long long minCost(vector<int>& arr, vector<int>& brr, long long k) {
        ll t1 = cal(arr, brr);
        sort(arr.begin(), arr.end());
        sort(brr.begin(), brr.end());
        return min(t1, k + cal(arr, brr));
    }

    ll cal(vector<int>& arr, vector<int>& brr) {
        ll ans = 0;
        for(int i = 0; i < arr.size(); i++)
            ans += abs(arr[i] - brr[i]);
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
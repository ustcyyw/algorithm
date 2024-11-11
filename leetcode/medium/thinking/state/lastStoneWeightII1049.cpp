/**
 * @Time : 2022/9/19-11:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。

每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：

如果 x == y，那么两块石头都会被完全粉碎；
如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
最后，最多只会剩下一块 石头。返回此石头 最小的可能重量 。如果没有石头剩下，就返回 0。

 

示例 1：

输入：stones = [2,7,4,1,8,1]
输出：1
解释：
组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
示例 2：

输入：stones = [31,26,33,21,40]
输出：5
 

提示：

1 <= stones.length <= 30
1 <= stones[i] <= 100

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/last-stone-weight-ii
 */
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        vector<int> arr1, arr2;
        for(int i = 0, n = stones.size(); i < n; i++){
            if(i < n / 2) arr1.push_back(stones[i]);
            else arr2.push_back(stones[i]);
        }
        vector<int> w1 = get_weight(arr1), w2 = get_weight(arr2);
        sort(w1.begin(), w1.end()), sort(w2.begin(), w2.end());
        int res = INT_MAX, n1 = w1.size(), n2 = w2.size();
        for(int i = 0, j = 0; i < n1; i++){
            while (j < n2 && w2[j] <= w1[i]) j++;
            if(j > 0) res = min(res, abs(w2[j - 1] - w1[i]));
            if(j < n2) res = min(res, abs(w2[j] - w1[i]));
        }
        return res;
    }

    vector<int> get_weight(vector<int>& stones){
        int total = accumulate(stones.begin(), stones.end(), 0);
        int n = stones.size(), u = (1 << n) - 1;
        vector<int> res = {total};
        for(int s = u; s; s = (s -  1) & u){
            int sum = 0;
            for(int j = 0; j < n; j++)
                if((1 << j) & s) sum += stones[j];
            res.push_back(abs(total - 2 * sum));
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
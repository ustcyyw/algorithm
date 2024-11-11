/**
 * @Time : 2024/6/9-3:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛401 t3 背包dp
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxTotalReward(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        int n = arr.size(), mv = arr.back();
        vector<bool> f(mv, false);
        f[0] = true;
        for(int i = 0; i < n - 1; i++) {
            int v = arr[i];
            // 可取的值为j，如果要选择当前元素 那么前置元素为 j - v，需要满足j - v < v, j < 2v
            for(int j = min(mv - 1, 2 * v - 1); j >= v; j--) {
                f[j] = f[j] || f[j - v];
            }
        }
        for(int s = mv - 1; s >= 0; s--) {
            if(f[s]) return s + mv;
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
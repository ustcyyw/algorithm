/**
 * @Time : 2023/11/26-8:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        int l1 = getLen(hBars), l2 = getLen(vBars);
        int t = min(l1, l2);
        return (t + 1) * (t + 1);
    }

    int getLen(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int n = arr.size(), len = 0;
        for(int i = 0, j; i < n; ) {
            j = i + 1;
            while(j < n && arr[j] - arr[j - 1] == 1) j++;
            len = max(len, j - i);
            i = j;
        }
        return len;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
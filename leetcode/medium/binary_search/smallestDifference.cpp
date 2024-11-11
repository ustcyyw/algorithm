/**
 * @Time : 2022/6/21-1:39 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 执行用时：84 ms, 在所有 C++ 提交中击败了66.62%的用户
     * 内存消耗：35.8 MB, 在所有 C++ 提交中击败了5.21%的用户
     */
    int smallestDifference(vector<int>& a, vector<int>& b) {
        if(a.size() > b.size()){
            vector<int> temp = a;
            a = b;
            b = temp;
        }
        sort(a.begin(), a.end());
        long res = 2147483647l;
        int n = a.size();
        for(int num : b){
            if(num <= a[0]) res = min(res, (long)a[0] - num);
            else if(num >= a[n - 1]) res = min(res, (long)num - a[n - 1]);
            else res = min(res, binary_search(a, num));
            if(res == 0) return 0;
        }
        return res;
    }

    // 找到插入的位置，也就是找到大于等于target的最小数
    long binary_search(vector<int>& arr, int target){
        int lo = 0, hi = arr.size() - 1;
        while (lo < hi){
            int mid = (lo + hi) >> 1;
            if(arr[mid] == target) return 0;
            if(arr[mid] < target) lo = mid + 1;
            else hi = mid;
        }
        return min((long)target - arr[lo - 1], (long)arr[lo] - target);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
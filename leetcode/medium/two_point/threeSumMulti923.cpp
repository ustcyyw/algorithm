/**
 * @Time : 2023/3/14-9:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int n = arr.size(), res = 0;
        for(int i = 0; i < n; i++){
            for(int j = i + 1, k = n - 1, cnt = 0; j < n; j++){
                int sum = arr[i] + arr[j];
                cout << arr[i] << "," << arr[j] << endl;
                if(k < j) break;
                if(j == i + 1 || arr[j - 1] != arr[j]){
                    cnt = 0;
                    while (k > j && target - arr[k] <= sum) {
                        if(target - arr[k] == sum) cnt++;
                        k--;
                    }
                }
                res += cnt;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {1,1,2,2,2,2};
    s.threeSumMulti(arr, 5);
    cout << 0 << endl;
}
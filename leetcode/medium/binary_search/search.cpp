/**
 * @Time : 2022/6/14-10:57 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& arr, int target) {
        int index = find_rotate(arr);
        int hi = arr.size() - 1;
        if(index == 0) return binary_search(arr, 0, hi, target);
        int temp = binary_search(arr, 0, index - 1, target);
        return temp == -1 ? binary_search(arr, index, hi, target) : temp;
    }

    int find_rotate(vector<int>& arr){
        int lo = 0, hi = arr.size() - 1;
        while (lo < hi){
            int mid = (lo + hi) >> 1;
            if(arr[mid] < arr[0]) hi = mid;
            else if(arr[mid] > arr[0]) lo = mid + 1;
            else {
                for(int i = lo; i < mid; i++)
                    if(arr[i] > arr[i + 1]) return i + 1;
                lo = mid + 1;
            }
        }
        return lo;
    }

    int binary_search(vector<int>& arr, int lo, int hi, int target){
        while (lo < hi){
            int mid = (lo + hi) >> 1;
            if(arr[mid] >= target) hi = mid;
            else lo = mid + 1;
        }
        return arr[lo] == target ? lo : -1;
    }
};

int main(){
    Solution s;
    vector<int> arr = {2, 1, 2, 2, 2};
    cout << s.search(arr, 2) << endl;
}
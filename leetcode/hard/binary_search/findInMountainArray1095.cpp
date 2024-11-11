/**
 * @Time : 2023/4/1-9:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class MountainArray {
public:
    int get(int index);
    int length();
};

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountain) {
        int n = mountain.length(), top = find_top(mountain, n);
        int t1 = search(mountain, 0, top, target, 1);
        if(t1 != -1) return t1;
        return search(mountain, top + 1, n - 1, target, -1);
    }

    int search(MountainArray &mountain, int lo, int hi, int target, int sign){
        while (lo <= hi){
            int mid = (lo + hi) >> 1;
            int temp = mountain.get(mid);
            if(temp == target) return mid;
            if(temp * sign < target * sign) lo = mid + 1;
            else hi = mid - 1;
        }
        return -1;
    }

    int find_top(MountainArray &mountain, int n){
        int lo = 0, hi = n - 1;
        while (lo < hi){
            int mid = (lo + hi + 1) >> 1;
            if(mountain.get(mid) > mountain.get(mid - 1))
                lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}
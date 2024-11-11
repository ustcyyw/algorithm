/**
 * @Time : 2023/5/30-12:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

class Solution {
public:
    vector<int> ids;
    bool canTraverseAllPairs(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return true;
        ids = vector(2 * N, 0);
        for(int i = 0; i < 2 * N; i++)
            ids[i] = i;
        for(int i = 0; i < n; i++) {
            int num = nums[i];
            if(num == 1) return false;
            connect(num + N, i);
            for(int j = 2; j <= (int)sqrt(num); j++) {
                if(num % j != 0) continue;
                connect(j + N, i), connect(num / j + N, i);
            }
        }
        int id = find(0);
        for(int i = 1; i < n; i++)
            if(id != find(i)) return false;
        return true;
    }

    void connect(int p, int q) {
        ids[find(p)] = ids[find(q)];
    }

    int find(int p) {
        if(p == ids[p]) return p;
        ids[p] = find(ids[p]);
        return ids[p];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
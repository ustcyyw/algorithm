/**
 * @Time : 2024/12/9-10:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3378 数学 数论 调和级数 并查集
 */
 /*
  * 如果一个数大于t, 那么它一定是自己一个连通分量
  * 所以只需要考虑 <= t的数 也就是 2e5以下的数
  * num = 1，其倍数是1 2 3 4 .. n
  * num = 2, 其倍数是2,4,6,8 .. n
  * 针对每个数枚举倍数 调和级数求和
  *
  * 碰到和lcm（或者 gcd）相关的题目，限制又不大（1e6以内）的情况下
  * 通常会试一下枚举 lcm（或者 gcd）
  */
#include<bits/stdc++.h>
using namespace std;

struct UF {
    vector<int> id;
    UF(int total) {
        for(int i = 0; i <= total; i++)
            id.push_back(i);
    }

    int find(int p) {
        return id[p] == p ? p : id[p] = find(id[p]);
    }

    bool connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return true;
        id[p] = q;
        return false;
    }
};

class Solution {
public:
    int countComponents(vector<int>& nums, int threshold) {
        vector<int> arr;
        for(int num : nums) {
            if(num <= threshold)
                arr.push_back(num);
        }
        int n = arr.size();
        UF uf(n + threshold + 1); // 将倍数1到threshold的初始编号当做 j + n
        for(int i = 0; i < n; i++) {
            for(int j = arr[i]; j <= threshold; j += arr[i])
                uf.connect(i, n + j);
        }
        unordered_set<int> set;
        for(int i = 0; i < n; i++)
            set.insert(uf.find(i));
        return set.size() + nums.size() - n;
    }
};
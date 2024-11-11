/**
 * @Time : 2023/7/27-9:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 由于字母可以重排 所以只需要关注每一个字母出现了奇数次还是偶数次
     * 只有两种情况是符合条件的路径：所有字母都出现偶数次；只有一个字母出现了奇数次
     * 并且只会出现小写字母，可以使用一个int变量表示各字母出现次数的状态
     *
     * 假设B C两个结点的路径上经过A点 AB,AC两条子路径的状态分别为s1 s2
     * BC是一条回文路径的条件是 s1 ^ s2 = 0 || bit_count(s1 ^ s2) = 1
     * 两个条件分别等价于s2 = s1
     * s1 ^ s2 = 1 << i, s2 = s1 ^ (1 << i)
     *
     * 枚举结点，查看左右子树的状态情况，时间复杂度超了
     * 但是注意到 两个结点 C D，有最近公共祖先B，根结点假定为A
     * s_ac = s_ab ^ s_bc
     * s_ad = s_ab ^ s_bd
     * s_ac ^ s_ad = s_ab ^ s_bc ^ s_ab ^ s_bd = s_bc ^ s_bd
     * 因此只需要知道从根结点到子结点的路径状态，就能知道子结点之间到lca的路径状态的异或值
     *
     * 找到满足条件
     * s2 = s1 或者 s2 = s1 ^ (1 << i) 的数目且去重 可以用两数之和的类似思路 边遍历边查看前置统计的情况
     */
    long long res = 0;
    long long countPalindromePaths(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> graph(n);
        for(int i = 1; i < n; i++)
            graph[parent[i]].push_back(i);
        unordered_map<int, int> map;
        map[0] = 1; // 根结点的路径状态为0，且出现一次。可以用于找从根出发到某个结点的路径状态
        dfs(graph, map, s, 0, 0);
        return res;
    }

    void dfs(vector<vector<int>>& graph, unordered_map<int, int>& map, string& s, int status, int v) {
        for(int w : graph[v]) {
            int bit = 1 << (s[w] - 'a'), ns = status ^ bit; // 计算出到当前结点的路径状态
            res += map[ns]; // 对应 s1 == s2 的情况
            for(int i = 0; i < 26; i++) // 对应 s2 = s1 ^ (1 << i) 的情况
                res += map[ns ^ (1 << i)];
            map[ns]++;
            dfs(graph, map, s, ns, w);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
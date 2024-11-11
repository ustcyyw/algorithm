/**
 * @Time : 2023/4/24-10:18 PM
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
     * 找连通分量（也就是相同的字母） 然后贪心地优先将小的字母给最先出现的连通分量
     * 使用并查集
     * 给定lcp[i][j] = len 意味着
     * s[i] = s[j], s[i + 1] = s[j + 1] ... s[i + len - 1] = s[j + len - j]
     * 但是 s[i + len] != s[j + len]
     *
     * 注意对于lcp[i][j]，对于所有 j - i = k 可能存在大量的重复相等点对
     * 例如 lcp[1][3] = 7; lcp[3][5] = 5
     * 有5对点对是重复计算。
     * 因此我们从lcp[i][j]确定的区间，从左往右扫一遍，遇到已经连通的就停止
     * 再从右往左扫一遍，遇到已经连通的就停止 避免大量重复计算
     *
     * 另外 要使lcp合法
     * 1. lcp[i][j] = lcp[j][i] 是有对称性的
     * 2. lcp[i][j] = len。右边界 r1 = i + len - 1, r2 = j + len - 1 都要小于 n
     * 3. lcp[i][j] = n - i
     * 4. lcp确定不想等的位置，不能在同一个连通分量
     * 5. 最终并查集中不能有超过26个连通分量，否则小写字母不够用
     */
    vector<int> id;
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size(); // 字符串的长度
        for(int i = 0; i < n; i++)
            id.push_back(i);
        vector<vector<int>> ne; // 表示不相等的位置对
        for(int i = 0; i < n; i++) {
            if(lcp[i][i] != n - i) return "";
            for(int j = i + 1; j < n; j++){
                if(lcp[i][j] != lcp[j][i]) return "";
                int len = lcp[i][j], r1 = i + len - 1, r2 = j + len - 1;
                if(r1 >= n || r2 >= n) return "";
                if(r1 + 1 < n && r2 + 1 < n) ne.push_back({r1 + 1, r2 + 1});
                int t1 = r1, t2 = r2;
                while (t1 >= i && connect(t1, t2)) t1--, t2--;
                t1 = i, t2 = j;
                while (t1 <= r1 && connect(t1, t2)) t1++, t2++;
            }
        }
        for(auto& pair : ne) {
            if(find(pair[0]) == find(pair[1]))
                return "";
        }
        unordered_map<int, vector<int>> map;
        for(int i = 0; i < n; i++) {
            int p = find(i);
            if(!map.count(p)) map[p] = {};
            map[p].push_back(i);
        }
        if(map.size() > 26) return "";
        string res(n, '.');
        for(int i = 0, j = 0; i < n; i++){
            if(res[i] != '.') continue;
            char c = (char)(j++ + 'a');
            for(int index : map[find(i)])
                res[index] = c;
        }
        return res;
    }

    int find(int p){
        if(id[p] == p) return p;
        id[p] = find(id[p]);
        return id[p];
    }

    // 如果已经连通了 则返回false；否则将两个点连通，返回true
    bool connect(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return false;
        id[p] = q;
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
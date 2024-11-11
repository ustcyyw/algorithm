/**
 * @Time : 2022/12/28-9:17 PM
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
     * 类型3的边，两个人都可以走。
     * 如果某一条类型3的边，连接了a和b两个点，将其去掉后a和b不再连通
     * 在这种情况下，要使用类型1和2，使bob和alice能够连通a和b，就需要两条边
     * 也就是说保留类型3的边，能尽可能多得删除边。
     * 因此我们先对类型3的边进行讨论，扣除冗余的类型3的边后，再考虑如何分别让bob和alice连通
     * 冗余边，可以通过并查集来找，某条边的两个点已经是在同一个连通分量中，就说明该边冗余
     *
     * 在类型3连接起的骨架上，再看两个人分别有哪些边冗余
     * 最后 还要检查对于两个人是否能得到完整的连通图，也就是检查所有点是否在同一个连通分量（id都相同）
     */
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        vector<vector<int>> type1, type2, type3;
        for(vector<int>& edge : edges){
            int type = edge[0];
            if(type == 1) type1.push_back(edge);
            if(type == 2) type2.push_back(edge);
            if(type == 3) type3.push_back(edge);
        }
        vector<int> id;
        for(int i = 0; i <= n; i++)
            id.push_back(i);
        int res = count_dege(id, type3);
        vector<int> id1 = id, id2 = id;
        res += count_dege(id1, type1) + count_dege(id2, type2);
        if(!check(id1) || !check(id2)) return -1;
        return res;
    }

    int count_dege(vector<int>& id, vector<vector<int>>& edges){
        int res = 0;
        for(auto& edge : edges){
            int v = edge[1], w = edge[2];
            if(connect(id, v, w)) res++;
        }
        return res;
    }

    bool check(vector<int>& id){
        int t = find(id, id[1]);
        for(int i = 2; i < id.size(); i++)
            if(t != find(id, i)) return false;
        return true;
    }

    int find(vector<int>& id, int p){
        if(id[p] == p) return p;
        id[p] = find(id, id[p]);
        return id[p];
    }
    // 已经连接了 就返回true
    bool connect(vector<int>& id, int p, int q){
        p = find(id, p), q = find(id, q);
        if(p == q) return true;
        id[p] = q;
        return false;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
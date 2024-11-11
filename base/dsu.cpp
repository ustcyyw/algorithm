/**
 * @Time : 2024/1/25-3:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 并查集
 */
#include<bits/stdc++.h>
using namespace std;

struct UF {
    int cnt; // 连通分量数
    vector<int> id;
    UF(int n) {
        this->id = vector(n, 0);
        for(int i = 0; i < n; i++)
            id[i] = i;
        this->cnt = 0;
    }

    int find(int p) {
        if(id[p] == p) return p;
        return id[p] = find(id[p]);
    }

    void connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return;
        cnt--;
        id[p] = q;
    }
};

/*
 * 合并两个并查集
 * 只有在同一场景下 结点数目相同的并查集合并才有意义
 * 相当于连接操作先分为两个部分进行 最后再合到一块 得到最终连通状态
 */
void merge(UF& uf1, UF& uf2) {
    int n = uf1.cnt;
    for(int i = 0; i < n; i++) {
        int p = uf1.find(i), q = uf2.find(i);
        if(p != q) uf1.connect(p, q);
    }
}
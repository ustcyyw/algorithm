/**
 * @Time : 2023/5/4-3:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
};

class LockingTree {
public:
    int n;
    vector<int> parent, marked;
    vector<vector<int>> tree;
    LockingTree(vector<int>& parent) {
        this->n = parent.size();
        this->parent = parent;
        marked = vector(n, 0);
        tree = vector(n, vector(0, 0));
        for(int i = 1; i < n; i++)
            tree[parent[i]].push_back(i);
    }

    bool lock(int num, int user) {
        if(marked[num] != 0) return false;
        marked[num] = user;
        return true;
    }

    bool unlock(int num, int user) {
        if(marked[num] != user) return false;
        marked[num] = 0;
        return true;
    }

    bool upgrade(int num, int user) {
        if(marked[num] != 0) return false;
        if(!check_father(num)) return false;
        if(check_son(num)) {
            marked[num] = user;
            return true;
        }
        return false;
    }
    // 检查父节点是否有上锁的 没有则返回true
    bool check_father(int id) {
        if(id == -1) return true;
        if(marked[id] != 0) return false;
        return check_father(parent[id]);
    }
    // 检查子孙结点是否有上锁的 如果有 都解锁并且返回true
    bool check_son(int id) {
        bool ans = marked[id] != 0;
        marked[id] = 0;
        for(int son : tree[id])
            ans |= check_son(son);
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}
/**
 * @Time : 2023/10/19-3:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * rj = ai * aj
 * 是ai定义了aj中元素的排列顺序
 * 而美丽值是从1开始的连续序列
 * 所以要找rj的美丽值 可以将aj的元素带着下标排列
 * 如果ai规定的顺序 刚好和aj排序得到的下标序列的前k个一致。
 * 就说明按ai定义的顺序 可以得到1到k的连续序列 但k+1没能接上 因此美丽值为k
 *
 * 要找ai * aj的最大美丽值 就看看对于所有aj排序得到的下标序列 和ai的最长公共前缀
 */
#include<bits/stdc++.h>
using namespace std;

struct node {
    node* next[10];
};

int T, n, m;
vector<vector<int>> nums;
node* root;

node* insert(node* x, vector<int>& order, int i) {
    if(x == nullptr) x = new node();
    if(i == m) return x;
    x->next[order[i]] = insert(x->next[order[i]], order, i + 1);
    return x;
}

void insert(vector<int>& arr) {
    vector<int> order(m, 0); // order记录0～m-1在arr中的位置
    for(int i = 0; i < m; i++)
        order[arr[i]] = i;
    root = insert(root, order, 0);
}

// 用arr来定义顺序 查询最长前缀
int search(node* x, vector<int>& arr, int i) {
    if(x == nullptr) return 0;
    if(i == m) return 1;
    return 1 + search(x->next[arr[i]], arr, i + 1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    for(int t = 0; t < T; t++) {
        root = nullptr;
        cin >> n >> m;
        nums = vector(n, vector(m, 0));
        for(int i = 0; i < n; i++) {
            for(int j = 0, num; j < m; j++) {
                cin >> num;
                nums[i][j] = num - 1;
            }
            insert(nums[i]);
        }
        for(int i = 0; i < n; i++) {
            cout << search(root, nums[i], 0) - 1 << " ";
        }
        cout << "\n";
    }
}
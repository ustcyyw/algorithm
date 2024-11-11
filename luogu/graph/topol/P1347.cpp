/**
 * @Time : 2023/5/6-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */

/*
 * 修改floyd算法 用于表示递推关系
 * 本题进行动态加边
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 27;
int n, m, rel[N][N];

// rel[i][j] = 1 表示 i < j
void relax(int v, int w) {
    if(rel[v][w]) return;
    rel[v][w] = true;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            rel[i][j] = rel[i][j] || (rel[i][v] && rel[w][j]);
    }
}

string check() {
    string ans(n, '.');
    for(int i = 0; i < n; i++) {
        int n1 = 0, n2 = 0;
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            if(rel[i][j] && rel[j][i]) return "-1";
            if(rel[i][j]) n2++;
            else if(rel[j][i]) n1++;
        }
        if(n1 + n2 == n - 1) ans[n1] = (char)(i + 'A');
    }
    for(int i = 0; i < n; i++)
        if(ans[i] == '.') return "0";
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    memset(rel, 0, sizeof(rel));
    for(int i = 0; i < n; i++)
        rel[i][i] = 1;
    char x, t, y;
    for(int i = 1; i <= m; i++){
        cin >> x >> t >> y;
        if(x == y) {
            printf("Inconsistency found after %d relations.", i);
            return 0;
        }
        relax(x - 'A', y - 'A');
        string msg = check();
        if(msg != "0") {
            if(msg == "-1") printf("Inconsistency found after %d relations.", i);
            else printf("Sorted sequence determined after %d relations: %s.", i, msg.c_str());
            return 0;
        }
    }
    printf("Sorted sequence cannot be determined.");
}
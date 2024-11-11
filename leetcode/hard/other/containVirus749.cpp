/**
 * @Time : 2023/3/18-2:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};
struct areaInfo{
    int cnt = 0; // 表示断绝此感染区的需要隔板
    unordered_set<int> next; // 表示威胁的区域
    unordered_set<int> infected; // 表示已经被感染的区域
};
class Solution {
public:
    int n, m;
    vector<vector<int>> grid; // 0表示未感染，1表示感染且未隔离，2表示感染且被隔离
    int containVirus(vector<vector<int>>& isInfected) {
        grid = isInfected;
        n = grid.size(), m = grid[0].size();
        int res = 0;
        while (true){
            vector<areaInfo> infos = findInfectedArea();
            if(infos.empty()) break;
            res += infos[0].cnt;
            // 隔离 设置该区域标识为2
            changeStatus(infos[0].infected, 2);
            // 其它感染区进行感染
            for(int i = 1; i < infos.size(); i++)
                changeStatus(infos[i].next, 1);
        }
        return res;
    }

    void changeStatus(unordered_set<int> area, int flag){
        for(int key : area)
            grid[key / 100][key % 100] = flag;
    }

    vector<areaInfo> findInfectedArea(){
        vector<areaInfo> res;
        unordered_set<int> marked;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == 1 && !marked.count(get_key(i, j))){
                    areaInfo info;
                    dfs(marked,i, j, info);
                    res.push_back(info);
                }
            }
        }
        // 按威胁区域的大小降序排序
        sort(res.begin(), res.end(),
             [](areaInfo& a, areaInfo& b) -> bool {return a.next.size() > b.next.size();});
        return res;
    }

    void dfs(unordered_set<int>& marked, int x, int y, areaInfo& info){
        marked.insert(get_key(x, y));
        info.infected.insert(get_key(x, y));
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m || marked.count(get_key(nx, ny))) continue;
            if(grid[nx][ny] == 0) {
                info.next.insert(get_key(nx, ny));
                info.cnt++;
            }
            else if(grid[nx][ny] == 1) dfs(marked,nx, ny, info);
        }
    }

    int get_key(int x, int y){
        return x * 100 + y;
    }
};

int main(){
    Solution s;
    vector<vector<int>> grid = {{0,0,0},{0,1,0},{0,0,0}};
    s.containVirus(grid);
    cout << 0 << endl;
}
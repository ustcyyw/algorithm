/**
 * @Time : 2023/3/1-7:43 PM
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
     * 如果某一列上的字符，存在排序错误，那这一列一定要删除
     *
     * 如果前一列的字符已经比出大小了，那么当前列就不应该在比较，只应该在上一列相等的字符串内部进行比较
     * 因此每一列的比较，都要将能区分大小的字符串分到不同组，每个组里面都是当前列还不能比较大小的
     */
    int minDeletionSize(vector<string>& strs) {
        vector<int> temp;
        vector<vector<int>> groups;
        for(int i = 0; i < strs.size(); i++)
            temp.push_back(i);
        groups.push_back(temp);
        int n = strs[0].size(), res = 0;
        for(int i = 0; i < n; i++){
            if(!check(groups, strs, i)) res++;
            // 每个字符串单独一个组，说明全部比较出了大小，并且符合升序要求
            if(groups.size() == strs.size()) return res;
        }
        return res;
    }

    bool check(vector<vector<int>>& groups, vector<string>& strs, int i){
        vector<vector<int>> aux;
        for(auto& group : groups){
            if(!check(aux, group, strs, i))
                return false;
        }
        swap(groups, aux);
        return true;
    }

    bool check(vector<vector<int>>& aux, vector<int>& group, vector<string>& strs, int j){
        vector<int> ng;
        ng.push_back(group[0]);
        for(int i = 1, pre = strs[group[0]][j]; i < group.size(); i++){
            if(strs[group[i - 1]][j] > strs[group[i]][j])
                return false;
            if(strs[group[i]][j] == pre) ng.push_back(group[i]);
            else {
                pre = strs[group[i]][j];
                aux.emplace_back(ng);
                ng.clear();
                ng.push_back(group[i]);
            }
        }
        aux.push_back(ng);
        return true;
    }
};

int main(){
    Solution s;
    vector<string> arr = {"ca","bb","ac"};
    cout << s.minDeletionSize(arr) << endl;
}
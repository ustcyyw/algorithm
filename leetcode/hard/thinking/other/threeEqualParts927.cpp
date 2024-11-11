/**
 * @Time : 2022/11/8-10:02 AM
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
     * 首先统计arr中1的个数，如果为0，那么任意非空的分割都可以
     * 如果个数不能3等分，那么一定没法表示成3部分
     * 在可以三等分的情况下，找到三个部分的第一个1（因为前导0不影响所表示的数），分别是指针i j k
     * 然后i j k逐步右移动，要每一步都相等。如果某一步不相等，就说明表示的数不一样，也就没法分成三部分了
     * 直到k移动到n，此时可以保证完成能分割成三部分
     *
     * 接下来就是确定切割点
     * 第三部分的后缀0的数量，唯一地确定了前两部分后缀0的数量
     * 找到每一个部分最后一个1，再加上后缀0的长度，就是该部分的右端点的索引
     */
    vector<int> threeEqualParts(vector<int>& arr) {
        int cnt = accumulate(arr.begin(), arr.end(), 0);
        if(cnt == 0) return {0, 2};
        if(cnt % 3 != 0) return {-1, -1};
        vector<int> start = find_start(arr, cnt / 3);
        int n = arr.size(), i = start[0], j = start[1], k = start[2];
        while (k < n){
            if(arr[i] != arr[j] || arr[j] != arr[k]) return {-1, -1};
            i++, j++, k++;
        }
        vector<int> end = find_end(arr, cnt / 3);
        int m = n - end[2] - 1;
        return {end[0] + m, end[1] + m + 1}; // 注意区间划分
    }

    vector<int> find_start(vector<int>& arr, int cnt){
        vector<int> res;
        for(int i = arr.size() - 1, sum = 0; res.size() < 3; i--){
            sum += arr[i];
            if(arr[i] == 1 && sum % cnt == 0) res.push_back(i);
        }
        reverse(res.begin(), res.end());
        return res;
    }

    vector<int> find_end(vector<int>& arr, int cnt){
        vector<int> res;
        for(int i = 0, sum = 0; res.size() < 3; i++){
            sum += arr[i];
            if(arr[i] == 1 && sum % cnt == 0) res.push_back(i);
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {1,0,1,0,1};
    s.threeEqualParts(arr);
    cout << 0 << endl;
}
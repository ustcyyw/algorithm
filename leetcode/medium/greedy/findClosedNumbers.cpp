/**
 * @Time : 2022/6/3-11:42 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findClosedNumbers(int num) {
        vector<int> res = vector(2, -1);
        res[0] = get_higher(num);
        res[1] = get_lower(num);
        return res;
    }

    int get_higher(int num){
        bitset<32> set(num);
        // 找到第一个前面是0的1，交换，然后将该元素右边的1尽可能放置在后面
        for(int i = 0; i < 30; i++){ // 特别注意这个30。因为第32位数（索引31）是符号位，所以只应该检查到i+1=30这个二进制位
            if(set[i] == 1 && set[i + 1] == 0){
                change(set, i, i + 1);
                for(int lo = 0, hi = 0; hi < i; hi++){
                    int temp = set[hi];
                    set[hi] = 0;
                    if(temp) set[lo++] = 1;
                }
                break;
            }
        }
        int res = (int)set.to_ulong();
        return num == res ? -1 : res;
    }

    int get_lower(int num){
        bitset<32> set(num);
        // 找到第一个后面是0的1，交换，然后将该0右边的1尽可能放置在前面
        for(int i = 1; i < 31; i++){
            if(set[i] == 1 && set[i - 1] == 0){
                change(set, i, i - 1);
                for(int lo = i - 2, hi = i - 2; hi >= 0; hi--){
                    int temp = set[hi];
                    set[hi] = 0;
                    if(temp) set[lo--] = 1;
                }
                break;
            }
        }
        int res = (int)set.to_ulong();
        return num == res ? -1 : res;
    }

    void change(bitset<32>& set, int i, int j){
        set[i] = set[i] == 0 ? 1 : 0;
        set[j] = set[j] == 0 ? 1 : 0;
    }
};

int main(){
    Solution s;
    s.findClosedNumbers(2147483646);
}
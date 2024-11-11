/**
 * @Time : 2023/4/1-9:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        int n = 0, sum = 0, min_val = -1, max_val = -1, mode = -1, time = 0;
        vector<int> aux; // 记录出现过的数字
        for(int i = 0; i < count.size(); i++){
            sum += i * count[i];
            n += count[i];
            if(count[i]){
                aux.push_back(i);
                max_val = i;
                if(min_val == -1) min_val = i;
                if(count[i] > time) {
                    time = count[i];
                    mode = i;
                }
            }
        }
        double median = 0.0;
        for(int i = 0, temp = 0, t = (n + 1) / 2; i < aux.size(); i++){
            temp += count[aux[i]];
            if(temp >= t) {
                if(n % 2 == 1) median = aux[i];
                else {
                    if(temp == t) median = (aux[i] + aux[i + 1]) * 1.0 / 2;
                    else median = aux[i];
                }
                break;
            }
        }
        return {(double)min_val, (double)max_val, sum * 1.0 / n, median, (double)mode};
    }
};

int main(){
    Solution s;
    vector<int> arr = {0,1,3,4,0};
    s.sampleStats(arr);
    cout << 0 << endl;
}
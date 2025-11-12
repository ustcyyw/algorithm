/**
 * @Time : 2023/5/18-1:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

string arr_to_string(vector<int>& arr) {
    string res = "";
    for(int i = 0, n = arr.size(); i < arr.size(); i++){
        res += to_string(arr[i]);
        if(i != n -1) res += " ";
    }
    return res;
}

void test() {
    // 输出 long double 类型并保留10位小数
    long double num = 123.4567890123456789L;
    printf("%.10Lf\n", num);
}

int main(){

    cout << 0 << endl;
}
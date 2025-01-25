#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int MOD = 1e9 + 7;
 
typedef vector<vector<ll>> matrix;
 
matrix multiply(const matrix &a, const matrix &b) {
    matrix res(6, vector<ll>(6, 0));
    for(int i=0;i<6;i++) {
        for(int k=0;k<6;k++) {
            if(a[i][k]==0) continue;
            for(int j=0;j<6;j++) {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return res;
}
 
matrix power_matrix(matrix a, ll power) {
    matrix result(6, vector<ll>(6, 0));
    for(int i=0;i<6;i++) {
        result[i][i] = 1;
    }
    while(power > 0) {
        if(power & 1) {
            result = multiply(result, a);
        }
        a = multiply(a, a);
        power >>=1;
    }
    return result;
}
 
int main(){
    ll n;
    cin >> n;
 
    if(n ==0){
        cout << 1;
        return 0;
    }
    if(n ==1){
        cout << 1;
        return 0;
    }
    if(n ==2){
        cout << 2;
        return 0;
    }
    if(n ==3){
        cout << 4;
        return 0;
    }
    if(n ==4){
        cout << 8;
        return 0;
    }
    if(n ==5){
        cout << 16;
        return 0;
    }
    if(n ==6){
        cout << 32;
        return 0;
    }
 
    matrix T(6, vector<ll>(6, 0));
    for(int j=0;j<6;j++) T[0][j] =1;
    for(int i=1;i<6;i++) {
        T[i][i-1] =1;
    }
 
    matrix T_n = power_matrix(T, n-6);
 
    vector<ll> initial = {32,16,8,4,2,1};
 
    ll f_n =0;
    for(int j=0;j<6;j++) {
        f_n = (f_n + T_n[0][j] * initial[j]) % MOD;
    }
 
    cout << f_n;
}

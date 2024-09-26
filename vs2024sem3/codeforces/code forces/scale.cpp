#include <bits/stdc++.h>
using namespace std;
#include <algorithm> 
#define ll long long 
using namespace std;
#define pb push_back
#define mod 1000000007
int main (){
//your code
ll t ; cin>>t;
while (t--){
    ll n , k;
    cin>>n>>k;
    ll orignal_arr [n][n];
    for(int i = 0 ; i<n; i++){
         for(int j = 0 ; j<n; j++){
        cin>>orignal_arr[i][j];
    }
    cout<<endl;
    }
    int s = n/k;
    for(int i = 0 ; i<n; i++){
         for(int j = 0 ; j<s; j++){
        cout<<orignal_arr[i][j];
    }
    cout<<endl;
    }
}
    return 0;
}
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
    int aar[n];
    bool baba=0;
    for (int i=0 ; i<n ; i++){
        cin>>aar[i];
        if(i>0) if(aar[i]<aar[i-1]) baba=1;
    }
    if(k==1 && baba==1) cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
}
    return 0;
}
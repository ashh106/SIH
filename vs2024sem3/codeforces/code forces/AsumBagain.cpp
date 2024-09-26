#include <bits/stdc++.h>
using namespace std;
#include <algorithm> 
#define ll long long 
using namespace std;
#define pb push_back
#define mod 1000000007
int main (){
    long long t ;
    cin>>t;
while (t--){
ll n ; cin>>n;
ll sum = 0;
 while(n!=0){
   
sum = n%10 +sum;
 n = n/10;
}

cout<<sum<<endl;
}
    return 0;
}
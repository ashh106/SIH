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
    // n - counted legs
long long n; //even
cin>>n;
 if (n%4 ==0){
    cout<<n/4<<endl;
 }
 else if (n%4 == 2) {
    cout<<(n/4)+1<<endl;
 }
}
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#include <algorithm> 
#define ll long long 
using namespace std;
#define pb push_back
#define mod 1000000007
int main (){
   //group of n fighters Ai ....An
   //n-1 battles
   //i , j 
   int t ;
   cin>>t;
   while (t--){
      ll sum = 0;
     ll n, sol; // no of fighters
     cin>>n;
     ll arr[n];
     for (ll i =  0 ; i < n  ; i++ ){//rating of fighters
         cin>>arr[i];       
   }
         for (ll i=0 ; i<n-2 ; i++ ){
            sum = sum + arr[i];
         }
         ll a = arr[n-2] - sum ;
         sol =  arr[n-1]-a;
      cout<<sol<<endl;  
}
}



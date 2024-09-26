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
    ll a1 , a2 , b1 , b2 ;
    cin>>a1>>a2>>b1>>b2;
    int count = 0;
    if (a1>b1 && a1>b2){
        count++;
    }
    if (a2>b1 && a2>b2){
        count++;
    }
       
         if (a2>b2 && a1>b2){
        count++;
    }

       if (a2>b2 && a1>b2){
        count++;
    }

         if (a2==b2 && a1>b2){
        count++;
    }
         if (a2>b2 && a1==b2){
        count++;
    }

             if (a2==b2 && a1>b2){
        count++;
    }

             if (a2>b2 && a1==b2){
        count++;
    }
      if (a2==b1 && a2>b2){
        count++;
    }
      if (a2>b1 && a2==b2){
        count++;
    }
      if (a1==b1 && a1>b2){
        count++;
    }
  if (a1>b1 && a1==b2){
        count++;
    }

    cout<<count<<endl;
}
    return 0;
}
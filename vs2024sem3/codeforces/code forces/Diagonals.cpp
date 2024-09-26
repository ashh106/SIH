#include<iostream>
using namespace std;
int main (){
    int t ; cin>>t;
    //when lc ==0 , lc = 3 
while (t--){
    int n ,k ;
    cin>>n>>k;
      if (k==0){
        cout<<0<<endl;
    }
    else if (k<=n){
        cout<<1<<endl;
    }
    else{
          int i = 0;
    while(k>0){
        k=k-(n-i);
        i++;
    }
    cout<<2*i<<endl;
    }
    }
    return 0 ;
}
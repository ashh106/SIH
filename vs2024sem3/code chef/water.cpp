// #include<bits/stdc++.h>
// using namespace std;
// int main (){
//     int t ; cin>>t;
//     while(t--){
//         int x ; cin>>x;
//         if (x>=2000){
//             cout<<"yes"<<endl;
//         }
//         else {
//             cout<<"no"<<endl;
//         }
//     }
//     return 0;
// }

// #include<bits/stdc++.h>
// using namespace std;
// int main() {
// 	int t ; cin>>t;
// 	while (t--){
//         int max;
// 	    int n ; cin>>n ;
// 	    int arr[n];
// 	    for (int i = 0 ; i < n ; i++){
// 	        cin>>arr[i];
// 	    }
//         max = arr[0];
//    for (int i = 0 ; i < n ; i++){
//             if (arr[i]>max){
//                 max = arr[i];
//             }
//    }
//           cout<<max<<endl;
// 	}

// }



#include<bits/stdc++.h>
using namespace std;
int main() {
	int t ; cin>>t;
	while (t--){
        int n ; cin>>n;
      string x;
    cin>>x;
    string a ;
    string b ;
    for ( int i = 0 ; i <  n/2 ; i++){
        a = a + x[i];
    }
    for(int i = n/2; i<n ; i++){
        b = b + x[i];
    }
    for(int i=0;i<n;i++){
    cout << a[i] << endl;
    }
	}
}

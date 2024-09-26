#include <bits/stdc++.h>
using namespace std;
#include <algorithm> 
#define ll long long 
using namespace std;
#define pb push_back
#define mod 1000000007
int main() {
    int t;
    cin >> t;
    string v = "aeiou";
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cout << v[i % 5];
        }
        cout << endl;
    }
    return 0;
}



#include<bits/stdc++.h>
using namespace std ;
using  vint= vector<int> ;
#define  mod 1000000007 ;
#define  Pi 3.1415926535897932384626433832795 ;
#define all(v) v.begin(), v.end()
#define forr(a, b, c) for (long long(a) = (b); (a) < (c); ++(a))
#define for2(a,b,c) for (long long(a) = (b); (a) < (c); (a)+=2)
#define ford(a, b, c) for (long long(a) = (b); (a) >= (c); --(a))
using  vll =vector<long long> ;
using  ll =long long int ;
using  vc =vector<char>;
using  vs =vector<string> ;
#define  ff first ;
#define  ss second ;
using  pii= pair<int,int> ;
using  vvint= vector<vector<int>> ;
using  vvl =vector<vector<long long>> ;
using  ulli =unsigned long long int ;
using umii= unordered_map<int,int> ;
using umcc = unordered_map<char,char> ;
using umci=unordered_map<char,int> ;
using mii= map<int,int> ;
using mcc=map<char,char> ;
using mci=map<char,int> ;
using usint=unordered_set<int> ;
using sint= set<int> ;
using uscar=unordered_set<char> ;
using scar=set<char> ;

void fastio()
{
 ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}
void solve()
{
    ll n ;cin>>n ;
    ll s=n*(n+1)/2 ;
    if(s%2)
    {
        cout<<"NO"<<endl ;return ;
    }
    else
    {
        cout<<"YES"<<endl;

            if(n%2)
            {
                cout<<n/2<<endl ;
                cout<<n<<" " ;
                for2(i,2,n/2)cout<<i<<" "<<n-i<<" " ;cout<<endl ;
                cout<<(n+1)/2<<endl ;
                for2(i,1,n/2+1)cout<<i<<" "<<n-i<<" " ;cout<<endl ;


            }

            else
            {
                cout<<(n+1)/2<<endl ;
                cout<<n<<" "<<1<<" " ;
                for2(i,3,n/2)cout<<i<<" "<<n-i+1<<" " ;cout<<endl ;
                cout<<n/2<<endl ;
                for2(i,2,n/2+1)cout<<i<<" "<<n-i+1<<" " ;cout<<endl ;
            }

    }
return ;

}

int main()
{
    fastio() ;
    int t=1;
    //cin>>t ;
    while(t--)
    {
        solve() ;
    }
}

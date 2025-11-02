#include<bits/stdc++.h>
using namespace std ;
using  vint= vector<int> ;
#define  mod 1000000007 ;
#define  Pi 3.1415926535897932384626433832795 ;
#define all(v) v.begin(), v.end()
#define forr(a, b, c) for (int(a) = (b); (a) < (c); ++(a))
#define ford(a, b, c) for (int(a) = (b); (a) >= (c); --(a))
#define for2(a, b, c) for (int(a) = (b); (a) >= (c); (a)+=2)
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
using umll= unordered_map<long long int,long long int> ;
using umcc = unordered_map<char,char> ;
using umci=unordered_map<char,int> ;
using umcll=unordered_map<char,long long> ;
using mii= map<int,int> ;
using mcc=map<char,char> ;
using mci=map<char,int> ;
using usint=unordered_set<int> ;
using sint= set<int> ;
using uscar=unordered_set<char> ;
using scar=set<char> ;
ll fact(ll n)
{
    if(n<2)return 1 ;
    if(n==2)return 2 ;
    return n*fact(n-1);
}
void fastio()
{
 ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void gen(int cs,int ts,mci mp,string s)
{
    if(cs>=ts)
    {
        //out<<911<<endl ;
        cout<<s<<endl ;return ;
    }
    for(auto it=mp.begin();it!=mp.end();++it)
    {
        //cout<<911<<endl ;
        if(mp[it->first]>0)
            {
                //cout<<911<<endl ;
            char ch=it->first ;
        mp[ch]-=1 ;
        gen(cs+1,ts,mp,s+ch) ;
        mp[ch]+=1 ;
            }
           // cout<<911<<endl ;
    }
    return ;
}

void solve()
{
    string s ;cin>>s ;
    int n=s.size();
    mci mp ;
    forr(i,0,n)mp[s[i]]++ ;
    ll k=fact(n) ;
    for(auto it=mp.begin();it!=mp.end();++it)
    {
        k/=fact(it->second) ;
    }

    cout<<k<<endl ;
    gen(0,n,mp,"") ;
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


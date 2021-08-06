#include<bits/stdc++.h>
using namespace std ;
using  vint= vector<int> ;
#define  mod 1000000007 ;
#define  Pi 3.1415926535897932384626433832795 ;
#define all(v) v.begin(), v.end()
#define forr(a, b, c) for (int(a) = (b); (a) < (c); ++(a))
#define ford(a, b, c) for (int(a) = (b); (a) >= (c); --(a))
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
    string s ;
    cin>>s ;
    mci mp ;
    int n=s.size() ;
    forr(i,0,n)mp[s[i]]++ ;
    int cnt=0 ;
    for(auto it=mp.begin(); it!=mp.end(); ++it)
    {
        if(it->second%2)cnt++ ;
    }
    if(cnt>1){cout<<"NO SOLUTION"<<endl ;return ;}
    else
    {
        ///cout<<"here1"<<endl;
        string ans="" ;
        char c ;
        for(auto it=mp.begin(); it!=mp.end(); ++it)
        {
           /// cout<<"here2"<<endl;
            int freq=it->second ;
            if(freq%2)c=it->ff ;
            if((freq%2)==0)
            {
               /// cout<<"here3"<<endl;
                for(int i=0 ; i<(freq)/2; i++)
                {
                    ///<<"here4"<<endl;
                    ans+=it->first ;
                }
            }

        }
       /// cout<<mp.size()<<endl ;
        if(cnt==1)
        {
                //cout<<"here5"<<endl;
                int freq=mp[c] ;
                for(int i=0 ;i<freq/2;i++)
                {
                    //cout<<"here6"<<endl;
                    ans+=c ;
                }

            string hans=ans ;
            reverse( all(hans) ) ;
            ans=ans+c+hans ;
            cout<<ans<<endl ;
            return ;
        }
        string hans=ans ;
            reverse( all(hans) ) ;
            ans=ans+hans ;
        cout<<ans<<endl ;return ;

    }

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

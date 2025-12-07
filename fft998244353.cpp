#include <bits/stdc++.h>
#define LL_INF 9223372036854775807
#define INT_INF 2147483647
using namespace std;
using ll = long long;

struct ntt{
  ll mod=998244353;
  vector<ll> root,invroot;
  //root[i] := 2^i乗根

  ntt(){
    root.resize(24);
    invroot.resize(24);
    root[23]=powmod(3LL,119LL);
    for(int i=22;i>=0;i--){
      root[i]=(root[i+1]*root[i+1])%mod;
    }
    for(int i=0;i<24;i++){
      invroot[i]=powmod(root[i],mod-2);
    }
  }

  ll powmod(ll a,ll b){
    //a^b
    if(b==0)return 1;
    if(b==1)return a;
    ll ans=1;
    if(b%2==1){
      ans*=a;
    }
    b/=2;
    ll num=powmod(a,b);
    ans*=num;
    ans%=mod;
    ans*=num;
    ans%=mod;
    return ans;
  }

  void fft(vector<ll> &v,int l,int r){
    // l<=i<r
    ll n=r-l;
    if(n==1)return;
    ll num=1;
    ll cnt=0;
    while(num<n){
      num=num<<1;
      cnt++;
    }
    vector<ll> memo(n);
    for(int i=0;i<n;i++)memo[i]=v[l+i];
    for(int i=0;i<n/2;i++){
      v[l+i]=(memo[i]+memo[i+n/2])%mod;
    }
    for(int i=0;i<n/2;i++){
      v[l+n/2+i]=(((memo[i]-memo[i+n/2])%mod)+mod)%mod;
      v[l+n/2+i]=(v[l+n/2+i]*powmod(root[cnt],i))%mod;
    }
    fft(v,l,l+n/2);
    fft(v,l+n/2,r);
    for(int i=0;i<n;i++)memo[i]=v[l+i];
    for(int i=0;i<n;i+=2)v[l+i]=memo[i/2];
    for(int i=1;i<n;i+=2)v[l+i]=memo[n/2+i/2];
    return;
  }

  void invfft(vector<ll> &v,int l,int r){
    ll n=r-l;
    if(n==1)return;
    ll num=1;
    ll cnt=0;
    while(num<n){
      num=num<<1;
      cnt++;
    }
    vector<ll> memo(n);
    for(int i=0;i<n;i++)memo[i]=(v[l+i]*499122177)%mod;
    for(int i=0;i<n/2;i++){
      v[l+i]=(memo[i]+memo[i+n/2])%mod;
    }
    for(int i=0;i<n/2;i++){
      v[l+n/2+i]=(((memo[i]-memo[i+n/2])%mod)+mod)%mod;
      v[l+n/2+i]=(v[l+n/2+i]*powmod(invroot[cnt],i))%mod;
    }
    invfft(v,l,l+n/2);
    invfft(v,l+n/2,r);
    for(int i=0;i<n;i++)memo[i]=v[l+i];
    for(int i=0;i<n;i+=2)v[l+i]=memo[i/2];
    for(int i=1;i<n;i+=2)v[l+i]=memo[n/2+i/2];
  }

  vector<ll> convolution(vector<ll> a,vector<ll> b){
    ll num=(a.size()+b.size());
    ll n=1;
    while(n<num)n=n<<1;;
    a.resize(n,0);
    b.resize(n,0);
    fft(a,0,n);
    fft(b,0,n);
    for(ll i=0;i<n;i++){
      b[i]=(a[i]*b[i])%mod;
    }
    invfft(b,0,n);
    b.resize(num-1);
    return b;
  }
};

int main(){
  cout << setprecision(20);
  ll CNT=1;
  int n,m;
  cin >> n >> m;
  vector<ll> v(n),w(m);
  for(int i=0;i<n;i++)cin >> v[i];
  for(int i=0;i<m;i++)cin >> w[i];
  ntt nt;
  for(ll i=0;i<CNT;i++){
    v=nt.convolution(v,w);
  }
  for(auto p:v)cout << p << " ";
  cout << endl;
}

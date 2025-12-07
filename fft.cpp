#include <bits/stdc++.h>
#define LL_INF 9223372036854775807
#define INT_INF 2147483647
using namespace std;
using ll = long long;

vector<complex<double>> fft(vector<complex<double>> v){
  if(v.size()==1)return v;
  int num=1;
  while(num<v.size())num*=2;
  while(v.size()!=num)v.push_back(0);
  vector<complex<double>> odd,even;
  for(int i=0;i<num/2;i++)even.push_back(v[i]+v[num/2+i]);
  for(int i=0;i<num/2;i++)odd.push_back((v[i]-v[num/2+i])*(polar(1.0,-2*M_PI*i/num)));
  even=fft(even);
  odd=fft(odd);
  for(int i=0;i<num/2;i++)v[i*2]=even[i];
  for(int i=0;i<num/2;i++)v[i*2+1]=odd[i];
  return v;
}

vector<complex<double>> invfft(vector<complex<double>> v){
  if(v.size()==1)return v;
  int num=1;
  while(num<v.size())num*=2;
  while(v.size()!=num)v.push_back(0);
  vector<complex<double>> odd,even;
  for(int i=0;i<num/2;i++)even.push_back(v[i]+v[num/2+i]);
  for(int i=0;i<num/2;i++)odd.push_back((v[i]-v[num/2+i])*(polar(1.0,2*M_PI*i/num)));
  even=invfft(even);
  odd=invfft(odd);
  for(int i=0;i<num/2;i++)v[i*2]=even[i]/complex<double>(2,0);
  for(int i=0;i<num/2;i++)v[i*2+1]=odd[i]/complex<double>(2,0);
  return v;
}

vector<complex<double>> convolution(vector<complex<double>> a,vector<complex<double>> b){
  if(a.size()>b.size())swap(a,b);
  while(a.size()<b.size())a.push_back(0);
  a=fft(a);
  b=fft(b);
  for(auto p:a)cout << p << " ";
  cout << endl;
  for(int i=0;i<b.size();i++){
    b[i]=a[i]*b[i];
  }
  b=invfft(b);
  return b;
}

int main(){
  cout << setprecision(20);
  int CNT=1;
  vector<complex<double>> v={5,2,3,8,1};
  vector<complex<double>> w={4,7,6,2};
  for(auto p:v){
    cout << p << " ";
  }
  cout << endl;
  for(int i=0;i<CNT;i++){
    v=convolution(v,w);
  }
  for(auto p:v){
    if(abs(p.real())<1e-10)p.real(0);
    if(abs(p.imag())<1e-10)p.imag(0);
    cout << p.real() << "+" << p.imag() << " ";
  }
  cout << endl;
}

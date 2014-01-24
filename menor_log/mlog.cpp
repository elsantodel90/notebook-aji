#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define forn(i,n) for(int i=0;i<(n);++i)
#define dforn(i,n) for(int i=(n)-1;i>=0;--i)
#define forsn(i,s,n) for(int i=s;i<(n);++i)
#define forall(it,X) for(typeof(X.begin()) it = X.begin(); it != X.end(); ++it)
typedef pair<int,int> pint;
typedef long long tint;

int vec[1000050];
char msg[1000050];

bool esPrimo(tint n){
	if(n<2)return false;
	if(n%2==0)return n == 2;
	for(tint i=3;i*i<=n;i+=2)if(n%i==0)return false;
	return true;
}

//insersion y consulta de cuantos <= en log n
struct leqset {
   int maxl; vector<int> c;
   int pref(int n, int l) { return (n>>(maxl-l))|(1<<l); }
   void ini(int ml) { maxl=ml; c=vector<int>(1<<(maxl+1)); }
   //inserta c copias de e, si c es negativo saca c copias
   void insert(int e, int q=1) { forn(l,maxl+1) c[pref(e,l)]+=q; }
   int leq(int e) {
      int r=0,a=1;
      forn(i,maxl) {
         a<<=1; int b=(e>>maxl-i-1)&1;
         if (b) r+=c[a]; a|=b;
      } return r + c[a]; //sin el c[a] da los estrictamente menores
   }
   int size() { return c[1]; }
   int count(int e) { return c[e|(1<<maxl)]; }
};

void primos() {
	int cnt = 0;
	forsn(i, 2, 1000000001) {
		cnt += esPrimo(i);
		int d = i; int e = 0;
		while (d%10==0) d /= 10, e++;
		if (d==1) cout << "$\\pi(10^" << e << ")$ = " << cnt << endl;
	}
}


int main(void) {
	leqset q;


	return 0;
}

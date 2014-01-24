#include <cstdio>
#include <iostream>
using namespace std;
#define forn(i,n) for(int i=0;i<n;++i)
#define dforn(i,n) for(int i=n-1;i>=0;--i)
#define forsn(i,s,n) for(int i=s;i<n;++i)

typedef int tipo;
typedef long long tint;
tint mcd(tint a, tint b){return (b==0)?a:mcd(b, a%b);}

/* Codigo para el notebook */
struct frac {
	tint p,q;
	frac(tint num=0, tint den=1):p(num),q(den) { norm(); }
	frac& operator+=(const frac& o){
		tint a = mcd(q,o.q);
		p=p*(o.q/a)+o.p*(q/a);
		q*=(o.q/a);
		norm();
		return *this;
	}
	frac& operator-=(const frac& o){
		tint a = mcd(q,o.q);
		p=p*(o.q/a)-o.p*(q/a);
		q*=(o.q/a);
		norm();
		return *this;
	}
	frac& operator*=(frac o){
		tint a = mcd(q,o.p);
		tint b = mcd(o.q,p);
		p=(p/b)*(o.p/a);
		q=(q/a)*(o.q/b);
		return *this;
	}
	frac& operator/=(frac o){
		tint a = mcd(q,o.q);
		tint b = mcd(o.p,p);
		p=(p/b)*(o.q/a);
		q=(q/a)*(o.p/b);
		norm();
		return *this;
	}

	void norm(){
		tint aux = mcd(p,q);
		if (aux){ p/=aux; q/=aux; }
		else { q=1; }
		if (q<0) { q=-q; p=-p; }
	}
};
/* fin codigo para el notebook */

int main(void) {
	#ifndef ONLINE_JUDGE
	freopen("frac.in","r",stdin);
	#endif
	
	int n;
	while( cin >> n && n) {
		/* Mataría hacer testing acá */
	}

	return 0;
}

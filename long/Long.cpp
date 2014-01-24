#include <iostream>
#include <string>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);++i)
#define dforn(i,n) for(int i=(n)-1;i>=0;--i)
#define forsn(i,s,n) for(int i=s;i<int(n);++i)
typedef unsigned long long int mtint;
typedef long long int tint;
#define DBG(x) { cout << #x << " = "; out(x); } 

//

typedef tint tipo;
#define BASEXP 6
#define BASE 1000000
#define LMAX 1000

struct Long {
	int l;
	tipo n[LMAX];
	
	Long(tipo x) { 	l = 0; forn(i, LMAX) { n[i]=x%BASE; l+=!!x||!i; x/=BASE;} }
	Long(){*this = Long(0);}
	Long(string x) {
		l=(x.size()-1)/BASEXP+1;
		fill(n, n+LMAX, 0);
		tipo r=1;
		forn(i,x.size()){
			n[i / BASEXP] += r * (x[x.size()-1-i]-'0');	
			r*=10; if(r==BASE)r=1;
		} 
	}

};

void out(Long& a) {
	char msg[BASEXP+1];
	dforn(i,a.l) {
		sprintf(msg, "%6.6llu", a.n[i]); cout << msg;
	}
	cout << endl; 
}


void invar(Long &a) { 
	fill(a.n+a.l, a.n+LMAX, 0);
	while(a.l>1 && !a.n[a.l-1]) a.l--;
}

void lsuma(const Long&a, const Long&b, Long&c) { // c = a + b
	c.l = max(a.l, b.l);
	tipo q = 0;
	forn(i, c.l) q += a.n[i]+b.n[i], c.n[i]=q%BASE, q/=BASE;
	if(q) c.n[c.l++] = q;
	invar(c);
}
Long& operator+= (Long&a, const Long&b) { lsuma(a, b, a); return a; }
Long operator+ (const Long&a, const Long&b) { Long c; lsuma(a, b, c); return c; }

bool lresta(const Long&a, const Long&b, Long&c) { // c = a - b
	c.l = max(a.l, b.l);
	tipo q = 0;
	forn(i, c.l) q += a.n[i]-b.n[i], c.n[i]=(q+BASE)%BASE, q=(q+BASE)/BASE-1;
	invar(c);
	return !q;
}
Long& operator-= (Long&a, const Long&b) { lresta(a, b, a); return a; }
Long operator- (const Long&a, const Long&b) { Long c; lresta(a, b, c); return c; }

bool operator< (const Long&a, const Long&b) { Long c; return !lresta(a, b, c); }
bool operator<= (const Long&a, const Long&b) { Long c; return lresta(b, a, c); }
bool operator== (const Long&a, const Long&b) { return a <= b && b <= a; }

void lmul(const Long&a, const Long&b, Long&c) { // c = a * b
	c.l = a.l+b.l;
	fill(c.n, c.n+b.l, 0);
	forn(i, a.l) {
		tipo q = 0;
		forn(j, b.l) q += a.n[i]*b.n[j]+c.n[i+j], c.n[i+j] = q%BASE, q/=BASE;
		c.n[i+b.l] = q;
	}
	invar(c);
}

Long& operator*= (Long&a, const Long&b) { Long c; lmul(a, b, c); return a=c; }
Long operator* (const Long&a, const Long&b) { Long c; lmul(a, b, c); return c; }

void ldiv(const Long& a, tipo b, Long& c, tipo& rm) { // c = a / b ; rm = a % b
	rm = 0;
	dforn(i, a.l) {
		rm = rm * BASE + a.n[i];
		c.n[i] = rm / b; rm %= b;
	}
	c.l = a.l;
	invar(c);  
}

void ldiv(const Long& a, const Long& b, Long& c, Long& rm) { // c = a / b ; rm = a % b
	rm = 0;
	dforn(i, a.l) {
//		DBG(rm);
		dforn(j, rm.l) rm.n[j+1] = rm.n[j];
		rm.n[0] = a.n[i]; rm.l++;
		tipo q = rm.n[b.l] * BASE + rm.n[b.l-1];
		tipo u = q / (b.n[b.l-1] + 1);
		tipo v = q /  b.n[b.l-1] + 1;
		while (u < v-1) {
//			cout << ".";
			tipo m = (u+v)/2;
			if (b*m <= rm) u = m; else v = m;
		}
		c.n[i] = u;
		rm -= b*u;
	}
	c.l = a.l;
	invar(c);  
}

int main(int argc, char** argv) {
	Long a (9876543210LL);
	Long b ("123456789");
	
	Long c;
	lsuma(a, b, c);
	
	DBG(a); DBG(b); DBG(c);
	
	Long x = a, y = a;
	Long z = x * y;
	DBG(z);
	a *= a;
	DBG(a);
	
	cout << "a = a ^ 32 \n";
	forn(i, 4) a *= a;
	DBG(a)

	forn(i, 3) b *= b;
	DBG(b)
	
//	b = 999999;
	tipo rm;
	tipo dv = 1234;
	ldiv(a, dv, c, rm);
	cout << "Resto: " << rm << endl;
	
	Long d = c;
	d *= dv;
	d += rm;
	DBG(d);
	if (a == d) cout << "lmul [ OK ]; ldiv(tint) [ OK ]" << endl;
	
	Long w, r;
	ldiv(a, b, w, r);
	DBG(w);
	DBG(r);
	
	Long aa = b * w + r;
	DBG(aa);
	if (a == aa) cout << "ldiv(Long) [ OK ]" << endl;
//	cout << a << endl;
	return 0;
}

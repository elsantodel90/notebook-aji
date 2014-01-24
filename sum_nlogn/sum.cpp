#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;
#define forn(i,n) for(int i=0;i<n;++i)
#define dforn(i,n) for(int i=n-1;i>=0;--i)
#define forsn(i,s,n) for(int i=s;i<n;++i)

typedef int tipo;
/* Codigo para el notebook */

#define MAXN 100000

struct rmq {
	int MAX;
	tipo vec[4*MAXN];
	tipo* init(int n) {
		MAX = 1 << (32-__builtin_clz(n)); 
		fill(vec, vec+2*MAX, 0); // 0 = elemento neutro
		return vec+MAX;
	}
	void updall() { dforn(i, MAX) vec[i] = vec[2*i] + vec[2*i+1]; } // + = operacion
	void pset(int i, tipo vl) {
		vec[i+=MAX] = vl;
		while(i) { i /= 2; vec[i] = vec[2*i] + vec[2*i+1]; } // + = operacion
	}
	tipo pget(int i, int j) { return _pget(i+MAX, j+MAX); }
	tipo _pget(int i, int j) {
		tipo res = 0;             // 0 = elemento neutro
		if (j-i <= 0) return res;
		if (i%2) res += vec[i++]; // + = operación
		res += _pget(i/2, j/2);   // + = operación
		if (j%2) res += vec[--j]; // + = operación
		return res;
	}
};

/* fin codigo para el notebook */

rmq ra;

int qget(int i, int j) { // intervalo [i,j)
  int res = 0;
	forsn(a, i, j) res += ra.vec[ra.MAX+a];
	return res;
}

int main(void) {
	#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	#endif
	
	int n;
	while( cin >> n && n) {
		tipo* v = ra.init(n);
		forn(i, n) cin >> v[i];
		ra.updall();

		cout << ra.MAX << endl;

		cout << "Sumas: " << endl;
		forsn(j, 1, n+1) {
			forn(i, j) cout << ra.pget(i, j) << " "; cout << endl;
		}

		forn(x, 200) {
			ra.pset(rand()%n, rand()%100);

			forsn(j, 1, n+1) {
				forn(i, j) {
					if (ra.pget(i, j) != qget(i,j)) {
						cout << "Error: (" << i << ", " << j << ") -- pget: " << ra.pget(i, j) << " | expect: " << qget(i, j) << endl;
					}
				}
			}
		}

		cout << endl << "Represenacion interna: " << endl;
		forn(i, ra.MAX+n) cout << ra.vec[i] << " "; cout << endl;
	}

	return 0;
}

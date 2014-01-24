#include <cstdio>
#include <iostream>
using namespace std;
#define forn(i,n) for(int i=0;i<n;++i)
#define forsn(i,s,n) for(int i=s;i<n;++i)

/* Codigo para el notebook */

// Debe ser n < 2^LVL

#define LVL 10

int vec[LVL][1<<LVL];
int mn(int i, int j) { // intervalo [i,j)
	int p = 31-__builtin_clz(j-i);
	return min(vec[p][i],vec[p][j-(1<<p)]);
}
void mn_init(int n) {
	int mp = 31-__builtin_clz(n);
	forn(p, mp) forn(x, n-(1<<p)) vec[p+1][x] = min(vec[p][x], vec[p][x+(1<<p)]);
}

/* fin codigo para el notebook */

/*
	Observaciones:
	* Inicializacion: Cargar el arreglo en vec[0][i] y llamar a mn_init(n)
	*                 PRE: n < 2 ^ LVL
	*
	* Consulta: mn(i, j) dice el mínimo en O(1) del intervalo [i, j)  (NO INCLUYE j!)
	*           PRE: j > i  (intervalo no vacío)
*/

int main(void) {
	#ifndef ONLINE_JUDGE
	freopen("mn.in","r",stdin);
	#endif
	
	int n;
	cin >> n;
	forn(i, n) cin >> vec[0][i];
	mn_init(n);

	cout << "Comparaciones: " << endl;
	forsn(j, 1, n+1) {
		forn(i, j) cout << mn(i, j) << " "; cout << endl;
	}

	cout << endl << "Represenacion interna: " << endl;
	forn(p, 4) {
		forn(x, n) cout << vec[p][x] << " "; cout << endl;
	}

	return 0;
}

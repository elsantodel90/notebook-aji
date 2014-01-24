#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define forn(i,n) for(int i=0;i<n;++i)
#define forsn(i,s,n) for(int i=s;i<n;++i)

/* Codigo para el notebook */

typedef long double tipo;

typedef vector<tipo> Vec;
typedef vector<Vec> Mat;
#define eps 1e-16
#define epsval 1e-14
#define feq(a, b) (fabs(a-b)<eps)

bool resolver(Mat a, Vec y, Vec &x){
  int n = a.size();
  vector<int> p; forn(i,n) p.push_back(i);
  forn(i, n){
    int uc=i, uf=i;
    forsn(f, i, n) forsn(c, i, n) if (fabs(a[f][c]) > fabs(a[uf][uc])) {uf=f;uc=c;}
    if (feq(a[uf][uc], 0)) return false;
		forn(j, n) swap(a[j][i], a[j][uc]);
    swap(a[i], a[uf]); swap(y[i], y[uf]); swap(p[i], p[uc]);
    tipo inv = 1 / a[i][i]; //aca divide
    forsn(j, i+1, n) {
      tipo v = a[j][i] * inv;
      forsn(k, i, n) a[j][k]-=v * a[i][k];
      y[j] -= v*y[i];
    }
  }
  x = vector<tipo>(n);
  for(int i=n-1;i>=0;i--){
    tipo s = y[i];
		forsn(j, i+1, n) s -= a[i][j]*x[p[j]];
    x[p[i]] = s / a[i][i]; //aca divide
  }
  return true;
}

#define MAXVAR 100
#define MAXRES 200
tipo rmat[MAXRES][MAXVAR+MAXRES*2];
tipo bvec[MAXRES];
tipo cfun[MAXVAR+MAXRES*2];
tipo xvar[MAXVAR];

#define HAYSOL	0
#define NOSOL -1
#define NOCOTA -2

int simplex(int m, int n) { // cant restric; cant vars
	int base[MAXVAR+MAXRES], esab[MAXVAR+MAXRES];
	int nn = n+m; // Variables (originales) + holgura
	tipo res = 0;

	forn(i, m) forn(j, m) rmat[i][n+j] = (i==j);
	forn(i, m) cfun[n+i] = 0;

	forn(i, n) esab[i] = -1;
	forn(i, m) { base[i] = n+i; esab[n+i] = i; }

	// Agrega las artificiales; si todos los bvec[] son positivos se puede omitir esto
	int arts[MAXRES];
	int bmin = 0;
	forn(i, m) if (bvec[i] < bvec[bmin]) bmin = i;
	int art = bvec[bmin] < -eps;
	forn(i, m) arts[i] = 2*(bvec[i] >= -eps) - 1;
	if (art) {
		forn(i, m) rmat[i][nn] = -(bvec[i] < -eps);
		esab[n+bmin] = -1; esab[nn] = bmin; base[bmin] = nn;
		nn++;
	}

	Mat B(m, Vec(m, 0));
	Vec y(m, 0), c(m, 0), d(m, 0);
	int j0 = 0;
	do {
		forn(i, m) forn(j, m) B[i][j] = arts[j] * rmat[j][base[i]];
		forn(i, m) c[i] = art?base[i]>=m+n:cfun[base[i]];
		resolver(B, c, y);

		for(; j0 < nn; ++j0) if (esab[j0] == -1) {
			res = art?j0>=m+n:cfun[j0];
			forn(i, m) res -= y[i] * arts[i] * rmat[i][j0];
			if (j0 < m+n && res < epsval) break;
		}

		forn(i, m) forn(j, m) B[i][j] = rmat[i][base[j]];
		forn(i, m) c[i] = rmat[i][j0];
		resolver(B, c, d);
		forn(i, m) c[i] = bvec[i];
		resolver(B, c, y);

		if (j0 == nn) if (art) {
			if (esab[m+n] != -1 && y[esab[m+n]] > epsval) return NOSOL;
			for(int i = m+n-1; i >= 0; i--) if (esab[i] == -1) { esab[i] = esab[m+n]; base[esab[i]] = i; break; }
			art = 0; nn = m+n; j0 = 0; continue;
		} else break; // Optimo

		bool bl = true;
		forn(i, m) bl = bl && (d[i] <= eps);

		if (bl) return NOCOTA; // Problema no acotado

		int j1 = 0;
		forn(i, m) if (d[i] > 0) {
			tipo mlt = y[i] / d[i];
			if (!bl || (feq(mlt, res) && (base[i] < j1)) || (mlt < res)) {
				res = mlt;
				j1 = base[i];
				bl = true;
			}		
		}
		if (res < eps && ++j0) continue;
		if (art && j1 == m+n) nn--, art--;

		int w = esab[j1];      // variable de salida
		base[w] = j0;           // Entra j0
		esab[j0] = w;
		esab[j1] = -1;         // j1 es no basica ahora.
		j0 = 0;
	} while(1);

	forn(i, m) forn(j, m) B[i][j] = rmat[i][base[j]];
	forn(i, m) c[i] = bvec[i];
	resolver(B, c, y);

	forn(i, n) xvar[i] = (esab[i] == -1)?0:y[esab[i]];

	return HAYSOL;
}

// Programación lineal entera

void show_sol(int res, tipo* xvar, int n);

tipo xmej[MAXVAR];
tipo spxmej;
tipo spxres[2][MAXVAR];
int spxus[2][MAXVAR];

void simplex_zinit(int n) {
	spxmej = 1e200;
	forn(k, 2) forn(i, n) spxus[k][i] = 0;
}

int simplex_z(int m, int n) {
	int res = simplex(m, n);
	if (res == NOCOTA || res == NOSOL) return res;

	tipo mej = 0; forn(i, n) mej += cfun[i] * xvar[i];
	if (mej >= spxmej) return res;

	tipo hmej = 0; forn(i, n) hmej += cfun[i] * round(xvar[i]);
	if (hmej < spxmej) {
		bool b = 1;
		forn(i, m*b) {
			tipo sum = 0; forn(j, n) sum += rmat[i][j] * round(xvar[j]);
			b = sum <= bvec[i];
		}
		if (b) {
			spxmej = hmej;
			forn(i, n) xmej[i] = round(xvar[i]);
			if (mej >= hmej) return res;
		}
	}

	int j = -1;
	forn(i, n) if (fabs(round(xvar[i]) - xvar[i]) > 1e-7) { j = i; break; }

	if (j != -1) {
		tipo x = xvar[j];
		forn(kk, 2) { int k = 1-kk;
			bool b = spxus[k][j];
			b || (spxus[k][j] = m++);
			int p = spxus[k][j];
			if (!b) forn(i, n) rmat[p][i] = k?(i==j):-(i==j);

			tipo y = bvec[p]; bvec[p] = k?floor(x):-ceil(x);

			simplex_z(m, n);
			bvec[p] = y;
			b || (spxus[k][j]=0, m--);
		}
	} else {
		spxmej = mej;
		forn(i, n) xmej[i] = xvar[i];
	}
	return res;
}

/* fin codigo para el notebook */

void show_sol(int res, tipo* xvar, int n) {
	if (res == HAYSOL) {
		cout << "HAYSOL  ";
		forn(i, n) printf("%14.4f ", (double)xvar[i]); cout << endl;
		tipo res = 0;
		forn(i, n) res += xvar[i] * cfun[i];
		printf("Valor del funcional: %16.4f\n", (double)res);

	} else if (res == NOSOL) cout << "NOSOL" << endl;
	else if (res == NOCOTA) cout << "NOACOTADO" << endl;
	else cout << "*** ERROR ***" << endl;
}

int main(void) {
	freopen("simplex.in","r",stdin);
	/* Formato de archivo:
		m n (restricciones, variables)
		A | B (matriz de m x n; vector indep)
		C (vector de n posiciones = función _beneficio_)
	*/
	// Resuelve: max(C^t * X) / A*X <= B y X >= 0

	int m, n;

	cin >> m >> n;
	forn(i, m) { forn(j, n) cin >> rmat[i][j]; cin >> bvec[i]; }
	forn(i, n) cin >> cfun[i];

	cout << "Simplex real " << endl << endl;
	show_sol(simplex(m, n), xvar, n);

	cout << endl << "Simplex entero " << endl;

	simplex_zinit(n);
	int sol = 0;
//	sol = simplex_z(m, n);
	forn(i, n) xvar[i] = xmej[i];
	show_sol(sol, xmej, n);

	return 0;
}

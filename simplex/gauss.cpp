#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define forn(i,n) for(int i=0;i<n;++i)
#define forsn(i,s,n) for(int i=(s);i<(n);++i)

typedef double tipo;

/* Codigo para el notebook */

typedef vector<vector<tipo> > Mat;
typedef vector<tipo> Vec;
#define feq(a, b) (fabs(a-b)<0.00000001)

void show(Mat &a);

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

bool diagonalizar(Mat &a){
	// PRE: a.cols > a.filas
	// PRE: las primeras (a.filas) columnas de a son l.i.
  int n = a.size(), m = a[0].size();
  forn(i, n){
		int uf = i;
		forsn(k, i, n) if (fabs(a[k][i]) > fabs(a[uf][i])) uf = k;
		if (feq(a[uf][i], 0)) return false;
		swap(a[i], a[uf]);
    tipo inv = 1 / a[i][i]; // aca divide
    forn(j, n) if (j != i) {
      tipo v = a[j][i] * inv;
      forsn(k, i, m) a[j][k] -= v * a[i][k];
		}
    forsn(k, i, m) a[i][k] *= inv;
  }
	return true;
}

void show(Mat &a) {
	forn(i, a.size()) {
		forn(j, a[i].size()) {
			if (j == a.size()) cout << "| ";
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(void) {
	freopen("gauss.in","r",stdin);
	/* Formato de archivo:
		n, m (fila x columna)
		A | B (matriz de n x n; vector sol)
	*/

	int n, m;

	cin >> n >> m;
	Mat a(n, Vec(m, 0));
	Vec b(n, 0);
	Vec y(n, 0);

	forn(i, n) forn(j, m) cin >> a[i][j];
	forn(i, n) b[i] = a[i][n];

	show(a);
	if (!resolver(a, b, y)) cout << "NO RESOLVER" << endl;
	diagonalizar(a);
	show(a);
	cout << endl;
	forn(i, n) cout << y[i] << " "; cout << endl;

	
}

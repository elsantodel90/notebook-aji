#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define forn(i,n) for(int ___n = (n), i=0;i<___n;++i)
#define dforn(i,n) for(int i=(n)-1;i>=0;--i)
#define forsn(i,s,n) for(int ___n = (n), i = (int)(s);i<___n;++i)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); ++it)
#define dforall(it,X) for(typeof((X).rbegin()) it = (X).rbegin(); it != (X).rend(); ++it)
#define all(c) (c).begin(), (c).end()
#define D(a) << #a << "=" << a << " "
#define OUT(a) cout D(a) << endl;
template <class T, class S>ostream& operator<<(ostream &os, const pair<T, S> &t){os << "(" << t.first << ", "  << t.second << ")";return os;}
template <class T>ostream& operator<<(ostream &os, const vector<T> &t){os << "{"; forn(i, (t).size()){if(i>0)os<<", ";os << t[i];} os << "}";return os;}
typedef pair<int,int> pint;
typedef long long tint;
typedef long double tipo;

/* Start código notebookizable */

typedef vector<tipo> Vec;
typedef vector<Vec> Mat;
#define eps 1e-10
#define feq(a, b) (fabs(a-b)<eps)

void show(const Mat &a);
void show(const Mat &a, const Vec &b);

bool resolver(Mat a, Vec y, Vec &x){
// Sólo con matrices de n x n
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
  dforn(i, n){
    tipo s = y[i];
    forsn(j, i+1, n) s -= a[i][j]*x[p[j]];
    x[p[i]] = s / a[i][i]; //aca divide
  }
  return true;
}

bool resolver_rect(Mat a, Vec y, Vec &x){
  int n = a.size(), m = n?a[0].size():0, rw = min(n, m);
  vector<int> p; forn(i,m) p.push_back(i);
  forn(i, rw){
    int uc=i, uf=i;
    forsn(f, i, n) forsn(c, i, m) if(fabs(a[f][c])>fabs(a[uf][uc])) {uf=f;uc=c;}
    if (feq(a[uf][uc], 0)) { rw = i; break; }
    forn(j, n) swap(a[j][i], a[j][uc]);
    swap(a[i], a[uf]); swap(y[i], y[uf]); swap(p[i], p[uc]);
    tipo inv = 1 / a[i][i]; //aca divide
    forsn(j, i+1, n) {
      tipo v = a[j][i] * inv;
      forsn(k, i, m) a[j][k]-=v * a[i][k];
      y[j] -= v*y[i];
    }
  } // rw = rango(a)
  forsn(i, rw, n) if (!feq(y[i],0)) return false;
  x = vector<tipo>(m, 0);
  dforn(i, rw){
    tipo s = y[i];
    forsn(j, i+1, rw) s -= a[i][j]*x[p[j]];
    x[p[i]] = s / a[i][i]; //aca divide
  }
  return true;
}

bool resolver_ev(Mat a, Vec y, Vec &x, Mat &ev){
  int n = a.size(), m = n?a[0].size():0, rw = min(n, m);
  vector<int> p; forn(i,m) p.push_back(i);
  forn(i, rw){
    int uc=i, uf=i;
    forsn(f, i, n) forsn(c, i, m) if(fabs(a[f][c])>fabs(a[uf][uc])) {uf=f;uc=c;}
    if (feq(a[uf][uc], 0)) { rw = i; break; }
    forn(j, n) swap(a[j][i], a[j][uc]);
    swap(a[i], a[uf]); swap(y[i], y[uf]); swap(p[i], p[uc]);
    tipo inv = 1 / a[i][i]; //aca divide
    forsn(j, i+1, n) {
      tipo v = a[j][i] * inv;
      forsn(k, i, m) a[j][k]-=v * a[i][k];
      y[j] -= v*y[i];
    }
  } // rw = rango(a)
  forsn(i, rw, n) if (!feq(y[i],0)) return false;
  x = vector<tipo>(m, 0);
  dforn(i, rw){
    tipo s = y[i];
    forsn(j, i+1, rw) s -= a[i][j]*x[p[j]];
    x[p[i]] = s / a[i][i]; //aca divide
  }
  ev = Mat(m-rw, Vec(m, 0));
  forn(k, m-rw) {
    ev[k][p[k+rw]] = 1;
    dforn(i, rw){
      tipo s = -a[i][k+rw];
      forsn(j, i+1, rw) s -= a[i][j]*ev[k][p[j]];
      ev[k][p[i]] = s / a[i][i]; //aca divide
    }
  }
  return true;
}

/* End código notebookizable */

void show(const Mat &a) {
  forn(i, a.size()) {
    forn(j, a[i].size()) {
      if (j == (int)a.size()) cout << "| ";
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void show(const Mat &a, const Vec &b) {
  forn(i, a.size()) {
    forn(j, a[i].size()) cout << a[i][j] << " ";
    cout << "| " << b[i] << endl;
  }
  cout << endl;
}

int main(void) {
  freopen("linear.in","r",stdin);
  /* Formato de archivo:
    n, m (fila x columna)
    A | B (matriz de n x m; vector sol (tamaño n))
  */

  int n, m, t = 0;
  while (cin >> n >> m && n && m) {
    cout << "Case #" << ++t << endl;
    Mat a(n, Vec(m, 0));
    Vec b(n, 0);
    Vec x(m, 0);

    forn(i, n) { forn(j, m) cin >> a[i][j]; cin >> b[i]; }

    show(a, b);
    cout << "Method: resolver" << endl;
    if (n == m) {
      if (!resolver(a, b, x)) cout << "Sol: No hay o hay varias" << endl;
      else cout << "Sol: " << x << endl;
    } else cout << "Inaplicable" << endl;
    cout << endl;

    cout << "Method: resolver_rect" << endl;
    if (!resolver_rect(a, b, x)) cout << "Sol: No hay" << endl;
    else cout << "Sol: " << x << endl;
    cout << endl;

    cout << "Method: resolver_ev" << endl;
    Mat ev;
    if (!resolver_ev(a, b, x, ev)) cout << "Sol: No hay" << endl;
    else {
      cout << "Sol: " << x << endl;
      cout << "Ev: " << ev << endl;
//      forall(vec, ev) { cout << "  " << (*vec) << endl; }
    }
    cout << endl;

  }
}

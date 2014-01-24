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

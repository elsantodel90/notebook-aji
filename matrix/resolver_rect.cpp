bool resolver_rect(Mat a, Vec y, Vec &x){
  int n = a.size(), m = a[0].size(), rw = min(n, m);
  vector<int> p; forn(i,m) p.push_back(i);
  forn(i, rw){
    int uc=i, uf=i;
    forsn(f, i, n) forsn(c, i, m) if(fabs(a[f][c])>fabs(a[uf][uc])){uf=f;uc=c;}
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

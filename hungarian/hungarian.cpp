/**
 * Algoritmo húngaro (Hungarian Algorithm).
 * Resuelve Matching PERFECTO de costo MAXIMO en grafos BIPARTITOS COMPLETOS
 *
 * Fuente: http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=hungarianAlgorithm
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <queue>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
#define forsn(i,s,n) for(int i=s;i<int(n);++i)
#define forall(i,c) for(typeof(c.begin()) i=c.begin();i!=c.end();++i)
#define DBG(X) cerr << #X << " = " << X << endl;
typedef vector<int> vint;
typedef vector<vint> vvint;

void showmt();

/* begin notebook */

#define MAXN 256
#define INFTO 0x7f7f7f7f
int n;
int mt[MAXN][MAXN]; // Matriz de costos (X * Y)
int xy[MAXN], yx[MAXN]; // Matching resultante (X->Y, Y->X)

int lx[MAXN], ly[MAXN], slk[MAXN], slkx[MAXN], prv[MAXN];
char S[MAXN], T[MAXN];

void updtree(int x) {
	forn(y, n) if (lx[x] + ly[y] - mt[x][y] < slk[y]) {
		slk[y] = lx[x] + ly[y] - mt[x][y];
		slkx[y] = x;
	}
}
int hungar() {
	forn(i, n) {
		ly[i] = 0;
		lx[i] = *max_element(mt[i], mt[i]+n);
	}
	memset(xy, -1, sizeof(xy));
	memset(yx, -1, sizeof(yx));

	forn(m, n) {
		memset(S, 0, sizeof(S));
		memset(T, 0, sizeof(T));
		memset(prv, -1, sizeof(prv));
		memset(slk, 0x7f, sizeof(slk));
		queue<int> q;
		#define bpone(e, p) { q.push(e); prv[e] = p; S[e] = 1; updtree(e); }
		forn(i, n) if (xy[i] == -1) { bpone(i, -2); break; }

		int x=0, y=-1;
		while (y==-1) {
			while (!q.empty() && y==-1) {
				x = q.front(); q.pop();
				forn(j, n) if (mt[x][j] == lx[x] + ly[j] && !T[j]) {
					if (yx[j] == -1) { y = j; break; }
					T[j] = 1;
					bpone(yx[j], x);
				}
			}
			if (y!=-1) break;
			int dlt = INFTO;
			forn(j, n) if (!T[j]) dlt = min(dlt, slk[j]);
			forn(k, n) {
				if (S[k]) lx[k] -= dlt;
				if (T[k]) ly[k] += dlt;
				if (!T[k]) slk[k] -= dlt;
			}
//			q = queue<int>();
			forn(j, n) if (!T[j] && !slk[j]) {
				if (yx[j] == -1) {
					x = slkx[j]; y = j; break;
				} else {
					T[j] = 1;
					if (!S[yx[j]]) bpone(yx[j], slkx[j]);
				}
			}
		}
		if (y!=-1) {
			for(int p = x; p != -2; p = prv[p]) {
				yx[y] = p;
				int ty = xy[p]; xy[p] = y; y = ty;
			}
		} else break;
	}
	int res = 0;
	forn(i, n) res += mt[i][xy[i]];
	return res;
}

/* end notebook */


void showmt() {
	cerr << "mt:" << endl;
	forn(i, n) {
		cerr << lx[i] << " | ";
		forn(j, n) cerr << mt[i][j] - lx[i] - ly[j] << " ";
		cerr << endl;
	}
	cerr << "lx = "; forn(i, n) cerr << lx[i] << " "; cerr << endl;
	cerr << "ly = "; forn(i, n) cerr << ly[i] << " "; cerr << endl;
	cerr << "xy = "; forn(i, n) cerr << xy[i] << " "; cerr << endl;
	cerr << "yx = "; forn(i, n) cerr << yx[i] << " "; cerr << endl;
	cerr << "slk= "; forn(i, n) cerr << slk[i] << " "; cerr << endl;
	cerr << endl;
}

int main() {
	freopen("hungarian.in", "r", stdin);
	vector<string> g;
	while(cin >> n && n) {

		int w;
		forn(i,n) forn(j,n) { cin >> w; mt[i][j] = w; }

		int res = hungar();
		cout << res << endl;
		forn(i, n) cerr << xy[i] << " "; cerr << endl;
	}
	return 0;
}

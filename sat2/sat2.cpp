/* Problema 4185 de valladolid nuevoportal */
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <set>
#include <list>
#include <functional>
#include <cmath>

using namespace std;

#define forn(i,n) for(int i=0; i < (int)(n); ++i)
#define DBG(X) cerr << #X << " = " << X << endl;
typedef vector<int> vint;
typedef long double tdbl;
typedef long long tint;

void show(int x);

#define dvar(x) ((x<MAXN)?"":"-") << "x" << ((x<MAXN)?x:neg(x)) 

/* Begin codigo notebook */
#define MAXN 1024
#define MAXEQ 1024000

int fch[2*MAXN], nch[2*MAXEQ], dst[2*MAXEQ], eqs;
#define neg(X) (2*MAXN-1-(X))
#define addeje(s,d) { nch[eqs]=fch[s]; dst[fch[s]=eqs++]=d; }
void init() {
	memset(fch, 0xff, sizeof(fch));
	eqs=0;
}
void addEqu(int a, int b) {
	addeje(neg(a), b);
	addeje(neg(b), a);
}
int us[2*MAXN], lw[2*MAXN], id[2*MAXN];
stack<int> q; int qv, cp;
void tjn(int i) {
	lw[i] = us[i] = ++qv;
	id[i]=-2; q.push(i);
	for(int j = fch[i]; j!=-1; j=nch[j]) { int x = dst[j];
		if (!us[x] || id[x] == -2) {
			if (!us[x]) tjn(x);
			lw[i] = min(lw[i], lw[x]);
		}
	}
	if (lw[i] == us[i]) {
		int x; do { x = q.top(); q.pop(); id[x]=cp; } while (x!=i);
		cp++;
	}
}
void compCon(int n) { // Tarjan algorithm
	memset(us, 0, sizeof(us));
	memset(id, -1, sizeof(id));
	q=stack<int>(); qv = cp = 0;
	forn(i, n) {
		if (!us[i]) tjn(i);
		if (!us[neg(i)]) tjn(neg(i));
	}
}
bool satisf(int n) {
	compCon(n);
	forn(i, n) if (id[i] == id[neg(i)]) return false;
	return true;
}
/* End codigo notebook */

void show(int x) { cerr << "x" << dvar(x) << endl; }
void showgr(int n) {
	forn(i, n) { int x = i; forn(k, 2) { x = neg(x);
		cerr << dvar(x) << " --> ";
		for(int j = fch[x]; j!=-1; j=nch[j]) cerr << " " << dvar(dst[j]); cerr << endl;
	}}
}

int main() {
#ifdef AMDINSIDE
	freopen("entrada.txt", "r", stdin);
#endif

	int n, m;
	while(cin >> n >> m && n && m) {
		init();
		forn(i, m) {
			int i, j;
			char ci, cj;
			cin >> ci >> i >> cj >> j; i--; j--;
//			cerr << ci << i << " " << cj << j << endl;
			int a = (ci=='+')?i:neg(i); 
			int b = (cj=='+')?j:neg(j);
			addEqu(a, b);
		}
//		showgr(n);
		int res = satisf(n);
		cout << res << endl;
	}
	return 0;
}

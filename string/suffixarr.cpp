/*
 * Suffix Array construction
 *
 * See http://acmicpc-live-archive.uva.es/nuevoportal/data/problem.php?p=3999
 */

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

typedef unsigned char xchar;
void show(const xchar* s, int* r);

/* Begin codigo notebook */
typedef unsigned char xchar;
#define MAXN 1000000

int p[MAXN], r[MAXN], t, n;

bool sacmp(int a, int b) { return p[(a+t)%n] < p[(b+t)%n]; }
void bwt(const xchar *s, int nn) {
	n = nn;
	int bc[256];
	memset(bc, 0, sizeof(bc));
	forn(i, n) ++bc[s[i]];
	forn(i, 255) bc[i+1]+=bc[i];
	forn(i, n) r[--bc[s[i]]]=i;
	forn(i, n) p[i]=bc[s[i]];
	
	int lnb,nb = 1;
	for(t = 1; t < n; t*=2) {
		lnb = nb; nb = 0;
		for(int i = 0, j = 1; i < n; i = j++) {
			/*calcular siguiente bucket*/
			while(j < n && p[r[j]] == p[r[i]]) ++j;
			if (j-i > 1) {
				sort(r+i, r+j, sacmp);
				int pk, opk = p[(r[i]+t)%n];
				int q = i, v = i;
				for(; i < j; i++) {
					if (((pk = p[(r[i]+t)%n]) != opk) && !(q <= opk && pk < j)) { opk = pk; v = i; }
					p[r[i]] = v;
				}
			}
			nb++;
		}
		if (lnb == nb) break;
	}
//	prim = p[0];
}

void lcp(const xchar* s, int* h) {
	int q = 0, j;
	forn(i,n) if (p[i]) {
		j = r[p[i]-1];
		while(q < n && s[(i+q)%n] == s[(j+q)%n]) ++q;
		h[p[i]-1] = q;
		if (q > 0) --q;
	}
}

/* End codigo notebook */

int h[MAXN];


/*** DEBUG ***/
void show(const xchar* s, int* r) {
	forn(i,n) {
		printf("%2d (%2d,%2d) ", r[i], p[r[i]], p[(r[i]+t)%n]);
		if (i) forn(j,t) {
			char a=s[(r[i-1]+j)%n];
			char b=s[(r[i]+j)%n];
			if (a>b) printf("-------------- V -----------\n");
			if (a!=b) break;
		}
		forn(j,n) printf("%c", s[(r[i]+j)%n]); printf("\n");
	}
	printf("\n");
}

bool check(const xchar* src) {
	forn(i, n-1) { int ii = i + 1;
		forn(j, n) {
			if (src[(r[i]+j)%n] > src[(r[ii]+j)%n]) {
				cerr << r[i] << " "; forn(k, n) cerr << src[(r[i]+k)%n]; cerr << endl;
				cerr << r[ii] << " "; forn(k, n) cerr << src[(r[ii]+k)%n]; cerr << endl;
				return false;
			}
			if (src[(r[i]+j)%n] != src[(r[ii]+j)%n]) break;
		}
	}
	return true;
}

int main() {
#ifdef AMDINSIDE
	freopen("entrada.txt", "r", stdin);
#endif

	string s;
	while(getline(cin, s)) {
		int n = s.size();
		const xchar* src = (const xchar*)s.c_str();
		bwt(src, n);
//		show(src, r);
		lcp(src, h);
		DBG(check(src));
	}

	xchar buf[40000];
	forn(i, 400) {
		n = 10000 + rand()%10000;
		forn(j, n) buf[j] = rand()%256;
		bwt(buf, n);
		if (!check(buf)) cerr << "JOTA PUTO" << endl; else cerr << ".";
	}
	
	return 0;
}


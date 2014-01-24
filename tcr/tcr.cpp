#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define forn(i,n) for(int i=0;i<(n);++i)
#define dforn(i,n) for(int i=(n)-1;i>=0;--i)
#define forsn(i,s,n) for(int i=s;i<(n);++i)
#define forall(it,X) for(typeof(X.begin()) it = X.begin(); it != X.end(); ++it)
typedef pair<int,int> pint;
typedef long long tint;

struct dxy {tint d,x,y;};
dxy mcde(tint a, tint b) {
  dxy r, t;
  if (b == 0) {
    r.d = a; r.x = 1; r.y = 0;
  } else {
    t = mcde(b,a%b);
    r.d = t.d; r.x = t.y;
    r.y = t.x - a/b*t.y;
  }
  return r;
}

/* begin notebook */

#define modq(x) (((x)%q+q)%q)
tint tcr(tint* r, tint* m, int n) { // x \equiv r_i (m_i) i \in [0..n)
	tint p=0, q=1;
	forn(i, n) {
		p = modq(p-r[i]);
		dxy w = mcde(m[i], q);
		if (p%w.d) return -1; // sistema incompaible
		q = q / w.d * m[i];
		p = modq(r[i] + m[i] * p / w.d * w.x);
	}
	return p; // x \equiv p (q)
}

/* end notebook */

tint rem[10000], mod[10000];

int main(void) {
	#ifdef AMDINSIDE
	freopen("tcr.in","r",stdin);
	#endif

	int n;
	while (cin >> n && n) {
		forn(i, n) {
			cin >> rem[i] >> mod[i];
//			cout << "x = " << rem[i] << "  (" << mod[i] << ")" << endl;
		}

		tint x = tcr(rem, mod, n);
		cout << "x := " << x << endl;

		if (x!=-1) {
			bool bl = true;
			forn(i, n) {
				bl = (x-rem[i])%mod[i] == 0;
				if (!bl) break;
			}
			if (!bl) cout << "ERROR" << endl;
		}
//		cout << endl;
	}
	return 0;
}

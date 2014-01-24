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
#define D(a) << #a << "=" << a << " "
#define OUT(a) cout D(a) << endl;
typedef long long tint;

int prm[78600];
int cprm;

void init() {
	prm[0] = 2; cprm = 1;
	forsn(i, 2, 10000) { i++;
		tint n = i;
		forn(j, cprm) {
			if (n%prm[j] == 0) n = 0;
			if (prm[j]*prm[j] > n) break;
		}
		if (n) prm[cprm] = n, cprm++;
	}
}

//begin_code_block sigma
tint sigma(tint n) {
	tint cd = !!n;
	for(int i = 0; prm[i]*prm[i] <= n; i++) { tint p = prm[i];
		tint d = 1;
		while(n%p==0) n/=p,d=d*p+1;
		cd *= d;
	}
	if (n>1) cd *= n+1;
	return cd;
}
//end_code_block
//begin_code_block cantdiv
tint cantdiv(tint n) {
	tint cd = !!n;
	for(int i = 0; prm[i]*prm[i] <= n; i++) { tint p = prm[i];
		tint d = 0;
		while(n%p==0) n/=p,d++;
		cd *= d+1;
	}
	return cd * ((n>1)+1);
}
//end_code_block

int main(void) {
	init();

	tint mx = 0;
	forn(i, 10000000) {
		tint s = sigma(i);
		if (s > mx) {
			printf("$\\sigma_1(%d) = %d$\n", i, (int)s);
			mx = s;
		}
	}

	mx = 0;
	forn(i, 10000000) {
		tint s = cantdiv(i);
		if (s > mx) {
			printf("$\\sigma_0(%d) = %d$\n", i, (int)s);
			mx = s;
		}
	}


}

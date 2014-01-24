#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define forn(i,n) for(int i=0;i<(int)(n);++i)
#define dforn(i,n) for(int i=(int)(n)-1;i>=0;--i)
#define forsn(i,s,n) for(int i=s;i<(int)(n);++i)
#define forall(it,X) for(typeof(X.begin()) it = X.begin(); it != X.end(); ++it)
#define all(X) (X).begin(), (X).end()
typedef pair<int,int> pint;
typedef long long tint;


typedef long long tint;
struct pto { int x, y; 
	pto(int xx, int yy) : x(xx), y(yy) {} pto() :x(0),y(0){}
} r;

int cuad(const pto &a) {
	if(a.x > r.x && a.y >= r.y)return 1;
	if(a.x <= r.x && a.y > r.y)return 2;
	if(a.x < r.x && a.y <= r.y)return 3;
	if(a.x >= r.x && a.y < r.y)return 4;
	return 0; // es r
}

bool operator<(const pto& p1, const pto& p2) {
	int c1 = cuad(p1), c2 = cuad(p2);
	return (c1==c2)?((p1.y-r.y)*(p2.x-r.x)<(p1.x-r.x)*(p2.y-r.y)):(c1 < c2);
}

vector<pto> vv;

int main(void) {
	r = pto(0,0);
	forn(i, 5) forn(j, 5) vv.push_back(pto(i-2, j-2));
	sort(all(vv));
	forall(it, vv) cout << "(" << it->x << ", " << it->y << ") ";
	cout << endl << endl;

	forn(i, 5) {
		forn(j, 5) cout << vv.lower_bound(pto(i-2, j-2)) << " ";
		cout << endl;
	}

	return 0;
}

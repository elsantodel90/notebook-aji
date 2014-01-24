#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
#define forsn(i,s,n) for(int i=s;i<int(n);++i)
#define forall(i,c) for(typeof(c.begin()) i=c.begin();i!=c.end();++i)

ifstream in("test.txt");

static int aug=2,blo=1,done=0;
typedef pair<int, vector<int> > dfsres;

class node {
public:	node() { ex=true;mt=-1; }
set<int> ady; bool ex; int mt,dd;
};
vector<node> v;
void shrink(vector<int> nodes) {
	node& d=v[nodes[0]];
	forsn(i,1,nodes.size()) {
		node& p=v[nodes[i]];
		p.ex=false;	p.mt=1000;
		forall(i,p.ady) if (*i!=nodes[0]) d.ady.insert(*i);
	} d.mt=-1; d.ex=true;
}
void augpath(vector<int> nodes) { forn(i,nodes.size()) v[nodes[i]].mt=nodes[i+1-(i%2)*2]; }
int unmatched() { forn(i,v.size()) if (v[i].ex&&v[i].mt==-1&&v[i].dd==-1) return i; return -1; }
void cleardist() { forn(i,v.size()) v[i].dd=-1; }
dfsres dfs(int f, int d) {
	node& n=v[f];
	if (!n.ex) return dfsres(done,vector<int>());
	if (n.dd!=-1) {
		if (n.dd%2==d%2) return dfsres(done,vector<int>());
		else return dfsres(blo,vector<int>(1,f));
	} n.dd=d;
	if (d%2==1 && n.mt==-1) return dfsres(aug,vector<int>(1,f));
	if (d%2==1) {
		dfsres r=dfs(n.mt,d+1);
		if (r.first) {
			if (r.second[0]==f) return r;
			r.second.push_back(f);
		} return r;
	} else {
		forall(j,n.ady) if (*j!=n.mt) {
			dfsres r=dfs(*j,d+1);
			if (r.first!=0) {
				if (r.second[0]==f) return r;
				r.second.push_back(f);
				return r;
			}
		}
		return dfsres(done,vector<int>());
	}
}
int mm() {
	int u,ret=0;
	cleardist();
	while(true) {
		if ((u=unmatched())==-1) break;
		dfsres r=dfs(u,0);
		if (r.first==blo) shrink(r.second);
		else if (r.first==aug) {
			ret++; augpath(r.second);
		} else continue;
		cleardist();
	} return ret;
}
void parse(vector<string> g) {
	v=vector<node>(g.size());
	forn(i,g.size())forn(j,i) if (g[i][j]=='1')  {
		v[j].ady.insert(i);
		v[i].ady.insert(j);
	}
}
bool leer(vector<string>& g) {
	int n;
	in >> n;
	if (!n) return false;
	g=vector<string>(n);
	forn(i,n) in >> g[i];
	return true;
}
int main() {
	vector<string> g;
	while(leer(g)) {
		parse(g);
		cout << mm() << endl;
	}
	return 0;
}

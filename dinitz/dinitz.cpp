// Implementacion del problema 10330 de uva online judge.
// Incluye Dinitz.

#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cstdio>
#include <map>

using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)

#define forall(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)

// Algoritmo de Dinitz : Flujo maximo en una red de flujo dirigida.
// El caso no dirigido se obtiene simplemente seteando la capacidad igual en ambos sentidos.
// "long" se usa con semantica de flujo/capacidad (es decir, long podria ser tint o double en algunos problemas)
// Si se le pasan capacidades negativas, pone 0 en su lugar, lo cual salva de algunos bugs posibles en algunos problemas.

// Uso:
// Se llama a iniG (No le pasas la cantidad de nodos! Magia :D) Mientras los numeros de nodo v sean tales que 0 <= v < MAX_N todo bien :D
// Se va llamando a aEje agregando los ejes dirigidos, desde-hasta-capacidad .
// Despue de todo esto, se llama a flujo que te calcula el flujo, recibe S y T, fuente y sumidero.

// Se banca multiejes, ejes pa los dos lados, loops, lo que venga :D
// Lo unico, como colapsa los multiejes, si queres reconstruir el flujo y hay
// multiejes, el chabon te va a decir "Tenes que pasar tanto flujo de este nodo a este nodo",
// y eventualmente tenes que partir eso entre los multiejes que van entre esos dos nodos.
// Situacion altamente inusual, anyway, casi nunca hay que reconstruir el flujo, y si hay que
// hacerlo, en general no hay multiejes :P

// No guarda informacion para reconstruir el flujo: al final solo quedan las capacidades.
// Sin embargo, si uno quisiera reconstruirlo, bastaria con guardarse las capacidades
// originales y hacer la diferencia entre las capacidades finales y las originales.

// La representacion es lista de adyacencia.
// Los campos de cada registro de la lista (vecino, link, capacidad) se guardan en arrays paralelos.
// La lista de un nodo dado se halla en un espacio contiguo de indices.
// Mas precisamente, la lista del nodo i tiene indices [ po[i], po[i] + sz[i] )

// sz : Cantidad de vecinos de cada nodo, esto es para cada u, los v tal que (v,u) o (u,v) es arista.
//      Equivalentemente, es la longitud de la lista de adyacencia de ese nodo.
// r  : Rank (o sea, distancia a S, computada por el bfs)
// po : Posicion (indice) donde comienza la lista de adyacencia del nodo dado.

// INICIO DEL CODIGO DE DINITZ

#define INF 1000000000 // Infinito de FLUJO
#define DINF INF       // Infinito de distancia
#define MAX_M 1000000  // Maximo de aristas
#define MAX_N 45000    // Maximo de nodos
int v[2*MAX_M], l[2*MAX_M];	// Vecino, link. link te tira el indice de la arista "al reves" asociada en la lista del vecino.
long c[2*MAX_M];	// Capacidad
int sz[MAX_N], po[MAX_N], r[MAX_N], n, S, T;
typedef map<int,long> Mii;
Mii CAP[MAX_N];
void iniG() {
	n = 0;
	memset(sz,0,sizeof(sz));
	forn(i,MAX_N) CAP[i].clear();
}
void aEje(int d,int h,long cap) {
	if (d == h) return; // Ignoramos completamente autoejes, obvio :D
	n = max(n,max(d,h));
	pair<Mii::iterator,bool> par = CAP[d].insert(make_pair(h,0));
	if (par.second) {
		CAP[h][d] = 0;
		sz[d]++;
		sz[h]++;
	}
	par.first->second += max(cap,(long)0);
}
void _aEje(int d,int h,long capDH, long capHD) {
	#define ASIG(d,h,cap) {v[po[d]] = h; c[po[d]] = cap; l[po[d]] = po[h];}
	ASIG(d,h,capDH);
	ASIG(h,d,capHD);
	po[d]++; po[h]++;
}
void _iniG() {
	po[0] = 0;
	forn(i,n-1) po[i+1] = po[i] + sz[i];
	forn(u,n) forall(v,CAP[u])
		if (u < v->first) _aEje(u,v->first,v->second,CAP[v->first][u]);
}
long aumentar() {
	// bfs
	forn(i,n) r[i] = DINF;
	r[T] = 0;
    static int q[MAX_N];
    int qf = 0, qb = 0;
	q[qb++] = T;
	while (qb != qf) {
		int x = q[qf++];
		int d = r[x] + 1, b = po[x];
		if (r[S] < DINF) break;
		forsn(j,b,b+sz[x])
		if (c[l[j]]>0 && r[v[j]] == DINF) {
			r[v[j]] = d;
			q[qb++] = v[j];
		}
	}
	// dfs que hace la magia :P
	long res = 0;
	static int path[MAX_N]; path[0] = S;
	static int p[MAX_N],ind[MAX_N];
    forn(i,n) p[i] = -1;
	int pp = 0; // Path pointer, es la longitud
	while (pp >= 0)	{
		int x = path[pp];
		if (x == T)	{ // Llegamo, hay que hacer magia. O sea, ajustar todas las capacidades a lo largo del caminito que se satura.
			long f = INF;
			int pri = 0;
			dforn(i,pp)	if (c[ind[i]]<=f) f = c[ind[i]], pri = i;
			forn(i,pp) c[ind[i]] -= f, c[l[ind[i]]] += f;
			res += f;
			pp = pri;
		}
		else if (++p[x] < sz[x]) {
			int j = po[x]+p[x];
			if (p[v[j]] < 0 && c[j] > 0 && r[v[j]] < r[x])
				ind[pp] = j, path[++pp] = v[j];
		}
		else pp--;
	}
	return res;
}
long flujo(int ss,int tt) {
	S = ss; T = tt;
	n = max(n,max(S,T)) + 1; // Aca, n ya tiene el valor posta
	_iniG();
	forn(i,n) po[i] -= sz[i];
	
	long res = 0,c;
	do {res += (c = aumentar());} while (c>0);
	return res;
}

// FIN DEL CODIGO DE DINITZ

int main()
{
	#ifdef ACMTUYO
		stdin = freopen("entrada.in","r",stdin);
	#endif
	int n;
	while(cin >> n)
	{
		iniG();
		forn(i,n)
		{
			int c;
			cin >> c;
			aEje(2*i,2*i+1,c);
		}
		int M; cin >> M;
		forn(tt,M)
		{
			int i, j, c;
			cin >> i >> j >> c;
			i--;j--;
			aEje(2*i+1,2*j,c);
		}
		const int S = 2*n, T = 2*n+1;
		int B,D;
		cin >> B >> D;
		forn(i,B)
		{
			int x; cin >> x;
			x--;
			aEje(S,2*x,INF);
			
		}
		forn(i,D)
		{
			int x; cin >> x;
			x--;
			aEje(2*x+1,T,INF);
		}
		cout << flujo(S,T) << endl;
	}
}

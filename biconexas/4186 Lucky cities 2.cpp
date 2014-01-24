#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
using namespace std;
#define forn(i,n) for(int i=0; i<int(n); i++)
#define forsn(i,s,n) for(int i=(s); i<int(n); i++)
#define dforn(i,n) for(int i = int(n) - 1; i >= 0; i--)
#define forall(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define dforall(i,c) for(__typeof((c).rbegin()) i = (c).rbegin(); i != (c).rend(); i++)
#define all(c) (c).begin(), (c).end()
#define esta(v,c) ((c).find(v) != (c).end())
#define zMem(c) memset((c), 0, sizeof(c))
#define pb push_back
#define x first
#define y second
const int INF = 1000000000;
typedef long long tint;
typedef long double tdbl;
typedef pair<int,int> pint;
#define adj g
const int MAXN = 100100;
vector<int> adj[MAXN];
int N, M;


/**************************************************************************/
/***************************     HORROR      ******************************/
/**************************************************************************/
/**************************************************************************/

//#define DEBUG

bool lucky[MAXN];
int compoV[2*MAXN], compoVSz, Q[2*MAXN];
vector<int> compo[MAXN];
char color[MAXN];
void COMPO_START()
{
    #ifdef DEBUG
        cout<<endl<<"COMPO START"<<endl;
    #endif
    compoVSz = 0;
}
void COMPO_EDGE(int u, int v)
{
    #ifdef DEBUG
        cout<<"COMPO EDGE: "<<u+1<< " " << v+1 << endl;
    #endif
    compo[u].pb(v);compo[v].pb(u);
}
void COMPO_V(int v)
{compoV[compoVSz++] = v;}
void COMPO_END()
{
    #ifdef DEBUG
        cout << "COMPONENT: ";
        forn(i, compoVSz) cout << compoV[i] + 1 << " "; cout << endl;
    #endif
    
    if(compoVSz > 2)
    {
        forn(i, compoVSz)color[compoV[i]] = -1;
        int b = 0, f = 0;
        color[Q[f++] = compoV[0]] = 0;
        bool anda = false;
        #ifdef DEBUG
            cout << endl << "INICIO BFS: " << endl;
        #endif
        while(b < f)
        {
            int act = Q[b++];
            #ifdef DEBUG
                cout << "ACT: " << act + 1<< endl;
            #endif
            forall(nue, compo[act])
            {
                #ifdef DEBUG
                cout << "  NUE: " << *nue + 1 << endl;
            #endif
                if(color[*nue] != -1){
                    if(!(color[*nue] ^ color[act]))
                    {
                    #ifdef DEBUG
                        cout << "EPA!" << endl;
                    #endif
                    anda = true; break; }
                }
                else{
                    color[Q[f++] = *nue] = 1 ^ color[act];
                    #ifdef DEBUG
                        cout << "    COLOR: " << (int)(color[*nue]) << endl;
                    #endif
                }
            }
            if(anda) break;
        }
        if(anda) forn(i, compoVSz) lucky[compoV[i]] = true;
        #ifdef DEBUG
            cout << "FIN BFS: " << anda << endl << endl;
        #endif
    }
    forn(i, compoVSz)compo[compoV[i]].clear();
    #ifdef DEBUG
        cout<<"COMPO END"<<endl<<endl;
    #endif
}


/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

/**const char empezar = 0, pasivo = 1, activo = 2;
int pila[2 * MAXN], pilas;
char estado[MAXN];
int depth[MAXN], low[MAXN], j[MAXN], i[MAXN];
int S[2 * MAXN], K, ant[MAXN], tiempo;
void component()
{
    int root = pila[--pilas];
    COMPO_START();
    COMPO_V(root);
    for (int act = pila[pilas - 1]; act != root; act = pila[(--pilas) - 1]) {
        COMPO_V(act);
        if (depth[pila[pilas - 2]] < depth[act])
            forn(k, j[act]) COMPO_EDGE(act, adj[act][k]);
    }
    COMPO_END();
}
// asume depth[u] == -1 y back[u].size() == 0
void dfs (int root) {
    tiempo = 0;
    pilas = 0;
    ant[root] = -1;
    estado[root] = empezar;
    K = 0; S[K++] = root;
    
    while (K) {
        int act = S[--K], nue;
        switch (estado[act]) {
        case empezar:
            low[act] = depth[act] = tiempo++;
            pila[pilas++] = act;
            j[act] = i[act] = 0;
            estado[act] = pasivo;
            S[K++] = act;
            break;
        case pasivo:
            if (i[act] == (int)adj[act].size())
                break;
            nue = adj[act][i[act]];
            if (depth[nue] == -1) {
                //if(act == root and i[act]) ARTICULATION(act);
                ant[nue] = act;
                estado[act] = activo;
                S[K++] = act;
                estado[nue] = empezar;
                S[K++] = nue;
            } else {
                if (nue != ant[act])
                    low[act] = min(low[act], depth[nue]);
                if (depth[nue] < depth[act])
                    swap(adj[act][j[act]++], adj[act][i[act]]);
                i[act]++;
                estado[act] = pasivo;
                S[K++] = act;
            }
            break;
        case activo:
            nue = adj[act][i[act]];
            pila[pilas++] = act;
            low[act] = min(low[act], low[nue]);
            //if (low[nue] >= depth[act] and act != root) ARTICULATION(act);
            //if (low[nue] >= depth[nue]) BRIDGE(act, nue);
            if (low[nue] >= depth[act])
                component();
            i[act]++;
            estado[act] = pasivo;
            S[K++] = act;
            break;
        }
    }
}
void biconnectedComponents()
{
    forn(i, N) depth[i] = -1;
    forn(i, N) if(depth[i] == -1) dfs(i);
}**/

// VERSION ii:

inline void swap(int&a,int&b){int c;c=a,a=b,b=c;}





/** INICIO DE CÓDIGO DE COMPONENTES BICONEXAS, PUENTES Y PUNTOS DE ARTICULACIÓN **/
/** g es la lista de adyacencia de un grafo en forma vector<int>, N es cantidad de vértices,
 *  MAXN es una cota superior tanto para cantidad de vértices como cantidad de aristas**/

int D[MAXN], L[MAXN], J[MAXN], I[MAXN]; char E[MAXN];
int P[2 * MAXN], R, S[2 * MAXN], K, A[MAXN], T;
void component() {
    int r = P[--R]; COMPO_START(); COMPO_V(r);
    for (int u = P[R - 1]; u != r; u = P[--R - 1]) {
        COMPO_V(u);
        if (D[P[R - 2]] < D[u]) forn(i, J[u]) COMPO_EDGE(u, g[u][i]);
    } COMPO_END();
}
void dfs (int r) {
    E[r] = K = T = R = 0; A[S[K++] = r] = -1;
    while (K) { int u = S[--K], v;
        switch (E[u]) {
        case 0: L[u] = D[u] = T++; J[u] = I[u] = 0; P[R++] = u;
        case 1: c1: if (I[u] == (int)g[u].size()) break;
            if (D[v = g[u][I[u]]] == -1) {
                //if(u == r and I[u]) ARTICULATION(u);
                E[A[v] = S[K++] = u] = 2, E[S[K++] = v] = 0;
            } else { if (v != A[u] && D[v] < L[u]) L[u] = D[v];
                if (D[v] < D[u]) swap(g[u][J[u]++], g[u][I[u]]); //COMP
                I[u]++; E[S[K++] = u] = 1;
            } break;
        case 2: v = g[u][I[u]], P[R++] = u;
            if (L[v] < L[u]) L[u] = L[v];
            //if (L[v] >= D[u] && u != r) ARTICULATION(u);
            //if (L[v] >= D[v]) BRIDGE(u, v);
            if (L[v] >= D[u]) component(); //COMP
            I[u]++; goto c1;
        }
    }
}
void BC()
{
    forn(i, N) D[i] = -1;
    forn(i, N) if(D[i] == -1) dfs(i);
}

/** FIN DE CÓDIGO **/






int main()
{
	#ifdef ACMTUYO
        freopen("D.IN", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int TT; cin >> TT;
    forn(tt, TT)
    {
        cin >> N >> M;
        forn(i, N) g[i].clear(), lucky[i] = false;
        forn(m, M)
        {
            int u, v; cin >> u >> v; u--, v--;
            g[u].pb(v); g[v].pb(u);
        }
        BC();
        int res = 0;
        forn(i, N) if(lucky[i]) res++;
        cout << res << endl;
    }
    
	return 0;
}

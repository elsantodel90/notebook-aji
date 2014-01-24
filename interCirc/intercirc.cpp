#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(int)(n);i++)

#define all(c) (c).begin(),(c).end()

#define DBG(x) cerr << #x << " = " << (x) << endl

// A continuacion, codigo milagroso que computa interseccion, union, y similares,
// de n circunferencias, en O(n^3 lg n). Para el problema este chupa un huevo
// la complejidad porque n = 4, pero el codigo este puede servir.
// Lo que hace es tirar rayas verticales en lugares "interesantes" y en el medio
// integra (por formula :D) cachos de arco de circunferencia, y con lo que le queda
// el tipo resuelve "interseccion / union / similares"  de segmentos.

typedef double real; // abstraccion magica

struct pto
{
	real x,y;
	pto() : x(0),y(0) {}
	pto(real xx, real yy) : x(xx),y(yy) {}
	pto operator +(const pto &o) const { return pto(x+o.x,y+o.y); }
	pto operator -(const pto &o) const { return pto(x-o.x,y-o.y); }
	pto operator *(real k) const { return pto(k*x,k*y); }
	real norma() const { return hypot(x,y); }
	pto rotar(real alfa) const { return pto(x * cos(alfa) - y * sin(alfa), x* sin(alfa) + y * cos(alfa)); }
};

struct circ { pto c; real r; };

#define sqr(x) ((x)*(x))

struct event
{
	real x; int t; 
	event(real xx, int tt) : x(xx), t(tt) {}
	bool operator <(const event &o) const { return x < o.x; }
};

typedef vector<circ> VC;
typedef vector<event> VE;

real cuenta(VE &v, real A,real B)
{
	sort(all(v));
	real res = 0.0, lx = ((v.empty())?0.0:v[0].x);
	int contador = 0;
	forn(i,v.size())
	{
		// Esta es la linea magica que hay que tocar.
		// Cambiando trivialmente el if, hacemos que compute interseccion de todos (contador == n),
		// union de todos (contador > 0), conjunto de puntos cubierto por exactamente k circulos (contador == k),
		// etc. En este caso, le estamos pidiendo los puntos que son tocados por 1,2 o 3
		// circulos, que es lo que queremos pal problema del robotito que tira rayitos :D
		if (contador > 0 && contador < 4) res += v[i].x - lx;
		contador += v[i].t;
		lx = v[i].x;
	}
	return res;
}

const real PI = 4.0 * atan(1.0);

// La siguiente da una primitiva de sqrt(r*r - x*x) como funcion real de una variable x.
// Los bordes estan puestos estrategicamente para que todo ande joya :D
inline real primitiva(real x,real r)
{
	if (x >= r) return r*r*PI/4.0;
	if (x <= -r) return -r*r*PI/4.0;
	real raiz = sqrt(r*r-x*x);
	return 0.5 * (x * raiz + r*r*atan(x/raiz));
}

// Se llama asi pero en realidad calcula la funcion que calcule "cuenta" en base a los "intervalos" que esta le arma.
// Puede ser interseccion, union, o incluso algunas cosas mas locas :D.
real interCirc(const VC &v)
{
	vector<real> p; p.reserve(v.size() * (v.size() + 2));
	forn(i,v.size())
	{
		p.push_back(v[i].c.x + v[i].r);
		p.push_back(v[i].c.x - v[i].r);
	}
	forn(i,v.size())
	forn(j,i)
	{
		const circ &a = v[i], b = v[j];
		real d = (a.c - b.c).norma();
		if (fabs(a.r - b.r) < d && d < a.r + b.r)
		{
			real alfa = acos((sqr(a.r) + sqr(d) - sqr(b.r)) / (2.0 * d * a.r));
			pto vec = (b.c - a.c) * (a.r / d);
			p.push_back((a.c + vec.rotar(alfa)).x);
			p.push_back((a.c + vec.rotar(-alfa)).x);
		}
	}
	sort(all(p));
	real res = 0.0;
	forn(i,p.size()-1)
	{
		const real A = p[i], B = p[i+1];
		VE ve; ve.reserve(2 * v.size());
		forn(j,v.size())
		{
			const circ &c = v[j];
			real arco = primitiva(B-c.c.x,c.r) - primitiva(A-c.c.x,c.r);
			real base = c.c.y * (B-A);
			ve.push_back(event(base + arco,-1));
			ve.push_back(event(base - arco, 1));
		}
		res += cuenta(ve,A,B);
	}
	return res;
}

// Aca terminaria el codigo de interseccion de n circunferencias.

// Empieza la parte del problema particular del robotito que tira los dos rayitos :D.

VC v;

bool leer()
{
	bool res = false;
	pto p[4];
	forn(i,4) 
	{
		cin >> p[i].x >> p[i].y;
		res = res || p[i].x || p[i].y;
	}
	v.clear();
	forn(i,2)
	forsn(j,2,4)
	{
		circ aux;
		aux.c = (p[i] + p[j]) * 0.5;
		aux.r = (p[i] - p[j]).norma() * 0.5;
		v.push_back(aux);
	}
	return res;
}

int main()
{
	#ifdef ACMTUYO
		stdin = freopen("entrada.in","r",stdin);
	#endif
	int tt = 0;
	while (leer()) printf("Case %d: %.3lf\n\n",++tt,(double)interCirc(v));
	return 0;
}

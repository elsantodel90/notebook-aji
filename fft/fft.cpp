#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <assert.h>
#include <complex>

using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)

#define zMem(c) memset((c),0,sizeof(c))

// Inicio del FFT + Convolucion, incluyendo complejo

typedef double tipo;
// Tipo debe ser un tipo de punto flotante

struct Comp
{
	tipo r,i;
	Comp() : r(0), i(0) {}
	Comp(tipo rr) : r(rr), i(0) {}
	Comp(tipo rr, tipo ii) : r(rr), i(ii) {}
	Comp operator + (const Comp &o) const { return Comp(r + o.r, i + o.i); }
	Comp operator - (const Comp &o) const {	return Comp(r - o.r, i - o.i); }
	Comp operator * (const Comp &o) const {	return Comp(r * o.r - i * o.i,r * o.i + o.r * i); }
	Comp & operator += (const Comp &o) { return *this = *this + o; }
	Comp & operator *= (const Comp &o) { return *this = *this * o; }
};

#define MAXN (1<<21)	// Debe ser potencia de 2
						// Si se esta usando convolucion, debe ser
						// al menos 2 * n

const tipo PI = 4.0 * atan(1.0);

unsigned bTabla[(1<<16)]; 	// Es importante que sea unsigned para que al hacer shift right
							// haga shift logico y no shift aritmetico.

// Se llama a llenarTabla una vez al comienzo del programa.

void llenarTabla()
{
	bTabla[0] = 0;
	forn(i,16)
	{
		int s = (1<<i);
		forn(j,s) bTabla[s + j] = (bTabla[j] *= 2)+1;
	}
}

struct Fft
{
	// Tipo debe ser un tipo de punto flotante
	int n,nk;
	Comp v[MAXN];
	Comp *init(int nn)
	{
		for(n = 1, nk = 32; n < nn; n *= 2, nk--);
		zMem(v);
		return v;
	}
	Comp *fft()
	{
		forn(i,n)
		{
			int j = (((bTabla[i&0xFFFF] << 16) | bTabla[i>>16]) >> nk);
			if (j > i) swap(v[i],v[j]);
		}
		for(int i=2;i<=n; i+=2)
		{
			int s = 1, x = i;
			while (x%2 == 0)
			{
				x /= 2;
				Comp w1 = 1.0;
				const Comp w(cos(PI/tipo(s)),-sin(PI/tipo(s)));
				Comp *A = v+i-2*s, *B = v+i-s, *FIN = v+i;
				// Cuello de botella : este for.
				// En particular, las dos multiplicaciones.
				for(;B != FIN;A++,B++)
				{
					Comp X = *A, Y = w1 * *B;
					*A += Y;
					*B = X - Y;
					w1 *= w;
				}
				s *= 2;
			}
		}
		
		return v;
	}
	Comp *invfft()
	{
		reverse(v+1,v+n);
		forn(i,n) v[i] *= 1.0 / tipo(n);
		return fft();
	}
	// Uso:
	// Se llama a init, se llena el vector en el puntero devuelto.
	// Se llama a fft o a invftt, segun lo buscado.
	// El output aparece en el puntero devuelto.
};

struct Convolucion
{
	// Tipo debe ser un tipo de punto flotante
	Fft fft;
	Comp v[MAXN]; // Se usa el MAXN de fft
	Comp* init(int n)
	{
		return fft.init(2*n);
	}
	Comp *next()
	{
		fft.fft();
		memcpy(v,fft.v,sizeof(v));
		zMem(fft.v);
		return fft.v;
	}
	Comp *conv()
	{
		fft.fft();
		forn(i,fft.n)
			fft.v[i] *= v[i];
		return fft.invfft();
	}
	// Uso:
	// Se llama a init, se llena el primer vector en el puntero devuelto.
	// Se llama a next, se llena el segundo vector en el puntero devuelto.
	// Se llama a conv, la convolucion aparece en el puntero devuelto.
};

// Fin del FFT + Convolucion

ostream &operator<<(ostream &os, const Comp &z)
{
	#define EPS 1e-10
	#define FNZ(x) (fabs(x) > EPS)
	bool a = FNZ(z.r), b = FNZ(z.i);
	if (a) os << z.r;
	if (a && b) os << " + ";
	if (b) os << z.i << "i";
	if (!(a||b)) os << "0";
	return os;
}

int main()
{
	/*
	static Fft fft;
	int n; cin >> n;
	Comp *v = fft.init(n);
	forn(i,n) {tipo x; cin >> x; v[i] = x;}
	fft.invfft();
	memcpy(fft.v,fft.o,sizeof(fft.o));
	v = fft.fft();
	forn(i,n) cout << v[i] << endl;
	*/
	llenarTabla();

	static Convolucion c;
	//int n = MAXN/2;
	int n;cin >> n;
	
	Comp * v = c.init(n);
	//cerr << "VA!" << endl;
	forn(i,n) {tipo x; cin >> x; v[i] = x;}
	//forn(i,n) v[i] = Comp(1.2222,7.321);
	//cerr << "N1!" << endl;
	v = c.next();
	forn(i,n) {tipo x; cin >> x; v[i] = x;}
	//forn(i,n) v[i] = Comp(-7.321,1.22332);
	//cerr << "N2!" << endl;
	v = c.conv();
	//cerr << "Fin!" << endl;
	forn(i,2*n-1) printf("%lf ",(double)v[i].r);
	printf("\n");
	return 0;
}

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define forn(i,n) for(int i=0;i<(int)(n);++i)
#define forsn(i,s,n) for(int i=(s);i<(int)(n);++i)

typedef long double tipo;

/* Codigo para el notebook */

typedef vector<vector<tipo> > Mat;
typedef vector<tipo> Vec;
tipo sqr(tipo x) {return x*x;}

void show(Mat &a);

void qr(const Mat &a, Mat &q, Mat &r) {
	int n = a.size();
	r = a;
	q = Mat(n, Vec(n, 0));
	forn(i, n) forn(j, n) q[i][j] = (i==j);

	forn(k, n-1) {
		tipo beta = 0;
		forsn(i, k, n) beta += sqr(r[i][k]);
		tipo alph = sqrt(beta);
		if (alph * r[k][k] >= 0) alph = -alph;

		Vec v(n, 0);
		forsn(i, k, n) v[i] = r[i][k]; v[k] -= alph;
		beta += sqr(v[k]) - sqr(r[k][k]);

		#define QRmult(X) \
		forn(i, n) { tipo w = 0; \
			forsn(j, k, n) w += X * v[j]; w /= beta/2; \
			forsn(j, k, n) X -= w * v[j]; }

		// Q := Q * (I - 2 v * v^t) = Q - 2 * ((Q * v) * v^t)
		QRmult(q[i][j]);
		// A := Qj * A; \equiv A^t := A^t * Qj;
		QRmult(r[j][i]);

		forsn(i, k+1, n) r[i][k] = 0;
	}
}

// Hessenberg decomp. A=P*H*P^t, P unitary, H hessenberg
void hes(const Mat &a, Mat &p, Mat &h) {
	int n = a.size();
	h = a;
	p = Mat(n, Vec(n, 0));
	forn(i, n) forn(j, n) p[i][j] = (i==j);

	forn(k, n-2) {
		tipo beta = 0;
		forsn(i, k+1, n) beta += sqr(h[i][k]);
		tipo alph = sqrt(beta);
		if (alph * h[k+1][k] >= 0) alph = -alph;

		Vec v(n, 0);
		forsn(i, k+1, n) v[i] = h[i][k]; v[k+1] -= alph;
		beta += sqr(v[k+1]) - sqr(h[k+1][k]);

		// Q := Q * (I - 2 v * v^t) = Q - 2 * ((Q * v) * v^t)
		QRmult(p[i][j]);
//		// A := Qj * A; \equiv A^t := A^t * Qj;
//		QRmult(h[j][i]);

		// A := Qj * A; \equiv A^t := A^t * Qj;
		QRmult(h[j][i]);
		// A := A * Qj^t; \equiv A := A * Qj;
		QRmult(h[i][j]);

		forsn(i, k+1, n) h[i][k] = 0;
	}
}

// QR para calcular autvalores (no estoy seguro de para qué matrices sirve)
Mat operator* (const Mat &ml, const Mat &mr) {
	int a = ml.size(), b = mr.size(), c = mr[0].size();
	Mat res(a, Vec(c, 0));
	forn(i, a) forn(j, c) forn(k, b) res[i][j] += ml[i][k] * mr[k][j];
	return res;
}

#define iterac 1000
void autoval(Mat &a) {
	int n = a.size();
	Mat q(n, Vec(n, 0));
	forn(i, iterac) {
		qr(a, q, a);
		a = a * q;
	}
	// Los autovalores convergen en la diagonal de "a"
}

/* Fin codigo para el notebook */

void show(Mat &a) {
	forn(i, a.size()) {
		forn(j, a[i].size()) {
			if (j == (int)a.size()) cout << "| ";
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

tipo abserr(const Mat &a, const Mat &b) {
	tipo res = 0;
	forn(i, a.size()) forn(j, a[i].size()) res += fabs(a[i][j]-b[i][j]);
	return res;
}

int main(void) {
	freopen("qr.in","r",stdin);
	/* Formato de archivo:
		n
		A
	*/

	int n, tt = 0;

	while (cin >> n, n) {
		Mat a(n, Vec(n, 0));
		forn(i, n) forn(j, n) cin >> a[i][j];
		Mat q, r;
		qr(a, q, r);

		cout << "Test " << tt << " : QR decomposition" << endl;
		cout << "A = " << endl; show(a);
		cout << "Q = " << endl; show(q);
		cout << "R = " << endl; show(r);
		cout << endl;

		cout << "Test " << tt << " : Hessenberg decomposition" << endl;
		hes(a, q, r);
		cout << "P = " << endl; show(q);
		cout << "H = " << endl; show(r);

		Mat t = r * q * r;
		cout << "abserr: " << abserr(t, a) << endl;

		autoval(a);
		cout << "autoval(A) = " << endl; show(a);

	}	
}

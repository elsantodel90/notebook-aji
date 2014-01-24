// MALE OPTIMAL STABLE MARRIAGE PROBLEM O(N^2)
// gv[i][j] es la j esima mujer en orden de preferencia en la lista del varon i
// om[i][j] es la posicion que ocupa el hombre j en la lista de la mujer i
#define MAXN 1000
int gv[MAXN][MAXN],om[MAXN][MAXN]; // Inpu del algoritmo
int pv[MAXN],pm[MAXN];             // Oupu del algoritmo
int pun[MAXN];                     // Auxiliar

void stableMarriage(int n) {
	fill_n(pv,n,-1); fill_n(pm,n,-1); fill_n(pun,n,0);
	int s = n, i = n-1;
	#define engage pm[j] = i; pv[i] = j;
	while (s) {
		while (pv[i] == -1) {
			int j = gv[i][pun[i]++];
			if (pm[j] == -1) {
				s--;
				engage;
			}
			else if (om[j][i] < om[j][pm[j]]) {
				int loser = pm[j];
				pv[loser] = -1;
				engage;
				i = loser;
			}
		}
		i--;
		if (i < 0) i = n-1;
	}
}
#include <bits/stdc++.h>
using namespace std;

// inicialización de matrices de costos
map< char, int> ins;
map< pair<char,char>, int> sub;
map< char, int> del;
map< pair<char,char>, int> trans;

// generacios matrices de costo
void datasets( string nombre, int n, int m ){
	fstream arch;
	arch.open(nombre, ios::out);

	if(n==1){ n--; }
	vector<vector<int>> matriz(n + 1, vector<int>(m + 1, -1));

    for(int i=0; i<=n; i++){
        for(int j=0; j<=m; j++){
            int c;
            if (i == j) { c = 0;
            } else if (matriz[i][j] != -1) { c = matriz[i][j];
            } else {
                c = rand() % 10;
                matriz[i][j] = c;
                if (j <= n && i <= m) {
                    matriz[j][i] = c;
                }
            }
            arch << c << " ";
        }
        arch << "\n";
    }
    arch.close();
}

// funciones de costos
int costo_ins(char b){
	int costo;
	costo = ins[b];
	return costo;
}

int costo_sub(char a, char b){
	int costo;
	costo = sub[{a,b}];
	return costo;
}

int costo_del(char a){
	int costo;
	costo = del[a];
	return costo;
}

int costo_trans(char a, char b){
	int costo;
	costo = trans[{a,b}];
	return costo;
}

int main(){
	string strin, strout;
	cin >> strin >> strout;

	int n = strin.length(), m = strout.length();
	// n - primera columna; m - rellena filas en 0
	datasets( "cost_insert.txt", 1, m);
	datasets( "cost_delete.txt", 1, n);
	datasets( "cost_replace.txt", n, m);
	datasets( "cost_transpose.txt", n, m);

	vector< vector<int> > ans(n+1, vector<int>(m+1, 0));


	//////// lecutra de archivos de costos
	// archivo insertar
	fstream file; int cos;
	file.open("cost_insert.txt", ios::in);
	for(int j=0; j<m; j++){
		file >> cos;
		ins[strout[j]] = cos;
	}
	file.close();

	// archivo sustituir
	file.open("cost_replace.txt", ios::in);
	for(int j=0; j<m; j++){
		for(int i=0; i<n; i++){
			file >> cos;
			sub[{strin[i],strout[j]}] = cos;
		}
	}
	file.close();

	// archivo eliminar
	file.open("cost_delete.txt", ios::in);
	for(int i=0; i<n; i++){
		file >> cos;
		del[strin[i]] = cos;
	}
	file.close();

	// archivo transponer
	file.open("cost_transpose.txt", ios::in);
	for(int j=0; j<m; j++){
		for(int i=0; i<n; i++){
			file >> cos;
			trans[{strin[i],strout[j]}] = cos;
		}
	}
	file.close();
	//////// fin de la lecutra de archivos

	for(int i=1; i<=n; i++){ ans[i][0] = ans[i-1][0]+costo_del(strin[i-1]);	}
	for(int j=1; j<=m; j++){ ans[0][j] = ans[0][j-1]+costo_ins(strout[j-1]); }

	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if( strin[i-1]==strout[j-1] ){
				ans[i][j] = ans[i-1][j-1];
			} else {
				ans[i][j] = min({
					// mantener C e insertar U
					ans[i][j-1] + costo_ins(strout[j-1]),
					// borrar C e insertar CU
					costo_del(strin[i-1]) + ans[i-1][j],
					// mantener C y sustituir U por A
					ans[i-1][j-1] + costo_sub(strin[i],strout[j])
				});

                if (i>1 && j>1 && strin[i-1] == strout[j-2]) {
                    ans[i][j] = min(ans[i][j], ans[i-2][j-2] + costo_trans(strin[i-2], strin[i-1]));
                }
			}
		}
	}

	cout << "Distancia Mínimo de Edición: " << ans[n][m] << endl;
	return 0;
}
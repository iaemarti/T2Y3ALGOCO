#include <bits/stdc++.h>
using namespace std;

// inicialización de matrices de costos
map< char, int> ins;
map< pair<char,char>, int> sub;
map< char, int> del;
map< pair<char,char>, int> trans;

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
	getline(cin, strin);
    if(strin.empty()) { strin = ""; }

    getline(cin, strout);
    if(strout.empty()) { strout = ""; }

	int n = strin.length(), m = strout.length();
	// n - primera columna; m - rellena filas en 0

	vector< vector<int> > ans(n+1, vector<int>(m+1, 0));

	string claves = "abcdefghijklmnopqrstuvwxyz";
	//////// lecutra de archivos de costos
	// archivo insertar
	fstream file; int cos;
	file.open("cost_insert.txt", ios::in);
	for(int j=0; j<=26; j++){
		file >> cos;// cout << cos << " ";
		ins[claves[j]] = cos;
	}
	//cout << endl;
	file.close();

	// archivo sustituir
	file.open("cost_replace.txt", ios::in);
	for(int i=0; i<=26; i++){
		for(int j=0; j<=26; j++){
			file >> cos;// cout << cos << " ";
			sub[{claves[i],claves[j]}] = cos;
		}
		//cout << endl;
	}
	file.close();

	// archivo eliminar
	file.open("cost_delete.txt", ios::in);
	for(int i=0; i<=26; i++){
		file >> cos;// cout << cos << " ";
		del[claves[i]] = cos;
	}
	//cout << endl;
	file.close();

	// archivo transponer
	file.open("cost_transpose.txt", ios::in);
	for(int i=0; i<=26; i++){
		for(int j=0; j<=26; j++){
			file >> cos;// cout << cos << " ";
			trans[{claves[i],claves[j]}] = cos;
		}
		//cout << endl;
	}
	file.close();
	//////// fin de la lecutra de archivos

	//int total = 0;
	//for(int i=0;i<5;i++){
	auto start = chrono::steady_clock::now();
	for(int i=1; i<=n; i++){ ans[i][0] = ans[i-1][0]+costo_del(strin[i-1]);	}
	for(int j=1; j<=m; j++){ ans[0][j] = ans[0][j-1]+costo_ins(strout[j-1]); }

	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if( strin[i-1]==strout[j-1] ){
				ans[i][j] = ans[i-1][j-1];
			} else {
				ans[i][j] = min({
					ans[i][j-1] + costo_ins(strout[j-1]),
					costo_del(strin[i-1]) + ans[i-1][j],
					ans[i-1][j-1] + costo_sub(strin[i],strout[j])
				});

                if (i>1 && j>1 && strin[i-1] == strout[j-2]) {
                    ans[i][j] = min(ans[i][j], ans[i-2][j-2] + costo_trans(strin[i-2], strin[i-1]));
                }
			}
		}
	}
		/*
		cout << "Distancia Mínima de Edición: " << ans[n][m] << endl;
		auto end = chrono::steady_clock::now();
    		auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	    	total += duration;
	}*/
	
	cout << "Distancia Mínima de Edición: " << ans[n][m] << endl;
	auto end = chrono::steady_clock::now();
    	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
   	cout << "Tiempo de Ejecución:" << duration << endl;
   	
   	//cout << "Tiempo de Ejecución:" << total/5 << endl;
	return 0;
}

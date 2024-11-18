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

// funcion de recursión
int distancia(string input, string output, int i, int j){
	if(i == int(input.size())){ return output.size()-j; }
	if(j == int(output.size())){ return input.size()-i; }

	if( input[i]==output[j] ){ return distancia(input, output, i+1, j+1); }

	int ins = distancia(input, output, i, j+1);
	int del = distancia(input, output, i+1, j);
	int rep = distancia(input, output, i+1, j+1);
	int trans = INT_MAX;
	if( i+1<int(input.size()) && j+1<int(output.size()) && input[i+1]==output[j] ){ trans = distancia(input, output, i+2, j+2); }

	int dm = min({ins, del, rep, trans});

	if(dm==ins){ return costo_ins(output[j]) + dm;
	} else if(dm==del){ return costo_del(input[i]) + dm;
	} else if(dm==rep){ return costo_sub(input[i],output[j]) + dm;
	} else { return costo_trans(input[i],input[i+1]) + dm;
	}
}


int main(){
	string strin, strout;
	cin >> strin >> strout;

	int n = strin.length(), m = strout.length();
	datasets( "cost_insert.txt", 1, m);
	datasets( "cost_delete.txt", 1, n);
	datasets( "cost_replace.txt", n, m);
	datasets( "cost_transpose.txt", n, m);

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

	// contadores en cero para recorrer strings en la función
	int i = 0, j = 0;
	int dm = distancia(strin, strout, i, j);
	cout << "Distancia Mínimo de Edición: " << dm << endl;

	return 0;
}
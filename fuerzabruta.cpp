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
	getline(cin, strin);
    if(strin.empty()) { strin = ""; }

    getline(cin, strout);
    if(strout.empty()) { strout = ""; }

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

	/*
	int total = 0;
	for(int i=0;i<5;i++){
		auto start = chrono::steady_clock::now();
		// contadores en cero para recorrer strings en la función
		int dm = distancia(strin, strout, 0, 0);
		cout << "Distancia Mínima de Edición: " << dm << endl;
		auto end = chrono::steady_clock::now();
	    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	    total += duration;
	    cout << "Tiempo de Ejecución:" << total/5 << endl;
	}
	*/
	auto start = chrono::steady_clock::now();
	// contadores en cero para recorrer strings en la función
	int dm = distancia(strin, strout, 0, 0);
	cout << "Distancia Mínima de Edición: " << dm << endl;
	auto end = chrono::steady_clock::now();
    	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
   	cout << "Tiempo de Ejecución:" << duration << endl;

	return 0;
}

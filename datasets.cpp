#include <bits/stdc++.h>
using namespace std;

// generacios matrices de costo
void datasets( string nombre, int filas){
	fstream arch;
	arch.open(nombre, ios::out);

	vector<vector<int>> matriz(filas+1, vector<int>( 27, -1));

    for(int i=0; i<filas; i++){
        for(int j=0; j<26; j++){
            int c;
            if( i==j && filas!=1 ){ c = 0;
            } else if ( matriz[i][j]!=-1 ){ c = matriz[i][j];
            } else {
                c = (rand() % 9)+1;
                matriz[i][j] = c;
                if (j < filas && i < 26){
                    matriz[j][i] = c;
                }
            }
            arch << c << " ";
        }
        arch << "\n";
    }
    arch.close();
}

int main(){

	datasets( "cost_insert.txt", 1);
	datasets( "cost_delete.txt", 1);
	datasets( "cost_replace.txt", 26);
	datasets( "cost_transpose.txt", 26);

	return 0;
}

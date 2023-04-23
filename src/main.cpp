#include "Jogo.hpp"
#include <tuple>
 
using namespace std;

int main(){

    clock_t inicio, termino;
    inicio = clock();

    Jogo* jogo = new Jogo();
    string** matriz;
    unsigned short int tamanho=0, quantidade=0; 
    auto resultado = jogo->tamanho_quantidade_matriz(); 
    
    tamanho = get<0>(resultado);
    quantidade = get<1>(resultado);
    matriz = new string * [tamanho];
    for (int i=0; i < tamanho; i++){
        matriz[i] = new string[tamanho];
    }
    jogo->iniciar_partida(matriz, tamanho, quantidade);
    
    termino = clock();
    cout << "\nTEMPO DE EXECUCAO: " << (float(termino-inicio) / CLOCKS_PER_SEC) << " segundos.\n" << endl;
    cout << "\t\t\t\t====[FIM]====\t\t\n\n";

    return 0;
}
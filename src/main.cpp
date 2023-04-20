#include "Jogo.hpp"
#include <tuple>
 
using namespace std;

int main(){

    clock_t inicio, termino;
    inicio = clock();

    Jogo* jogo = new Jogo();
    string** matriz;
    unsigned short int tamanho=0, quantidade=0; 
    float tempo=0;

    auto resultado = jogo->tamanho_quantidade_matriz(); 
    tamanho = get<0>(resultado);
    quantidade = get<1>(resultado);
    matriz = new string * [tamanho];
    for (int i=0; i < tamanho; i++){
        matriz[i] = new string[tamanho];
    }
    jogo->iniciar_partida(matriz, tamanho, quantidade);
    
    termino = clock();
    tempo = (float(termino-inicio) / CLOCKS_PER_SEC);
    cout << "\nTEMPO DE EXECUCAO: " << tempo << " segundos." << endl;

    return 0;
}
#include "Jogo.hpp"
#include <tuple>
 
using namespace std;

int main(){

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

    return 0;
}
#ifndef JOGO_HPP
#define JOGO_HPP
//#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream> 
#include <tuple> 
#include <random>

using namespace std;

class Jogo {
    protected:
        
        unsigned short int vida; //quantidade de vida
        unsigned short int inventario; //quantidade de números coletados momentaneamente para transformar em vidas
        unsigned short int perigos; //quantidade de perigos encontrados
        unsigned short int consumo; //quantidade de numeros consumidos
        unsigned short int soma_caminhos_percorridos; //quantidade de vezes caminhadas
        unsigned short int soma_caminhos_nao_percorridos; //quantidade de caminhos nao explorados

    public:
        
        Jogo ();
        Jogo (unsigned short int vida, unsigned short int inventario, unsigned short int perigos, unsigned short int consumo, unsigned short int soma_caminhos_percorridos, unsigned short int soma_num_percorridos);
        ~Jogo();

        void setVida(unsigned short int vida); 
        unsigned short int getVida();

        void setInventario(unsigned short int inventario); 
        unsigned short int getInventario();

        void setPerigos(unsigned short int perigos); 
        unsigned short int getPerigos(); 

        void setConsumo(unsigned short int consumo); 
        unsigned short int getConsumo(); 

        void setCaminhos(unsigned short int soma_caminhos_percorridos); 
        unsigned short int getCaminhos(); 

        void setNaoPercorridos (unsigned short int soma_caminhos_nao_percorridos); 
        unsigned short int getnaoPercorridos();

        tuple<unsigned short int, unsigned short int> tamanho_quantidade_matriz();
        void ler_inputdata_e_criar_arq(unsigned short int  inicio_matriz, unsigned short int fim_matriz, string endereco_matriz);
        void recarregar_matriz(string** matriz, unsigned short int tamanho, string endereco);
        void atualizar_arq(string** matriz, unsigned short int  tamanho, string endereco);
        void imprimir_matriz (string** matriz, unsigned short int  tamanho);
        void caminhar_matriz(string** matriz, unsigned short tamanho, unsigned short &linha, unsigned short &coluna, string endereco_m, unsigned short int aux_rodada, string endereco_h);
        bool verificar_parede(string** matriz, unsigned short int posicao, unsigned short int x, unsigned short int y);
        void atualizar_dados(string** matriz, unsigned short int lin, unsigned short int col);
        tuple<unsigned short int, unsigned short int> verificar_parada(string endereco, unsigned short int tamanho);
        void criar_historico(string** matriz, unsigned short int tamanho, string endereco, unsigned short int contador,unsigned short int cont);
        void exibir_historico(string endereco_h);
        void iniciar_partida (string** matriz, unsigned short int tamanho, unsigned short int quantidade);
        void deletar_arquivo(string endereco);
        bool verificar_possibilidade(unsigned short int x, unsigned short int y, unsigned short int andar);
        bool verificar_ao_redor(string** matriz, unsigned short int  x, unsigned short int  y);
        void escrever_historico(string endereco_h, string m1);
};      

#endif
 
    
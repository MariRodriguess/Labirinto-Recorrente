#include <iostream>
#include <stdlib.h>
#include "Jogo.hpp"
 
Jogo :: Jogo () {
    this -> setVida(10);
    this -> setInventario(0);
    this -> setPerigos(0);
    this -> setConsumo(0);
    this -> setCaminhos(0);
    this -> setNaoPercorridos(0);
}
 
Jogo :: Jogo (unsigned short int vida, unsigned short int inventario, unsigned short int perigos, unsigned short int consumo, unsigned short int soma_caminhos_percorridos, unsigned short int soma_caminhos_nao_percorridos){
    this -> setVida(vida);
    this -> setInventario(inventario);
    this -> setPerigos(perigos);
    this -> setConsumo(consumo);
    this -> setCaminhos(soma_caminhos_percorridos);
    this -> setNaoPercorridos(soma_caminhos_nao_percorridos);
}
 
void Jogo :: setVida(unsigned short int vida){
    this -> vida = vida;
}
unsigned short int Jogo :: getVida() {
    return this -> vida;
}

void Jogo :: setInventario(unsigned short int inventario){
    this -> inventario = inventario;
}
unsigned short int Jogo :: getInventario() {
    return this -> inventario;
}
 
void Jogo :: setPerigos (unsigned short int perigos){
    this -> perigos = perigos;
}
short unsigned int Jogo :: getPerigos() {
    return this -> perigos;
}
 
void Jogo :: setConsumo (unsigned short int consumo){
    this -> consumo = consumo;
}
unsigned short int Jogo :: getConsumo() {
    return this -> consumo;
}

void Jogo :: setCaminhos (unsigned short int soma_caminhos_percorridos){
    this -> soma_caminhos_percorridos = soma_caminhos_percorridos;
}
unsigned short int Jogo :: getCaminhos() {
    return this -> soma_caminhos_percorridos;
}

void Jogo :: setNaoPercorridos (unsigned short int soma_caminhos_nao_percorridos){
    this -> soma_caminhos_nao_percorridos = soma_caminhos_nao_percorridos;
}
unsigned short int Jogo :: getnaoPercorridos() {
    return this -> soma_caminhos_nao_percorridos;
}

tuple<unsigned short int, unsigned short int> Jogo :: tamanho_quantidade_matriz(){
    ifstream arquivoE;
    string aux_tamanho, aux_quantidade, pular;
    unsigned short int tamanho=0, quantidade=0;

    arquivoE.open("dataset/input.data", ios::in);

    if (arquivoE.is_open()){ 
        getline(arquivoE, aux_tamanho, ' '); //pegando o tamanho
        tamanho =  atoi(aux_tamanho.c_str());
        getline(arquivoE, pular, ' ');
        getline(arquivoE, aux_quantidade, ' '); //pegando a quantidade
        quantidade =  atoi(aux_quantidade.c_str());
        arquivoE.close();  
    }else{
        cout << "\nNao foi possível abrir o arquivo.\n";
    }
    return make_tuple(tamanho, quantidade);
}

void Jogo :: ler_inputdata_e_criar_arq(string** matriz, unsigned short int  inicio_matriz, unsigned short int fim_matriz, unsigned short int cont){   
    string linha, elemento;
    unsigned short int linha_arq=0, contador=0, x=0, y=0, cont_linha=0;
    auto aux = tamanho_quantidade_matriz(); 
    unsigned short int tamanho = get<0>(aux);
    ifstream arquivoE;
    ofstream historico;
    
    arquivoE.open("dataset/input.data", ios::in);
    historico.open("dataset/historico.data", ios::app);
    historico << "\nComecando labirinto numero " << cont << ":\n";
    
    if ((arquivoE.is_open()) && (historico.is_open())){
        while(getline(arquivoE, linha)){
            if (linha_arq!=0){  
                if ((linha_arq>=inicio_matriz) && (linha_arq<=fim_matriz)){ //colocando na matriz e no historico apenas uma matriz específica que vai ser utilizada
                    for (int i=0; i<=(int)linha.size(); i++){
                        if ((linha[i] != '\0') && (linha[i] != '\n')){
                            if (linha[i] != ' '){  
                                elemento += linha[i];
                            }else{
                                historico << elemento + " ";
                                matriz[x][y] = elemento;
                                contador++;
                                y++;

                                if (y == tamanho){                  
                                    x++;
                                    y=0;
                                    cont_linha++;
                                }
                                if (cont_linha == tamanho){
                                    x=0;
                                    y=0;  
                                    cont_linha=0;
                                }
                                elemento.clear();      
                            }
                        }else{
                            break;
                        }
                    }
                }
            }
            linha_arq++; 
            if (linha_arq > fim_matriz){
                break;
            }
        }
        historico << "\nVida: " << getVida() << endl;
        historico << "Inventario: " << getInventario() << endl << endl;
        arquivoE.close();
        historico.close();
    }else{
        cout << "\nNao foi possível abrir o arquivo.\n";
    }
}

void Jogo :: recarregar_matriz(string** matriz, unsigned short int tamanho, string endereco){
    
    ifstream arquivoE;
    int x=0, y=0, cont_linha=0;
    string linha, elemento;
    arquivoE.open(endereco, ios::in);
    
    if (arquivoE.is_open()){ //abrindo o arq da matriz 
        while(getline(arquivoE, linha)){
            for (int i=0; i<=(int)linha.size(); i++){
                if ((linha[i] != '\0') && (linha[i] != '\n')){ //para que a matriz não fique com \n ou espaço
                    if (linha[i] != ' '){  
                        elemento += linha[i];
                    }else{
                        matriz[x][y] = elemento; //carregando a matriz
                        y++;
                        if (y == tamanho){                  
                            x++;
                            y=0;
                            cont_linha++;
                        }
                        if (cont_linha == tamanho){
                            x=0;
                            y=0;  
                            cont_linha=0;
                        }
                        elemento.clear();      
                    }
                }else{
                    break;
                }
            }
        }
        arquivoE.close();
    }else{
        cout << "\nNao foi possível abrir o arquivo.\n";
    }
}

void Jogo :: caminhar_labirinto(string** matriz, unsigned short int tamanho, unsigned short int &linha, unsigned short int &coluna, string endereco_m, unsigned short int aux_rodada, string endereco_h){
    unsigned short int x=linha, y=coluna, direcao=0, parada_individual=1;
    bool verif_redor=false, verif_parede=false, verif_possibilidade=false;
    random_device rd; 
    mt19937 gen(rd());  

    //nesse if é tratado a posicao inicial escolhida
    uniform_int_distribution <> inicio(0, tamanho-1);
    if((matriz[linha][coluna] == "#") || (matriz[linha][coluna] == ".#") || (coluna == (tamanho-1)) || (linha == (tamanho-1))){
        while(verif_redor==false){
            while((matriz[linha][coluna] == "#") || (matriz[linha][coluna] == ".#") || (coluna == (tamanho-1)) || (linha == (tamanho-1))){
                linha = inicio(gen); //recebe linha gerada aleatoriamente
                coluna = inicio(gen); //recebe coluna gerada aleatoriamente
            }
            verif_redor = verificar_ao_redor(matriz, linha, coluna);
        }           
    }else{ //nesse if é tratado o caso da posicao inicial ser cercada por paredes
        if (aux_rodada == 0){ //se for a primeira vez que a matriz está sendo processada
            verif_redor = verificar_ao_redor(matriz, linha, coluna);
            if (verif_redor==false){
                while(verif_redor==false){
                    do{
                        linha = inicio(gen); //recebe linha gerada aleatoriamente
                        coluna = inicio(gen); //recebe coluna gerada aleatoriamente
                    }while((matriz[linha][coluna] == "#") || (matriz[linha][coluna] == ".#") || (coluna == (tamanho-1)) || (linha == (tamanho-1)));
                    verif_redor = verificar_ao_redor(matriz, linha, coluna);
                } 
            }
        }    
    } 
    if ((x!=linha) || (y!=coluna)){ //mostra uma possivel alteração da posição inicial no historico
        string m1 = "\n[!!!] NOVA POSICAO INICIAL GERADA E DEFINIDA = [" + to_string(linha+1) + "][" + to_string(coluna+1) + "]\n\n";
        escrever_historico(endereco_h, m1);
    }
    x=linha; //atualiza as variaveis x=linha e y=coluna para andar na matriz
    y=coluna;
    atualizar_dados(matriz, x, y); //atualiza os dados da posicao inicial (tira vida ou aumenta inventario, e coloca as posicoes como caminhadas)

    if (getInventario() == 4){ 
        if (getVida() == 10){
            setInventario(0);
        }else{
            setVida(getVida()+1);
            setInventario(0);
        }    
    }
    if (aux_rodada == 1){ //se NAO for a primeira vez que a matriz está sendo processada
        auto aux_verificar_parada = verificar_parada(matriz, tamanho);
        parada_individual = get<0>(aux_verificar_parada);
    }
    if (parada_individual != 0){ //se a matriz ja nao tiver sido zerada
        uniform_int_distribution <> gerar(1, 8); //8 possiveis posicoes para caminhar
        while(getVida() > 0){
            direcao=0;

            if ((y==tamanho-1) || (x==tamanho-1)){ //se tiver na ultima coluna ou na ultima linha já irá para a próxima matriz
                break;
            }
            do{
                direcao = gerar(gen); //gera uma posicao aleatoria para caminhar
                verif_possibilidade = verificar_possibilidade(x, y, direcao); //verificar se é possivel caminhar ou se irá ser acessada uma posicao que nao existe
                if (verif_possibilidade == true){
                    verif_parede = verificar_parede(matriz, direcao, x, y); //se for possivel caminhar, verificar se nao é parede e atualizar os dados caso nao for
                }
            }while((verif_possibilidade==false) || ((verif_parede == false) && (verif_possibilidade == true))); //gerar posicao enquanto for parede e nao for possivel andar

            switch (direcao){
                case 1: 
                    x--; //diagonal esquerda acima
                    y--; 
                    break;
                case 2: 
                    x--; //cima
                    break;
                case 3: 
                    x--; //diagonal direita acima
                    y++; 
                    break;
                case 4: 
                    y--; //esquerda
                    break;
                case 5: 
                    y++; //direita
                    break;
                case 6: 
                    x++; 
                    y--; //diagonal esquerda abaixo
                    break;
                case 7: 
                    x++; //baixo
                    break;
                case 8: 
                    x++; 
                    y++; //diagonal direita abaixo
                    break;
            }                       
    
            if (getInventario() == 4){
                if (getVida() == 10){
                    setInventario(0);
                }else{
                    setVida(getVida()+1);
                    setInventario(0);
                }    
            }
            direcao=0;
            verif_parede = false; //colocando com falso novamente para as proximas iterações
            verif_possibilidade = false; //colocando com falso novamente para as proximas iterações
        }
    }    
    atualizar_arq(matriz, tamanho, endereco_m, 0, 0, 0); //substitui o arquivo da matriz pela matriz atualizada
}

bool Jogo :: verificar_possibilidade(unsigned short int x, unsigned short int y, unsigned short int direcao){
    bool livre=false;
    //OBSERVAÇÃO: Como já foi analisado se está na última linha ou última coluna, pois é uma condição de parada, essas posições jamais poderão ser as atuais

    if (direcao==1){ //para diagonal esquerda acima não pode estar na primeira linha ou primeira coluna
        if ((x!=0) && (y!=0)){ 
            livre = true;
        }
    }
    else if ((direcao==2) || (direcao==3)){ //para cima e diagonal direita acima não pode estar na primeira linha
        if (x!=0){
            livre=true;
        }
    }
    else if ((direcao==4) || (direcao==6)){ //para esquerda ou diagonal esquerda abaixo não pode estar na primeira coluna
        if (y!=0){
            livre=true;
        }
    }  
    else if ((direcao==5) || (direcao==7) || (direcao==8)){ //para direita, baixo e diagonal direita abaixo pode estar em qualquer posicao
        livre=true;
    }
    return livre;
}

bool Jogo :: verificar_parede(string** matriz, unsigned short int direcao, unsigned short int  x, unsigned short int  y){
    string verif = " ";
    unsigned short int lin=0, col=0;

    if (direcao==1){ //1-diagonal esquerda acima
        verif = matriz[x-1][y-1];
        lin = x-1;
        col = y-1;
    }
    else if (direcao==2){ //2-acima
        verif = matriz[x-1][y];
        lin = x-1;
        col = y;
    }
    else if (direcao==3){ //3-diagonal direita acima
        verif = matriz[x-1][y+1];
        lin = x-1;
        col = y+1;
    }
    else if (direcao==4){ //4-esquerda
        verif = matriz[x][y-1];
        lin = x;
        col = y-1;
    }
    else if (direcao==5){ //5-direita
        verif = matriz[x][y+1];
        lin = x;
        col = y+1;
    }
    else if (direcao==6){ //6-diagonal esquerda abaixo
        verif = matriz[x+1][y-1];
        lin = x+1;
        col = y-1;
    }
    else if (direcao==7){ //7-abaixo
        verif = matriz[x+1][y];
        lin = x+1;
        col = y;
    }
    else if (direcao==8){ //8-diagonal direita abaixo
        verif = matriz[x+1][y+1];
        lin = x+1;
        col = y+1;
    }

    if ((verif != "#") && (verif != ".#")){ //se for diferente de parede, atualizar os dados
        atualizar_dados(matriz, lin, col);
        setCaminhos(this->getCaminhos()+1); 
        return true; //retorna que é possível caminhar
    }else{
        string novo_elemento = ".#";
        if (matriz[lin][col].empty() || matriz[lin][col].size() < novo_elemento.size()) {
            matriz[lin][col].resize(novo_elemento.size()); // Redimensiona a string na posição [lin][col] para ter espaço suficiente
        }
        matriz[lin][col] = novo_elemento; //atualiza como posição descoberta
        return false; //retorna que NAO é possivel caminhar
    }
}

bool Jogo :: verificar_ao_redor(string** matriz, unsigned short int  x, unsigned short int  y){

    bool livre=true;
    string dce, c, ddc, e, d, deb, b, ddb;
    
    if ((x!=0) && (y!=0)){
        dce=matriz[x-1][y-1], c=matriz[x-1][y], ddc=matriz[x-1][y+1], e=matriz[x][y-1], d=matriz[x][y+1], deb=matriz[x+1][y-1], b=matriz[x+1][y], ddb=matriz[x+1][y+1];
        if (((dce=="#")||(dce==".#")) && ((c=="#")||(c==".#")) && ((ddc=="#")||(ddc==".#")) && ((e=="#")||(e==".#")) && ((d=="#")||(d==".#")) && ((deb=="#")||(deb==".#")) && ((b=="#")||(b==".#")) && ((ddb=="#")||(ddb==".#"))){
            livre=false;
        }
    }
    else if ((x==0) && (y==0)){
        d=matriz[x][y+1], b=matriz[x+1][y], ddb=matriz[x+1][y+1];
        if (((d=="#")||(d==".#")) && ((b=="#")||(b==".#")) && ((ddb=="#")||(ddb==".#")) ){
            livre=false;;
        }
    }    
    else if ((x==0) && (y!=0)){
        e=matriz[x][y-1], d=matriz[x][y+1], deb=matriz[x+1][y-1], b=matriz[x+1][y], ddb=matriz[x+1][y+1];
        if (((e=="#")||(e==".#")) && ((d=="#")||(d==".#")) && ((deb=="#")||(deb==".#")) && ((b=="#")||(b==".#")) && ((ddb=="#")||(ddb==".#"))){
            livre=false;
        }
    }
    else if ((y==0) && (x!=0)){
        c=matriz[x-1][y], ddc=matriz[x-1][y+1], d=matriz[x][y+1], b=matriz[x+1][y], ddb=matriz[x+1][y+1];
        if (((c=="#")||(c==".#")) && ((ddc=="#")||(ddc==".#")) && ((d=="#")||(d==".#")) && ((b=="#")||(b==".#")) && ((ddb=="#")||(ddb==".#"))){
            livre=false;
        }
    }
    return livre;
}

void Jogo :: atualizar_dados(string** matriz, unsigned short int lin, unsigned short int col){
    string novo_elemento, str;
    int aux_elemento=0;
    string verif = matriz[lin][col];

    if ((verif == "*") || (verif == ".*")){ //se for perigo
        novo_elemento = ".*";
        matriz[lin][col].resize(novo_elemento.size()); // Redimensiona a string na posição [lin][col] para ter espaço suficiente
        matriz[lin][col] = novo_elemento;
        setVida(getVida()-1);
        setPerigos(getPerigos()+1);
    }else{
        if (verif[0] == '!'){ //se for elementos já vistos anteriormente
            for (int i=1; i<(int)verif.size(); i++){
                novo_elemento = verif[i]; //pega o elemento sem a marcação da exclamação
            }
            aux_elemento = atoi(novo_elemento.c_str());  
        }else{
            aux_elemento = atoi(verif.c_str()); //se nao apenas pega o elemento
        }
        if (aux_elemento > 0){ //se os elementos puderem ser pegos (forem maior que zero)
            aux_elemento-= 1; //subtrai 1 do elemento
            str = to_string(aux_elemento);
            novo_elemento = "!" + str; //adciona a marcação de descoberta
            matriz[lin][col].resize(novo_elemento.size()); // Redimensiona a string na posição [lin][col] para ter espaço suficiente
            matriz[lin][col] = novo_elemento; //atualiza a posição com o novo elemento
            setConsumo(getConsumo()+1);
            setInventario(getInventario()+1);
        }
    }
}

void Jogo :: iniciar_partida (string** matriz, unsigned short int tamanho, unsigned short int quantidade){
    string endereco_matrizes, endereco_h = "dataset/historico.data";
    unsigned short int linha=0, coluna=0, cont=1, cont1=1, parada_total=1, parada_individual=1, contador=0, condicao=0;
    unsigned short int inicio_matriz=1, fim_matriz=tamanho, faltantes=0, percorridos=0, aux=0, aux_inicio=1;

    ofstream historico; //para caso o historico ja exista, os dados serem apagados
    historico.open(endereco_h, ios::out);
    historico.close();

    escrever_historico(endereco_h, "=========[INDICATIVOS]=========\n\n->POSICOES MARCADAS COM '!' = Posições percorridas que continham elementos de vida.\n\n->POSICOES MARCADAS COM '.' = Posições percorridas, no caso de perigos, e posiçoes descobertas, no caso de paredes.\n\n");
    escrever_historico(endereco_h, "->POSICÕES INICIAIS QUE:\n  -Forem parede;\n  -Estiverem cercadas por paredes;\n  -Forem a última linha ou última coluna;\n  serao substituidas por outras posicoes geradas aleatoriamente.\n\n=========[INDICATIVOS]========\n");

    cout << "\t\t\t\t====[START]====\t\t\n\n";
    cout << "POSICÕES INICIAIS QUE:\n  -Forem parede;\n  -Estiverem cercadas por paredes;\n  -Forem a última linha ou última coluna;\nserao substituidas por outras posicoes geradas aleatoriamente.\n\n";
    do{ //inserindo linha e coluna inicial
        if (aux==1){
            cout << "\nTamanho inválido. Permitido de 1 até " << tamanho << ". Tente novamente.";
        }
        cout << "\n\nPor qual ponto das matrizes voce deseja começar a percorrer? (de 1 até " << tamanho << ")\nLinha[x]: ";
        cin >> linha;
        cout << "\nColuna[y]: ";
        cin >> coluna;
        aux=1;
    }while((linha>tamanho) || (linha<=0) || (coluna>tamanho) || (coluna<=0));
    linha-=1; //para que o for possa começar no zero
    coluna-=1;

    while((getVida() > 0)){ //enquanto a vida for maior que zero
        
        endereco_matrizes = "dataset/matriz" + to_string(cont) + ".data";

        if (cont==1){
            parada_total=1;
        }
        if (aux_inicio==1){ //se for a primeira vez que está lendo cada matriz do input.data
            ler_inputdata_e_criar_arq(matriz, inicio_matriz, fim_matriz, cont); 
            caminhar_labirinto(matriz, tamanho, linha, coluna, endereco_matrizes, 0, endereco_h);
            atualizar_arq(matriz, tamanho, endereco_h, contador+1, cont, 1); //atualiza historico
        }else{
            recarregar_matriz(matriz, tamanho, endereco_matrizes);
            auto aux_verificar_parada = verificar_parada(matriz, tamanho);
            parada_individual = get<0>(aux_verificar_parada);
            caminhar_labirinto(matriz, tamanho, linha, coluna, endereco_matrizes, 1, endereco_h);
            atualizar_arq(matriz, tamanho, endereco_h, contador+1, cont, 1); //atualiza historico
        }
        parada_total=0;
        parada_total += parada_individual; 

        if (quantidade+1>=cont){
            cont++;
        }   
        if (quantidade+1==cont){ //para voltar a primeira matriz
            cont=1;
            aux_inicio=0;
        } 
        if ((cont==1) && (parada_total==0)){ // se os elementos totais por onde foi caminhado for zerado
            break;
        }

        //atualizando a posicao da proxima matriz dentro do input.data
        inicio_matriz = fim_matriz+2; 
        fim_matriz = inicio_matriz+(tamanho-1); 
        contador++;
    } 

    if (contador>=quantidade){ //verifica se toda matriz do input data foi percorrida
        condicao = quantidade+1;
    }else{
        condicao = contador+1;
    }

    while (cont1!=condicao){
        endereco_matrizes = "dataset/matriz" + to_string(cont1) + ".data";
        recarregar_matriz(matriz, tamanho, endereco_matrizes);
        auto verificar = verificar_parada(matriz, tamanho);
        faltantes += get<0>(verificar);
        percorridos += get<1>(verificar);   
        deletar_arquivo(endereco_matrizes);
        cont1++;
    }
    unsigned short int nao_percorridos = ((tamanho*tamanho*quantidade) - percorridos);

    for (int i = 0; i < tamanho; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    string divisoria1="\n\t\t\t   __________________________\t\n", divisoria2="\t\t\t   __________________________\t\n";
    
    if ((getVida()==0) && (faltantes!=0)){
        string txt1, txt2;
        cout<<"\n __________________________________________________________________________________________\n|";
        escrever_historico(endereco_h, divisoria1);
        txt1="\t\t\t\t====[NAO FOI DESSA VEZ]====\t\t\t\t    \n\n";
        cout << txt1;
        escrever_historico(endereco_h, txt1);
        txt2="\tSuas vidas acabaram antes do objetivo ser concluido... :(\n";
        cout << txt2;
        escrever_historico(endereco_h, txt2);
        escrever_historico(endereco_h, divisoria2);
        cout<<"|__________________________________________________________________________________________|\n";
        
    }else if (faltantes==0){
        string txt3, txt4;
        cout<<"\n __________________________________________________________________________________________\n|";
        escrever_historico(endereco_h, divisoria1);
        txt3="\t\t\t\t====[PARABENS!!]====\t\t\t\t           \n\n";
        cout << "\t\t\t\t====[PARABENS!!]====\t\t\t\t           |\n\n";
        escrever_historico(endereco_h, txt3);
        txt4="  Voce conseguiu capturar todos os elementos por onde passou no labirinto e venceu o jogo!\n";
        cout << txt4;
        escrever_historico(endereco_h, txt4);
        escrever_historico(endereco_h, divisoria2);
        cout<<"|__________________________________________________________________________________________|\n";
    }

    string txt5, txt6, txt7, txt8, txt9, txt10, txt11, txt12, txt13, txt14, txt15;
    cout<<"\n __________________________________________________________________________________________\n|";
    escrever_historico(endereco_h, divisoria1);
    txt5="\t\t\t\t====[RESULTADOS FINAIS]====\t\t\t\t   \n";
    cout << txt5;
    escrever_historico(endereco_h, txt5);
    txt6="\n  'Vida -> " + to_string(getVida());
    cout << txt6;
    escrever_historico(endereco_h, txt6);
    txt7="\n  'Inventario -> " + to_string(getInventario());
    cout << txt7;
    escrever_historico(endereco_h, txt7);
    txt8="\n  'Perigos encontrados -> " + to_string(getPerigos());
    cout << txt8;
    escrever_historico(endereco_h, txt8);
    txt9="\n  'Elementos consumidos -> " + to_string(getConsumo());
    cout << txt9;
    escrever_historico(endereco_h, txt9);
    txt10="\n  'Quantidades de vezes caminhadas -> " + to_string(getCaminhos());
    cout << txt10;
    escrever_historico(endereco_h, txt10);
    txt11= "\n  'Caminhos totais descobertos -> " + to_string(percorridos);
    cout << txt11;
    escrever_historico(endereco_h, txt11);
    txt12="\n  'Caminhos nao descobertos -> " + to_string(nao_percorridos);
    cout << txt12;
    escrever_historico(endereco_h, txt12);
    txt13="\n  'Elementos restantes para zerar os caminhos percorridos -> " + to_string(faltantes); 
    cout << txt13;
    escrever_historico(endereco_h, txt13);
    txt14="\n\n\t\t\t\t====[ATE A PROXIMA AVENTURA!]====\n";
    cout << txt14;
    escrever_historico(endereco_h, txt14);
    cout<<"|__________________________________________________________________________________________|\n\n";
    txt15="\t\t\t   _________________________________\t\n";
    escrever_historico(endereco_h, txt15);
}

void Jogo :: deletar_arquivo(string endereco){   
    ifstream arquivo(endereco);
    if (arquivo.good()) {
        arquivo.close();
        remove(endereco.c_str());
    } else {
        cout << "Erro ao deletar o arquivo\n";
    }
}

void Jogo :: escrever_historico(string endereco_h, string mensagem){
    ofstream arquivoS;
    arquivoS.open(endereco_h, ios::app);
    if (!arquivoS){
        cout << "\nErro ao criar arquivo.\n";
    }
    arquivoS << mensagem;
    arquivoS.close();
}

void Jogo :: atualizar_arq(string** matriz, unsigned short int tamanho, string endereco_arq, unsigned short int contador, unsigned short int cont, unsigned short int aux_historico){
    int exclamacao=0, aux_int=0;
    string elemento, aux_elemento, str;
    ofstream arquivoS;
    if (aux_historico==1){
        arquivoS.open(endereco_arq, ios::app);
    }else{
        arquivoS.open(endereco_arq, ios::out);
    }
    
    if (!arquivoS){
        cout << "\nErro ao criar arquivo.\n";
    }else{
        if (aux_historico==1){
            arquivoS << "\n\t===[RODADA NUMERO " << contador << "]===";
            arquivoS << "\nLabirinto numero " << cont << ":\n";
        }
        for (int i=0; i<tamanho; i++){
            for (int j=0; j<tamanho; j++){
                if (j==0){
                    elemento = matriz[i][j];
                    for (int k=0; k<=(int)elemento.size(); k++){
                        if ((elemento[k] == '!')){
                            exclamacao=1;
                        }else{
                            aux_elemento = aux_elemento + elemento[k];
                        }
                    }
                    if((exclamacao==1) && (i!=0)){
                        arquivoS << endl;
                        aux_int = atoi(aux_elemento.c_str());
                        str = to_string(aux_int);
                        str = "!" + str;
                        exclamacao=0;
                        arquivoS << str;
                    }else{
                        arquivoS << matriz[i][j];
                    }
                }else{
                    arquivoS << matriz[i][j];
                }
                arquivoS << " ";
                aux_elemento="";
            }
        }
        if (aux_historico==1){
            arquivoS << "\nVida: " << getVida() << endl;
            arquivoS << "Inventario: " << getInventario() << endl << endl;
        }
    }        
    arquivoS.close();
}

tuple<unsigned short int, unsigned short int> Jogo :: verificar_parada(string** matriz, unsigned short int tamanho){

    string aux_soma, elemento;
    int soma=0, pontos=0, descobertos=0;

    for (int i=0; i<tamanho; i++){
        for (int j=0; j<tamanho; j++){
            elemento = matriz[i][j];
            if (elemento[0] == '!'){
                for (int k=1; k<=(int)elemento.size(); k++){
                    aux_soma += elemento[k];
                }
                soma += atoi(aux_soma.c_str());
                aux_soma = "";
                pontos++;
                descobertos++;
            }
            else if (elemento[0]=='.'){
                descobertos++;
            }
        }        
    }
    return make_tuple(soma, descobertos);
}    
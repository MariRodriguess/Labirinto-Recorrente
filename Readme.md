# O Labirinto Recorrente
* Atividade realizada no 3º período para a disciplina de Algoritmos e Estrutura de Dados I.
* Curso de Engenharia da Computação - CEFET-MG, Campus V. 

## Instruções para a realização da atividade
<b>-</b> Um garoto se encontra perdido em um labirinto, o qual é compreendido por nós como sendo uma matriz cujas posição de sua localização é dada por um valor x,y dessa estrutura. Nesse labirinto há paredes que bloqueiam certos passos (#), perigos que consomem parte de sua vida (*) e trajetórias (valores positivos que devem ser subtraídos em 1 a cada passagem).<br>
<b>-</b> Quanto as paredes #, não há muito o que fazer a não ser desviar e continuar a rota. Já os perigos, a cada passada, tende a subtrair 1 de vida de um total de 10. Assim, ao ficar sem pontos de vida o algoritmo deve parar e indicar fim de jogo.<br>
<b>-</b> Ao decorrer do jogo, a cada passo correto sob uma estrada, o garoto consome um item, subtraindo esse do valor que compõe a posição x,y. Gravando nessa o valor resultante. A cada subtração bem sucedida, essa vai para um banco de vida que cheio (a cada 4 ações bem sucedidas) lhe retorna 1 de vida em seu contador, exceto se a vida já estiver completa (10), nesse caso o banco de vida apenas será zerado e uma nova vida não será retornada. Contudo, pode haver partes do caminho com zero itens, esses devem continuar sendo utilizados, porém, sem computar pontuação.<br>
<b>-</b> O labirinto deve ser lido do arquivo input.data, o qual apresentará várias matrizes, todas quadráticas. Sua missão é percorrer as matrizes até que todo o caminho percorrido pelo garoto se torne zero ou que ele venha a morrer devido aos perigos enfrentados. <br>
<b>-</b> No final é preciso apresentar como resultado: (a) quantas casas foram percorridas ao todo; (b) qual a soma de itens consumidos pelo caminho; (c) quantas casas da matriz ficaram sem serem exploradas; (d) quantos perigos foram enfrentados ao decorrer do percurso.<br>
<b>-</b> Para essa atividade, considere selecionar um passo de cada vez de forma aleatória, ou seja, escolha um valor x,y aleatoriamente e vá para ele se possível ou descarte caso seja uma parede. Perigos não são evitados, então, se a posição escolhida for um, enfrente-o. Por fim, a intenção global do problema não é encontrar uma saída, mas sim, tentar consumir o máximo possível de itens até chegar a zerar as possibilidades desse tipo ou morrer tentando.<br>

## Descrição


## Resolução do Problema
Programa feito na linguagem C++.<br>
- O programa do labirinto recorrente é constituído por quatro arquivos: jogo.cpp, jogo.hpp, main.cpp, input.data.<br>
- <b>main.cpp:</b> É criado um ponteiro para uma matriz de string e duas variáveis que irão chamar uma função que retorna o tamanho de cada matriz e quantas existe dentro do arquivo, nesse caso, o “input.data”. Em seguida, será realizada uma alocação dinâmica para a matriz, utilizando o tamanho retornado. Esses três elementos serão passados como parâmetros para as funções e utilizados durante todo o código. Ainda na main, será chamada a função "iniciar_partida", que será responsável por realizar as instruções do código.<br>
- <b>matriz.hpp:</b> É definida uma classe "Jogo" com todos os atributos necessários no jogo (vida, inventário, perigo...), e também definifo todas as funções e bibliotecas utilizadas no código.<br>
- <b>matriz.cpp:</b> É realizado a inicialização da classe e o desenvolvimento e a chamada de cada função.<br>
- <b>input.data:</b> Arquivo contendo o tamanho das matrizes e a quantidade existente (na primeira linha) e as próprias matrizes nas linhas seguintes. É importante salientar que a matriz é composta apenas por números inteiros positivos, asteriscos e hashtags, e o seu tamanho é quadrado, ou seja, tem o mesmo número de linhas e colunas. Abaixo um modelo de um arquivo com 4 matrizes 4x4:

<p align="center">
<img src="https://github.com/MariRodriguess/O-Caminho-Guloso/blob/aa046bc459b47a820e2bc43dfe601470e53778e2/imgs/arquivo_ex.png"> exemplo_arq
</p>

- <b>Terminal de comando:</b> Onde é pedido ao usuário para digitar a posição (linha e coluna) pela qual ele quer começar a caminhar na matriz. E onde também é impresso os resultados obtidos.

- Criação do programa: utilizado um notebook Lenovo com sistema operacional Windows 10 (terminal de comando com o software MinGW).
- Testes do programa: executado no mesmo notebook de criação, e em outros dois computadores diferentes com sistema operacional Linux.

## Explicação da lógica utilizada
Inicialmente, é aberto o arquivo "inoput.data" para leitura, e lido os valores do tamanho e da quantidade de matrizes existentes, para ser realizada e alocação dinâmica de uma matriz de string, e chamada a função "iniciar_partida" usando esses três parâmetros.
Na função "iniciar_partida", é pedido ao usuário para digitar a linha e a coluna inicial.
Na função "ler_andar_matriz", no matriz.cpp, é aberto o arquivo “input.data” para leitura, e criado um IF para toda vez que encontrar uma linha da matriz (linha 85). Dentro do IF, é realizado manobras para que uma variável auxiliar tipo string receba somente os elementos dessa matriz, sem os espaços ou “\0” (linha 90). Quando recebido um elemento, ele é transformado para inteiro e adicionado na matriz do programa, que foi passada como parâmetro para a função, e então, a variável é zerada para receber o próximo elemento, até que a matriz seja completamente preenchida (linhas 93 e 106).<br>
<br>Para o caminhamento, será utilizado essa matriz 4x4 para mostrar as decisões tomadas:

<p align="center">
<img src="https://github.com/MariRodriguess/O-Caminho-Guloso/blob/aa046bc459b47a820e2bc43dfe601470e53778e2/imgs/matriz_ex.PNG">
</p>

<b>Será utilizado duas cores:</b> <br>
<i>Azul claro:</i> todas as posições da matriz que entrariam na condição apresentada.<br>
<i>Azul escuro:</i> posição selecionada aleatoriamente, dentro das que cumprem a condição, para exemplificação de possíveis caminhos, utilizando as setas.<br><br>


## Exemplo de execução:
<p align="center">
<img src="https://github.com/MariRodriguess/O-Caminho-Guloso/blob/aa046bc459b47a820e2bc43dfe601470e53778e2/imgs/terminal_ex1.png">
</p>
<p align="center">
<img src="https://github.com/MariRodriguess/O-Caminho-Guloso/blob/aa046bc459b47a820e2bc43dfe601470e53778e2/imgs/terminal_ex2.png">
</p>


## Compilação e Execução
Esse pequeno exemplo possui um arquivo Makefile que realiza todo o procedimento de compilação e execução.<br>Para tanto, temos as seguintes diretrizes de execução:

| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

## Contato
✉️ <i> mariana.itapec@gmail.com </i>

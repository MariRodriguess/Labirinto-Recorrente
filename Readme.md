# O Labirinto Recorrente
* Atividade realizada no 3º período para a disciplina de Algoritmos e Estrutura de Dados I.
* Curso de Engenharia da Computação - CEFET-MG, Campus V. 

## Instruções para a realização da atividade
&nbsp; <b>-</b> Um garoto se encontra perdido em um labirinto, o qual é compreendido por nós como sendo uma matriz cujas posição de sua localização é dada por um valor x,y dessa estrutura. Nesse labirinto há paredes que bloqueiam certos passos (#), perigos que consomem parte de sua vida (*) e trajetórias (valores positivos que devem ser subtraídos em 1 a cada passagem).<br>
&nbsp; <b>-</b> Quanto as paredes #, não há muito o que fazer a não ser desviar e continuar a rota. Já os perigos, a cada passada, tende a subtrair 1 de vida de um total de 10. Assim, ao ficar sem pontos de vida o algoritmo deve parar e indicar fim de jogo.<br>
&nbsp; <b>-</b> Ao decorrer do jogo, a cada passo correto sob uma estrada, o garoto consome um item, subtraindo esse do valor que compõe a posição x,y. Gravando nessa o valor resultante. A cada subtração bem sucedida, essa vai para um banco de vida que cheio (a cada 4 ações bem sucedidas) lhe retorna 1 de vida em seu contador, exceto se a vida já estiver completa (10), nesse caso o banco de vida apenas será zerado e uma nova vida não será retornada. Contudo, pode haver partes do caminho com zero itens, esses devem continuar sendo utilizados, porém, sem computar pontuação.<br>
&nbsp; <b>-</b> O labirinto deve ser lido do arquivo input.data, o qual apresentará várias matrizes, todas quadráticas. Sua missão é percorrer as matrizes até que todo o caminho percorrido pelo garoto se torne zero ou que ele venha a morrer devido aos perigos enfrentados. <br>
&nbsp; <b>-</b> Para essa atividade, considere selecionar um passo de cada vez de forma aleatória, ou seja, escolha um valor x,y aleatoriamente e vá para ele se possível ou descarte caso seja uma parede. Perigos não são evitados, então, se a posição escolhida for um, enfrente-o. Por fim, a intenção global do problema não é encontrar uma saída, mas sim, tentar consumir o máximo possível de itens até chegar a zerar as possibilidades desse tipo ou morrer tentando.<br>

## Estrutura do código
- Programa feito na linguagem C++.<br>
- O programa do labirinto recorrente é constituído por quatro arquivos: jogo.cpp, jogo.hpp, main.cpp, input.data.<br>
- <b>main.cpp:</b> É criado um ponteiro para uma matriz de string e duas variáveis que irão chamar uma função que retorna o tamanho de cada matriz e quantas existe dentro do arquivo, nesse caso, o “input.data”. Em seguida, será realizada uma alocação dinâmica para a matriz, utilizando o tamanho retornado. Esses três elementos serão passados como parâmetros para as funções e utilizados durante todo o código. Ainda na main, será chamada a função "iniciar_partida", que será responsável por realizar as instruções do código, e também iniciada a função para contar o tempo de execução do código.<br>
- <b>matriz.hpp:</b> É definida uma classe "Jogo" com todos os atributos necessários no jogo (vida, inventário, perigos, consumo, soma dos caminhos percorridos e soma dos caminhos não percorridos), e também definido todas as funções e bibliotecas utilizadas no código.<br>
- <b>matriz.cpp:</b> É realizado a inicialização da classe e o desenvolvimento e a chamada de cada função.<br>
- <b>input.data:</b> Arquivo contendo o tamanho das matrizes e a quantidade existente (na primeira linha) e as próprias matrizes nas linhas seguintes. É importante salientar que a matriz é composta apenas por números inteiros positivos, asteriscos e hashtags, e o seu tamanho é quadrado, ou seja, tem o mesmo número de linhas e colunas. Abaixo um modelo de um arquivo com 2 matrizes 7x7:

<p align="center">
<img src="https://github.com/MariRodriguess/O-Caminho-Guloso/blob/aa046bc459b47a820e2bc43dfe601470e53778e2/imgs/arquivo_ex.png"> exemplo_arq
</p>

- <b>Terminal de comando:</b> Onde é pedido ao usuário para digitar a posição (linha e coluna) pela qual ele quer começar a caminhar na matriz. E onde também é impresso os resultados obtidos.

- <b>Criação do programa:</b> utilizado um notebook Lenovo com sistema operacional Windows 10 (terminal de comando com o software MinGW).
- <b>Testes do programa:</b> executado no mesmo notebook de criação, e em outros dois computadores diferentes com sistema operacional Linux.

## Decisões de implementação e regras
### -> Condições de início do jogo:
&nbsp; A posição inicial escolhida pelo usuário não poderá ser parede; estar cercada por paredes (assim não seria possível percorrer); ser a última linha ou última coluna da matriz (essas serão as condições de troca de matrizes). Se qualquer uma dessas opções forem atendidas, será gerada aleatoriamente uma nova posição inicial.

### -> Condições de parada do jogo:
&nbsp; <b>1-</b> Todo o caminho percorrido que haviam pontos (números) a serem capturados for zerado;<br>
&nbsp; <b>2-</b> A vida acabar (for zero).<br>

### -> Formas de ganhar ou perder vida:
&nbsp; <b>Ganhar:</b> Uma posição da matriz que contém algum número (ponto) terá que ser acessada. Quando isso ocorrer, será subtraído 1 desse número na matriz, e adicionado esse 1 no inventário do viajante. Toda vez que o inventário estiver com 4 elementos, eles serão substituídos por uma vida, sendo eliminados do inventário.<br>
&nbsp; <b>Perder:</b> Uma posição da matriz que contém um asterisco (perigo) terá que ser acessada. Quando isso ocorrer, será subtraído 1 da vida do viajante.<br>
&nbsp; <b>Observação:</b> Em casos onde a vida do viajante seja igual a 10 e o inventário tenha chegado a 4, não será adicionado 1 na vida do viajante, apenas será zerado o inventário e continuado o percusso.<br>

### -> Caminhamento:
&nbsp; Todo caminho a ser percorrido será gerado aleatoriamente, utilizando a combinação de duas classes em C++: classe random_device (fonte de entropia do sistema) e classe mt19937 (aleatoriedade pseudoaleatória). Com elas, será possível gerar uma sequência verdadeiramente aleatória dos números de 1 até 8.<br>
&nbsp; Cada número representa uma posição:<br>
&nbsp; &nbsp; 1- Diagonal esquerda acima; &nbsp; 2- Acima; &nbsp; 3- Diagonal direita acima;<br>
&nbsp; &nbsp; 4- Esquerda; &nbsp; 5- Direita;<br>
&nbsp; &nbsp; 6- Diagonal esquerda abaixo; &nbsp; 7- Abaixo; &nbsp; 8- Diagonal direita abaixo;<br>

### -> Condições de troca de labirinto:
&nbsp; A última linha ou a última coluna terá que ser acessada, quando isso ocorrer, o viajante será transportado para o próximo labirinto do arquivo input.data.<br>
&nbsp; O labirinto já terá que ter sido percorrida anteriormente, e ao chegar em sua posição inicial será analisado se o caminho percorrido nele foi zerado, e caso for, poderá ocorrer o teletransporte do viajante para o próximo.<br>
&nbsp; Caso o labirinto seja cercado por paredes em todas essas posições de troca, o viajante ficará preso nele, percorrendo até perder toda a sua vida e consequentemente o jogo acabar.<br>

### -> Modo que ocorrerá o caminhamento
&nbsp; O percurso ocorrerá analisando se é possível caminhar ou não para uma posição, dado a posição atual do viajante.<br>
&nbsp; Abaixo uma exemplificação dos caminhos possíveis de acordo com a posição do labirinto e um exemplo de um labirinto sendo percorrido:<br>
!!Colocar aqui a matriz com as cores! <br>
!!Colocar aqui a matriz percorrida


### -> Modo que ocorrerá a troca de labirinto
!!Colocar aqui o teletransporte de matrizes


## Implementação do código:
&nbsp; Inicialmente, é aberto o arquivo "input.data" para leitura, e lido o valor do tamanho e da quantidade de labirintos existentes, para ser realizada e alocação dinâmica de uma matriz de string, e chamada a função `iniciar_partida` usando esses três parâmetros.<br>
&nbsp; Toda vez que ocorrer uma partida e o labirinto for modificado, ele será salvo em um arquivo chamado "historico.data" para que o usuário possa acessá-lo e observar os caminhos percorridos.<br>
&nbsp; Na função `iniciar_partida`, é verificado se já existe esse arquivo do histórico criado em uma outra compilação, se tiver, ele será limpado e reutilizado para o jogo atual. É também pedido ao usuário para digitar a linha e a coluna inicial, onde o viajante irá começar a percorrer.<br>
&nbsp; Enquanto as condições de parada citadas não forem atendidas, será analisado duas situações, e realizado alguns procedimentos:<br>
&nbsp; &nbsp; &nbsp; <b>1-</b> Caso for a primeira vez que um labirinto está sendo acessado, será chamado a função `ler_inputdata`. Nela será aberto o arquivo “input.data” para leitura, e criado um IF para toda vez que encontrar uma linha de um labirinto em específico. Dentro do IF, é realizado manobras para que uma variável auxiliar tipo string receba somente os elementos desse labirinto, sem os espaços ou “\0”. 
Quando recebido um elemento, ele é escrito no arquivo de histórico e também passado para a matriz do jogo, e então, a variável é zerada para receber o próximo elemento, até que a matriz seja completamente lida. Como a matriz do jogo será atualizada com os elementos desse arquivo, ela estará pronta para o caminhamento, e cada vez que o labirinto for percorrido pelo viajante pela primeira vez, ele será reescrito em um outro arquivo individual com o nome contendo sua posição dentro do arquivo onde foi pega, por exemplo, "labirinto1.data".<br>
&nbsp; &nbsp; &nbsp; <b>2-</b> Caso não for a primeira vez, apenas será chamado a função `recarregar_matriz`, que irá acessar o arquivo do labirinto que será percorrido e colocar os dados na matriz do jogo, já que o arquivo individual já existe e não precisa mais ser pego no input.data.<br>
&nbsp; Sendo assim, só será criado o arquivo do labirinto se ele for percorrido, então caso o viajante morra ainda no primeiro, por exemplo, não será gerado um arquivo para os seguintes.<br>
&nbsp; Quando a matriz estiver recarregada com os elementos, será chamado a função `caminhar_labirinto`, nela é onde vai ocorrer todo o processo de caminhamento do jogo:<br>
&nbsp; &nbsp; &nbsp; <b>Primeiro passo:</b> Será analisado se a posição de início cumpre as condições de início do jogo já citadas. Se não cumprirem, será gerado novas posições aleatoriamente. Nesse caso, a posição inicial será atualizada e será escrito essas modificações no "historico.data".<br>
&nbsp; &nbsp; &nbsp; <b>Segundo passo:</b> Será chamado a função `atualizar_dados` logo para a posição inicial. Essa função é responsável por verificar o elemento da posição atual e fazer as modificações necessárias.<br>
&nbsp; &nbsp; &nbsp; &nbsp; -> Se o elemento for um perigo, será subtraído 1 da vida do viajante e marcado essa posição com ". *" na matriz, para que ela se dê como descoberta.<br>
&nbsp; &nbsp; &nbsp; &nbsp; -> Se o elemento for um ponto (número) a ser computado, e ele for maior que zero, será adicionado 1 ao inventário do viajante e subtraído 1 do ponto, além de ser concatenado uma "!" em frente ao número para que essa posição da matriz se dê como descoberta, por exemplo, o elemento "4" se transformaria em "!3" após o caminhamento. Caso o número seja igual a zero, apenas será marcado a posição.<br>
&nbsp; &nbsp; &nbsp; &nbsp; -> Se o elemento for uma parede, será atualizado essa posição com ".#" , para que ela também se dê como descoberta.<br>
&nbsp; &nbsp; &nbsp; &nbsp; -> Caso o elemento já tenha sido descoberto anteriormente, e consequentemente tenha uma marcação de "." ou "!", será lido apenas o valor da frente da marcação e realizado as respectivas modificações.<br>
&nbsp; &nbsp; &nbsp; &nbsp; Ou seja, a posição inicial selecionada já poderá retirar vida ou adicionar pontos ao inventário.<br>
&nbsp; &nbsp; &nbsp; <b>Terceiro passo:</b> Com a posição inicial já verificada e atualizada, será processado o restante do labirinto. Para isso, foi feito um loop (while) que vai ocorrer até que as condições de troca de labirinto ou as condições de parada não sejam atendidas. Nesse loop terá os seguintes procedimentos: <br>
&nbsp; &nbsp; &nbsp; &nbsp; -> Será analisado se está na última linha ou última coluna, nesse caso o loop já será encerrado para que o viajante possa ser teletransportado para o próximo labirinto. Caso contrário, o loop irá continuar normalmente com os próximos tópicos.<br>
&nbsp; &nbsp; &nbsp; &nbsp; -> Dentro de um do while, será gerado uma posição aleatória para o viajante caminhar, e só irá sair desse loop quando a posição gerada for realizável, ou seja, se não for uma posição que não existe na matriz e não for uma parede, para isso, será utilizado as funções `verif_possibilidade` e `verif_parede`.<br>
&nbsp; &nbsp; &nbsp; &nbsp; -> Quando for gerado uma posição que possa ser caminhada, será chamada novamente a função `atualizar_dados`, e em seguida atualizado a linha e a coluna do labirinto para aquela posição.<br>
&nbsp; &nbsp; &nbsp; &nbsp; -> Nas últimas linhas do while será conferido se o inventário está com 4 pontos e a vida do viajante não é 10, se sim, será adicionado 1 a vida, e o loop irá continuar.<br>
&nbsp; &nbsp; &nbsp; <b>Quarto passo:</b> Agora com o labirinto já percorrido, ou seja, alguma das condições de parada/teletransporte foram cumpridas, será chamado a função `atualizar_arq`, que irá atualizar o arquivo daquele labirinto em específico com as novas posições modificadas. <br>
&nbsp; Caso não for a primeira vez que um labirinto está sendo percorrido, irá ser processada apenas a posição inicial dele, para em seguida verificar se ele foi zerada, utilizando a função `verificar_parada`. Essa função vai acessar o arquivo desse labirinto, transformando em tipo "int"" e fazendo um somatório de todos os elementos que estiverem marcados com "!", pois foram posições que foram descobertas e que continham pontos. Caso o somatório retornado por ela seja igual a zero, significa que esse labirinto já foi zerado, não sendo mais necessário caminhar por ele. Portanto, nesse caso, o while do caminhamento não será acessado e o viajante será transportado para o labirinto seguinte.<br>
&nbsp; Quando a função `caminhar_matriz` já tiver cumprido o seu papel, será incrementado 1 em um contador auxiliar, que irá ser responsável por monitorar quantas partidas ocorreram. Também será chamanda a função `verificar_parada`, onde o valor retornado será somado a uma variável tipo inteiro chamada "parada_total". <br>
&nbsp; Toda vez que esse contador for igual a quantidade de matrizes que existem no "input.data", será conferido o valor da variável "parada_total". Caso o valor seja igual a zero, significa que todas as matrizes caminhadas foram zeradas, e o jogo foi vencido, caso contrário, a variável e o contador serão zerados para começarem a nova contagem.<br>
&nbsp; O acesso aos arquivos individuais será feito utilizando como auxiliar esse mesmo contador para o acesso ao endereço. Exemplo:<br>
&nbsp; &nbsp; &nbsp; string endereco_matrizes = "dataset/matriz" + to_string(cont) + ".data"<br>
&nbsp; &nbsp; &nbsp; recarregar_matriz(matriz, tamanho, endereco_matrizes) <br>
&nbsp; Quando o viajante morrer ou todos os caminhos forem zerados, será escrito no "historico.data" e printado para o usuário as seguintes informações: vida; inventário; perigos encontrados; elementos consumidos; quantidade de vezes caminhadas; caminhos totais descobertos; caminhos nao descobertos; elementos restantes para zerar o caminho.
&nbsp; As informações de perigos encontrados, elementos consumidos e caminhos totais descobertos foram criadas utilizando a função `verificar_parada`, que também computa quantos elementos com os sinais de "." e "!" haviam nas matrizes.

## Custo Computacional

## Conclusão

## Exemplos de execução

<p align="center">
<img src="">
</p>
<p align="center">
<img src="">
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

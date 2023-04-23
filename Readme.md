# O Labirinto Recorrente
* Atividade realizada no 3º período para a disciplina de Algoritmos e Estrutura de Dados I.
* Curso de Engenharia da Computação - CEFET-MG, Campus V. 

## Instruções para a realização da atividade
&nbsp; <b>-</b> Um garoto se encontra perdido em um labirinto, o qual é compreendido por nós como sendo uma matriz cujas posição de sua localização é dada por um valor x,y dessa estrutura. Nesse labirinto há paredes que bloqueiam certos passos (#), perigos que consomem parte de sua vida (*) e trajetórias (valores positivos que devem ser subtraídos em 1 a cada passagem).<br>
&nbsp; <b>-</b> Quanto as paredes #, não há muito o que fazer a não ser desviar e continuar a rota. Já os perigos, a cada passada, tende a subtrair 1 de vida de um total de 10. Assim, ao ficar sem pontos de vida o algoritmo deve parar e indicar fim de jogo.<br>
&nbsp; <b>-</b> Ao decorrer do jogo, a cada passo correto sob uma estrada, o garoto consome um item, subtraindo esse do valor que compõe a posição x,y. Gravando nessa o valor resultante. A cada subtração bem sucedida, essa vai para um banco de vida que cheio (a cada 4 ações bem sucedidas) lhe retorna 1 de vida em seu contador, exceto se a vida já estiver completa (10), nesse caso o banco de vida apenas será zerado e uma nova vida não será retornada. Contudo, pode haver partes do caminho com zero itens, esses devem continuar sendo utilizados, porém, sem computar pontuação.<br>
&nbsp; <b>-</b> O labirinto deve ser lido do arquivo input.data, o qual apresentará várias matrizes, todas quadráticas. Sua missão é percorrer as matrizes até que todo o caminho percorrido pelo garoto se torne zero ou que ele venha a morrer devido aos perigos enfrentados. <br>

## Estrutura do código
- Programa feito na linguagem C++.<br>
- O programa do labirinto recorrente é constituído por quatro arquivos: jogo.cpp, jogo.hpp, main.cpp, input.data.<br>
- <b>main.cpp:</b> É criado um ponteiro para uma matriz de string e duas variáveis que irão chamar uma função que retorna o tamanho de cada matriz e quantas existe dentro do arquivo, nesse caso, o “input.data”. Em seguida, será realizada uma alocação dinâmica para a matriz, utilizando o tamanho retornado. Esses três elementos serão passados como parâmetros para as funções e utilizados durante todo o código. Ainda na main, será chamada a função "iniciar_partida", que será responsável por realizar as instruções do código, e também iniciada a função para contar o tempo de execução do código.<br>
- <b>matriz.hpp:</b> É definida uma classe "Jogo" com todos os atributos necessários no jogo (vida, inventário, perigos, consumo, soma dos caminhos percorridos e soma dos caminhos não percorridos), e também definido todas as funções e bibliotecas utilizadas no código.<br>
- <b>matriz.cpp:</b> É realizado a inicialização da classe e o desenvolvimento e a chamada de cada função.<br>
- <b>input.data:</b> Arquivo contendo o tamanho das matrizes e a quantidade existente (na primeira linha) e as próprias matrizes nas linhas seguintes. É importante salientar que a matriz é composta apenas por números inteiros positivos, asteriscos e hashtags, e o seu tamanho é quadrado, ou seja, tem o mesmo número de linhas e colunas. Abaixo um modelo de um arquivo com 2 matrizes 7x7:<br>

<p align="center">
<img src="https://github.com/MariRodriguess/Labirinto-Recorrente/blob/d9f93378ba833c86f00f62b992b9799eab882f2d/imgs/ex_arq.PNG" width="135.3" height="274.6">
</p>

- <b>Terminal de comando:</b> Onde é pedido ao usuário para digitar a posição (linha e coluna) pela qual ele quer começar a caminhar na matriz. E onde também é impresso os resultados obtidos.<br>

- <b>Criação do programa:</b> Utilizado um notebook Lenovo com sistema operacional Linux.<br>
- <b>Testes do programa:</b> Executado no mesmo notebook de criação, e em outros dois computadores diferentes com sistema operacional Linux.<br>

## Decisões de implementação e regras
### -> Condições de início do jogo:
&nbsp; A posição inicial escolhida pelo usuário não poderá ser parede; estar cercada por paredes (assim não seria possível percorrer); ser a última linha ou última coluna da matriz (essas serão as condições de troca de matrizes). Se qualquer uma dessas opções forem atendidas, será gerada aleatoriamente uma nova posição inicial.<br>

### -> Condições de parada do jogo:
&nbsp; <b>1-</b> Todo o caminho percorrido que haviam pontos (números) a serem capturados for zerado;<br>
&nbsp; <b>2-</b> A vida acabar (for zero).<br>

### -> Formas de ganhar ou perder vida:
&nbsp; <b>Ganhar:</b> Uma posição da matriz que contém algum número (ponto) terá que ser acessada. Quando isso ocorrer, será subtraído 1 desse número na matriz, e adicionado esse 1 no inventário do viajante. Toda vez que o inventário estiver com 4 elementos, eles serão substituídos por uma vida, sendo eliminados do inventário.<br>
&nbsp; <b>Perder:</b> Uma posição da matriz que contém um asterisco (perigo) terá que ser acessada. Quando isso ocorrer, será subtraído 1 da vida do viajante.<br>
&nbsp; <b>Observação:</b> Em casos onde a vida do viajante seja igual a 10 e o inventário tenha chegado a 4, não será adicionado 1 na vida do viajante, apenas será zerado o inventário e continuado o percusso.<br>

### -> Caminhamento:
&nbsp; Todo caminho a ser percorrido será gerado aleatoriamente, utilizando a combinação de duas classes em C++: classe random_device (fonte de entropia do sistema) e classe mt19937 (aleatoriedade pseudoaleatória). Com elas, será possível gerar uma sequência verdadeiramente aleatória dos números de 1 até 8.<br>
&nbsp; Cada número representa uma posição para qual o viajante irá percorrer: <br>
&nbsp; &nbsp; <b>1-</b> Diagonal esquerda acima; &nbsp; <b>2-</b> Acima; &nbsp; <b>3-</b> Diagonal direita acima;<br>
&nbsp; &nbsp; <b>4-</b> Esquerda; &nbsp; <b>5-</b> Direita;<br>
&nbsp; &nbsp; <b>6-</b> Diagonal esquerda abaixo; &nbsp; <b>7-</b> Abaixo; &nbsp; <b>8-</b> Diagonal direita abaixo;<br>

### -> Condições de troca de labirinto:
&nbsp; A última linha ou a última coluna terá que ser acessada, quando isso ocorrer, o viajante será transportado para o próximo labirinto do arquivo input.data.<br>
&nbsp; No entanto, há uma exceção a ser considerada: se o viajante já percorreu uma matriz anteriormente e é teletransportado de volta para a posição inicial para começar a caminhada novamente, é verificado se a matriz já foi zerada. Se isso for verdade, apenas a posição inicial será percorrida e o viajante será teletransportado para a próxima matriz.<br>
&nbsp; Observação: Caso o labirinto seja cercado por paredes em todas essas posições de troca, o viajante ficará preso nele, percorrendo até perder toda a sua vida e consequentemente o jogo acabar.<br>

### -> Modo que ocorrerá o caminhamento
&nbsp; O percurso ocorrerá analisando se é possível caminhar ou não para uma posição, dado a posição atual do viajante.<br>
&nbsp; Abaixo uma exemplificação dos caminhos possíveis de acordo com a posição do labirinto e um exemplo de um labirinto sendo percorrido:<br>

<p align="center"> 
<img src="https://github.com/MariRodriguess/Labirinto-Recorrente/blob/d9f93378ba833c86f00f62b992b9799eab882f2d/imgs/ex_caminho.png" width="688.6" height="427.3" > 
</p>
<p align="center">
<img src="https://github.com/MariRodriguess/Labirinto-Recorrente/blob/d9f93378ba833c86f00f62b992b9799eab882f2d/imgs/ex_caminho2.png" width="759.3" height="290"> 
</p>

### -> Modo que ocorrerá a troca de labirinto
&nbsp; As matrizes serão percorridas sequencialmente, conforme especificado no arquivo "input.data", formando um ciclo quando a última matriz é alcançada.<br>
&nbsp; Há apenas a exceção citada no tópico "Condições de troca de labirinto".<br>
<p align="center">
<img src="https://github.com/MariRodriguess/Labirinto-Recorrente/blob/d9f93378ba833c86f00f62b992b9799eab882f2d/imgs/ex_teletransporte.png"> 
</p>

### -> Observação
&nbsp; Um arquivo output será gerado com o nome "historico.data" dentro da pasta dataset, para que qualquer usuário consiga acessar e verificar o caminho percorrido pelo viajante e os resultados obtidos.

## Implementação do código:
&nbsp; Inicialmente, o arquivo "input.data" é aberto para leitura e os valores do tamanho e quantidade de labirintos são lidos, através da função `tamanho_quantidade_matriz`, para que se possa realizar a alocação dinâmica de uma matriz de string. Em seguida, a função `iniciar_partida` é chamada utilizando esses três parâmetros.<br>
&nbsp; Cada vez que uma partida é realizada e o labirinto é modificado, ele é salvo no arquivo "historico.data", permitindo que o usuário possa acessá-lo posteriormente e visualizar os caminhos percorridos.<br>
&nbsp; Na função `iniciar_partida`, verifica-se a existência do arquivo de histórico criado em uma compilação anterior. Caso exista, ele é limpo e reutilizado para a nova partida. É também solicitado para o usuário fornecer as coordenadas iniciais da linha e coluna a partir das quais o viajante iniciará o percurso pelo labirinto. <br>
&nbsp; Enquanto as condições de parada mencionadas não forem satisfeitas, serão analisadas duas situações distintas e realizados determinados procedimentos.<br>
* <b>1-</b> Caso for a primeira vez que um labirinto está sendo acessado, será chamado a função `ler_inputdata`. Nela será aberto o arquivo “input.data” em modo de leitura, e criado um IF para toda vez que encontrar uma linha de um labirinto em específico. Dentro do IF, é realizado manobras para que uma variável auxiliar tipo string receba somente os elementos desse labirinto, sem os espaços ou “\0”. 
Quando recebido um elemento, ele é escrito no arquivo de histórico e também passado para a matriz do jogo, e então, a variável é zerada para receber o próximo elemento, até que a matriz seja completamente lida. Como a matriz do jogo será atualizada com os elementos desse arquivo, ela estará pronta para o caminhamento, e cada vez que o labirinto for percorrido pelo viajante pela primeira vez, ele será reescrito em um outro arquivo individual com o nome contendo sua posição dentro do arquivo onde foi pega, por exemplo, "labirinto1.data".<br>
* <b>2-</b> Caso o labirinto já tiver sido acessado anteriormente, a função `recarregar_matriz` será chamada para ler os dados do arquivo individual e atualizar a matriz do jogo. Nesse caso, como o arquivo individual já existe, ele não precisa ser extraído do "input.data" novamente.<br>

&nbsp; Assim, só será criado o arquivo do labirinto se ele for percorrido, então caso o viajante morra ainda no primeiro, por exemplo, não será gerado um arquivo para os seguintes.<br>
&nbsp; Quando a matriz estiver recarregada com os elementos, será chamado a função `caminhar_labirinto`, nela é onde vai ocorrer todo o processo de caminhamento do jogo:<br>
* <b>Primeiro passo:</b> Será verificado se a posição inicial cumpre as condições previamente estabelecidas para início do jogo. Caso não cumpra, novas posições aleatórias serão geradas. A posição inicial será atualizada e as modificações serão registradas no arquivo "historico.data".<br>
*  <b>Segundo passo:</b> A função `atualizar_dados` será chamada para a posição inicial. Essa função é responsável por verificar o elemento presente na posição atual e realizar as modificações necessárias.<br>
&nbsp; &nbsp; &nbsp;  -> Se o elemento for um perigo, será subtraído 1 da vida do viajante e a posição será marcada na matriz com ". *", indicando que ela foi descoberta..<br>
&nbsp; &nbsp; &nbsp;  -> Se o elemento for um ponto a ser computado e seu valor for maior que zero, será adicionado 1 ao inventário do viajante e subtraído 1 do valor do ponto. Além disso, um ponto de exclamação será concatenado na frente do número na matriz, indicando que a posição foi descoberta. Por exemplo, se o elemento inicial for "4", após o caminhamento será registrado como "!3". Caso o número seja igual a zero, apenas será marcada a posição.<br>
&nbsp; &nbsp; &nbsp;  -> Se o elemento for uma parede, será atualizado essa posição com ".#" , para que ela se dê como descoberta.<br>
&nbsp; &nbsp; &nbsp;  -> Se o elemento já tiver sido descoberto anteriormente e tiver uma marcação de "." ou "!", apenas o valor da frente da marcação será lido e as modificações correspondentes serão realizadas.<br>
&nbsp; &nbsp; &nbsp; Dessa forma, a posição inicial selecionada poderá reduzir a vida do viajante ou adicionar pontos ao seu inventário.<br>
* <b>Terceiro passo:</b> Após verificar e atualizar a posição inicial, procede-se ao processamento do restante do labirinto. Para isso, é implementado um loop (while) que continua até que as condições de troca de labirinto ou as condições de parada não sejam satisfeitas. Este loop é composto pelos seguintes procedimentos: <br>
&nbsp; &nbsp; &nbsp; -> É verificado se o viajante está na última linha ou última coluna do labirinto. Caso seja verdadeiro, o loop é encerrado e o viajante é teletransportado para o próximo labirinto. Caso contrário, o loop continua normalmente com os próximos passos.<br>
&nbsp; &nbsp; &nbsp;  -> Dentro de um do-while, é gerada uma posição aleatória para o viajante caminhar. O loop continua até que a posição gerada seja realizável, ou seja, não seja uma posição que não existe na matriz, e não seja uma parede. Para isso, são utilizadas as funções `verif_possibilidade` e `verif_parede`.<br>
&nbsp; &nbsp; &nbsp; -> Quando uma posição que possa ser caminhada é gerada, é chamada novamente a função `atualizar_dados`, e em seguida atualizado a linha e a coluna do labirinto para aquela posição.<br>
&nbsp; &nbsp; &nbsp; -> Nas últimas linhas do while, é verificado se o inventário contém 4 pontos e se a vida do viajante não é 10. Se ambas as condições forem verdadeiras, a vida é aumentada em 1 e o loop continua.<br>

&nbsp; Observação: Se esse não for o primeiro caminhamento do labirinto, apenas a posição inicial será processada. Em seguida, a função `verificar_parada` será utilizada para verificar se o labirinto foi zerado. Essa função acessa a matriz do labirinto e soma todos os elementos marcados com "!". Se o resultado dessa soma for igual a zero, o labirinto já terá sido zerado, e o loop while não será acessado, sendo o viajante teletransportado para o próximo labirinto.<br>
* <b>Quarto passo:</b> Após percorrer o labirinto, a função `atualizar_arq` será chamada para atualizar o arquivo daquele labirinto específico com as novas posições modificadas.<br>
*  <b>Quinto passo:</b> Quando a função `caminhar_matriz` já tiver cumprido o seu papel, será incrementado 1 em um contador auxiliar, que irá ser responsável por monitorar quantas partidas ocorreram. Também será chamanda a função `verificar_parada`, onde o valor retornado será somado a uma variável tipo inteiro chamada "parada_total".<br>Toda vez que esse contador for igual à quantidade de matrizes que existem no "input.data", será conferido o valor da variável "parada_total". Caso o valor seja igual a zero, significa que todas as matrizes caminhadas foram zeradas, e o jogo foi vencido, caso contrário, a variável e o contador serão zerados para a nova contagem.<br>Para acessar os arquivos individuais, será utilizado o contador auxiliar para obter o endereço. Por exemplo: "string endereco_matrizes = 'dataset/matriz' + to_string(cont) + '.data'", e a função "recarregar_matriz" será chamada com o endereço correspondente.<br>
*  <b>Sexto passo:</b> Quando o viajante morrer ou todos os caminhos forem zerados, será escrito no "historico.data" e printado para o usuário as seguintes informações: vida; inventário; perigos encontrados; elementos consumidos; quantidade de vezes caminhadas; caminhos totais descobertos; caminhos nao descobertos; elementos restantes para zerar o caminho; tempo de execução.<br>As informações de perigos encontrados, elementos consumidos e caminhos totais descobertos foram criadas utilizando a função `verificar_parada`, que também computa quantos elementos com os sinais de "." e "!" haviam nas matrizes.<br>

## Custo Computacional
Diante da impossibilidade de se calcular o custo computacional desse código, optou-se por realizar o cálculo do tempo de execução, o que proporciona uma medida aproximada do seu desempenho. Para isso, foi utilizada a biblioteca "time.h", realizando-se a subtração do tempo final pelo tempo inicial, e printando ao usuário o tempo de execução resultante.
Após a realização de dez execuções, todas elas utilizando o mesmo arquivo de entrada,  o tempo de execução médio obtido foi de 0,491 segundos.<br>

## Conclusão
O algoritmo aleatório demonstrou eficácia para solucionar a questão em pauta, simplificando, portanto, o processo de navegação pelo labirinto. Mas é importante ressaltar que esse tipo de algoritmo comporta alguns aspectos desfavoráveis, a exemplo da impossibilidade de calcular o custo computacional, ainda que haja sempre o mesmo número de entrada de dados, uma vez que cada experimento é independente do outro, ou seja, a ocorrência ou não do evento em um experimento não afeta a probabilidade de ocorrer em outro experimento, nos moldes do conceito de probabilidade de Bernoulli. Além disso, também se percebe certa dificuldade em se conceber novas otimizações sem retirar essa aleatoriedade.
De maneira geral, através do programa foi possível explorar e conhecer novas técnicas de programação, além de pensar em estratégias que reduzam o custo computacional quando se trabalha com dados em arquivos.<br>

## Exemplos de execução

<p align="center">
<img src="https://github.com/MariRodriguess/Labirinto-Recorrente/blob/d9f93378ba833c86f00f62b992b9799eab882f2d/imgs/ex_terminal.png" width="493.3" height="441.3">
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

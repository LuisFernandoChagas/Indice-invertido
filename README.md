<h1 align="center">💻 Índice Invertido</h1>

<h3 align="center">Objetivo</h3>

- Ler um arquivo tipo texto contendo as descrições de documentos textuais de uma coleção;

-  Criar um índice invertido a ser definido a seguir; 

- Receber do teclado consultas formada por termos e mostrar listas de documentos onde todos os termos da consulta ocorrem.

---

<h3 align="center">O que é um Índice Invertido</h3>

<h4>Um índice invertido é uma estrutura de dados que permite encontrar rapidamente em uma coleção de texto, quais unidades da coleção um dado termo ocorre. Um exemplo de índice invertido é o índice remissivo que aparece(geralmente ao final) em livros didáticos e manuais
técnicos. Nesse caso, podemos entender o livro como sendo uma coleção de páginas. O índice remissivo contém as principais palavras ou expressões do livro em ordem alfabética. Se uma pessoa quer saber em quais páginas (documentos) do livro (coleção), uma palavra ocorre, ela pode consultar a palavra no índice remissivo. Se a palavra estiver no índice, haverá ao seu lado, a sequência de páginas onde a palavra ocorre no livro.</h4>

<h4>O índice invertido é uma estrutura de dados utilizada em diversas aplicações, tais como máquinas de busca (como Google, Bing), para classificação de documentos e para agrupamento de documentos. Essa estrutura permite encontrar rapidamente os documentos onde um termo ocorre, sem ter que percorrer exaustivamente todos os documentos, procurando pelo termo.</h4>

---

<h3 align="center">Descrição do arquivo de entrada</h3>

####
A coleção de documentos já foi processada e foi transformada em um único arquivo tipo texto, onde cada linha do arquivo corresponde a um documento da coleção. Cada linha tem o seguinte formato:

<h4 align="center"><i> c t1:f t1 t2:f t2 t3:f t3 · · · tn:f tn</i></h4>

---

####
O primeiro valor c de uma linha corresponde a um número inteiro indicando a categoria a qual o documento pertence (esportes, cultura, Matemática, etc). Após o valor de classe há uma sequência de pares do tipo *ti:f ti*, onde ti é um número inteiro correspondente a uma palavra (ou termo) que aparece no documento e *f ti* é a frequência com que o termo *ti* aparece nesse documento (linha). Por exemplo, suponha que na j-ésima linha do arquivo (correspondendo ao j-ésimo documento), aparece o seguinte texto:

<h4 align="center"><i>5 0:13 1:1 6:1 10:1 13:2 15:2 17:1 18:2 26:16 27:3 28:17 29:2 30:3 36:3 37:54 40:21</i></h4>

---

####
Essa linha indica o seguinte: o documento j é da categoria 5 e é composto pelos termos indicados pelos primeiros componentes dos pares seguintes. Por exemplo, o termo 0 ocorre 13 vezes nesse documento, o termo 1 ocorre apenas uma vez e os termos 3, 4 e 5 não ocorrem no documento j. Repare que os pares aparecem ordenados em ordem crescente dada pelo valor
dos termos.

---

<h3 align="center">Módulo de contrução do Índice Invertido</h3>

####
O módulo de construção do índice invertido deve receber como entrada o arquivo contendo a coleção de documentos e gerar o índice invertido.

####
O vetor de cor azul corresponde ao vetor de termos. Cada elemento do componente vetor de termos aponta para uma sequência de triplas, onde cada tripla contém os seguintes componentes: a) *di* que indica o número de um documento (linha do arquivo de entrada) onde o termo ocorreu, b) *ft,di* que é a frequência com que o termo ocorreu no documento *di* e
c) a classe c do documento *di*. Uma sequência de triplas é denominada lista invertida.

<img src="./Assets/Visualização-do-indice-invertido (2).png" align="center">

---

<h3 align="center">Módulo de Consulta</h3>

####
Uma vez que o índice invertido tiver sido criado, o programa deve chamar o módulo de consulta. Nesse módulo, deve ser apresentada uma tela ao usuário com uma pergunta do tipo “Se quiser fazer uma consulta digite 1, senão, digite 0”. Se o usuário digitar 1, a tela deve ser limpada e uma nova tela com a seguinte frase deve aparecer: “Digite os números de termos
correspondentes a uma consulta ( no máximo 5 termos), separados entre si por um espaçoo”. Em seguida, o módulo deve ler uma linha com os números correspondentes aos termos da consulta. Deve acessar o índice invertido para cada termo da consulta e mostrar a interseção de todas as listas entre si. Caso a intersecção for vazia, a seguinte mensagem deve ser emitida: “Não há documentos que contenham concomitantemente todos os termos pesquisados”.

####
Após responder a uma consulta, o módulo de consulta deve apagar a tela e mostra a tela inicial novamente. Essa repetição de telas deve ocorrer até que o usuário digite 0 indicando que ele não quer fazer mais consultas. Nesse caso o programa deve chamar o módulo de liberação do índice e terminar.

---

<h3 align="center">Módulo de Liberação do Índice Invertido</h3>

####
Esse módulo deve ser chamado antes de terminar o programa e seu objetivo é o de liberar a área ocupada pelos componentes do índice invertido (vetor de termos e vetores de listas invertidas). Esse módulo deve primeiramente percorrer o vetor de termos e para cada elemento do vetor
de termos, liberar a lista invertida apontada pelo elemento. Após esse percurso, o próprio vetor de termos deve ser liberado.

---

<h3 align="center">Melhorias</h3>

####
- Aumentar os tipos de consultas que possam ser feitas. Na especificação acima, é feita uma intersecção das listas invertidas correspondentes aos termos da consulta. Essa intersecção implementa a operação e também denotada pelo símbolo ∧ entre os termos da consulta. O trabalho pode ser expandido para implementar a operação OU (∨) que corresponde a retornar a união das listas invertidas dos termos da consulta.

- Outra melhoria no programa é o armazenamento em disco do índice invertido e sua posterior leitura do disco. Assim, evita-se que o programa crie o índice invertido (uma operação mais lenta) toda vez que for executado. Se o índice invertido foi criado em uma execução anterior, basta lê-lo do disco e carrega-lo em memória.

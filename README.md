# lab01-AFD
# 1 Descrição
Neste programa, você deve implementar um programa que recebe como entrada um autômato finito determinístico M = (Σ, Q, q0, δ, F). Sua aplicação deve conter módulos distintos,
tais como:
• Um módulo capaz de carregar/gravar arquivos que representam autômatos;
• Um módulo que, a partir da definição do autômato finito determinístico seja capaz de
reconhecer palavras da linguagem que o autômato reconhece.
Sua aplicação deve analisar cada palavra da entrada e produzir como saída a mensagem
“M aceita a palavra <palavra>” se a <palavra> for aceita pelo autômato, ou a mensagem “M
rejeita a palavra <palavra>”, caso a <palavra> for rejeitada.
Todo tratamento pertinente de erros deve ser realizado. O programa deve emitir mensagens
de erro para todo erro encontrado. Em hipótese alguma o programa deve abortar caso ocorra
um erro.
# 2 Formato do Arquivo
O arquivo que representa um autômato é um arquivo texto que pode ser gerado utilizando
qualquer editor. A primeira coluna deste arquivo define o conteúdo da linha, e o restante da
linha depende da primeira coluna. Cada item da entrada corresponde a um elemento que
compõe a estrutura de um autômato finito visto em aula. Os seguintes caracteres devem ser
interpretados na primeira coluna:
• # Comentário: qualquer linha iniciada com # deve ser ignorada;
• A alfabeto: após o A devem seguir os símbolos terminais da linguagem (letras minúsculas) separados por espaços em branco;
• Q conjunto de estados: após o Q devem seguir os rótulos que correspondem aos estados
do autômato, separados por espaços em branco;
• q estado inicial: após o q deve seguir o estado inicial;
• F estados finais: após o F deve seguir a lista de estados finais do autômato, separados
por espaços em branco;
• T transição: para cada transição deverá haver uma linha T contendo o estado origem, o
símbolo lido e o estado destino (Veja o exemplo).
• P palavra: após o P deve seguir uma palavra de entrada para ser analisada pelo autômato.

# 3 Exemplo do arquivo de entrada
Automato Finito Determinístico
Este automato detecta qualque string contendo bb
L(G) = (a|ba)* bb (a|b)*
Alfabeto:
A a b
Estados:
Q A B C
Estado Inicial:
q A
Estados Finais:
F C
Transições
T A a A
T A b B
T B a A
T B b C
T C a C
T C b C
Palavras
P abababbababa
P aaabaababaa
P abb
P abab
4 Exemplo do arquivo de Saída
M aceita a palavra <abababbababa>
M rejeita a palavra <aaabaababaa>
M aceita a palavra <abb>
M rejeita a palavra <abab>
2
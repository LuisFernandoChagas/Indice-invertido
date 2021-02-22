#include <stdio.h>
#include <stdlib.h>
#define N 5

typedef struct{
    int linha_arquivo, frequencia, classe;
}tipoTripla;

typedef struct{
    int vetPalavra, vetColuna;
    tipoTripla *matriz;
}vetTermos;

void menorParaMaior_vetTermos(vetTermos *matriz, int tam);
int compararPalavras(vetTermos *vetorPalavra, int tamPalavra, int palavra);
int acharTermos(vetTermos *termoConsultado, vetTermos *vetPalavra, int *vetTermoParaConsultar, int tamVetPalavra, int tamVetTermoParaConsultar);
void interseccaoLinhas(FILE *dataColection, vetTermos *termoConsulta, int tamTermos);
void printfDataColection(FILE *dataColection, int *linhas, int tamLinhaConsultadas);

int main(){
    // GERAR ÍNDICE INVERTIDO
        // INICIALIZAÇÃO
    vetTermos *vetTermo;
    FILE *dataColectionLeitura;
    int tamLinhaIndice = 0, i = 0, aux;
    int classe, palavra, frequencia;
    char p;
    
    dataColectionLeitura = fopen("acm.txt", "rb");
    
    if(!dataColectionLeitura){
        printf("Arquivo nao encontrado: 1\n");
        system("pause");
        exit(1);
    }

    vetTermo = (vetTermos*) malloc(sizeof(vetTermos));

    if(!vetTermo){
        printf("Nao ha memoria suficiente: 1\n");
        system("pause");
        exit(1);    
    }

    vetTermo[0].matriz = (tipoTripla*) malloc(sizeof(tipoTripla));

    if(!vetTermo[0].matriz){
        printf("Nao ha memoria suficiente: 2\n");
        system("pause");
        exit(1);
    }

        // ÍNDICE INVERTIDO APENAS DA 1° LINHA
    fscanf(dataColectionLeitura, "%d ", &classe);
    while(fscanf(dataColectionLeitura, "%d:%d%c", &palavra, &frequencia, &p)){
        tamLinhaIndice++;

        if(i){
            vetTermos *aux1 = realloc(vetTermo, tamLinhaIndice * sizeof(vetTermos));

            if(!aux1){
                printf("Nao ha memoria suficiente: 3\n");
                system("pause");
                exit(1);
            }

            vetTermo = aux1;

            vetTermo[tamLinhaIndice - 1].matriz = malloc(sizeof(tipoTripla));

            if(!vetTermo[tamLinhaIndice - 1].matriz){
                printf("Nao ha memoria suficiente: 4\n");
                system("pause");
                exit(1);
            }
        }

        vetTermo[tamLinhaIndice - 1].vetPalavra = palavra;
        vetTermo[tamLinhaIndice - 1].vetColuna = 1;

        vetTermo[tamLinhaIndice - 1].matriz[0].classe = classe;
        vetTermo[tamLinhaIndice - 1].matriz[0].frequencia = frequencia;
        vetTermo[tamLinhaIndice - 1].matriz[0].linha_arquivo = 0;

        i++;
        if(p == '\n') break;
    }

    i = 1;

        // ÍNDICE INVERTIDO DO RESTANTE
    while(fscanf(dataColectionLeitura, "%d ", &classe) != EOF){
        while(fscanf(dataColectionLeitura, "%d:%d%c", &palavra, &frequencia, &p)){
            aux = compararPalavras(vetTermo, tamLinhaIndice, palavra);
                
            if(aux >= 0){
                vetTermo[aux].vetColuna++;

                tipoTripla *auxiliar1 = realloc(vetTermo[aux].matriz, vetTermo[aux].vetColuna * sizeof(tipoTripla));

                if(!auxiliar1){
                    printf("Nao ha memoria suficiente: 5\n");
                    system("pause");
                    exit(1);
                }

                vetTermo[aux].matriz = auxiliar1;

                vetTermo[aux].matriz[vetTermo[aux].vetColuna - 1].classe = classe;
                vetTermo[aux].matriz[vetTermo[aux].vetColuna - 1].frequencia = frequencia;
                vetTermo[aux].matriz[vetTermo[aux].vetColuna - 1].linha_arquivo = i;
            } else {
                tamLinhaIndice++;

                vetTermos *aux1 = realloc(vetTermo, tamLinhaIndice * sizeof(vetTermos));

                if(!aux1){
                    printf("Nao ha memoria suficiente: 6\n");
                    system("pause");
                    exit(1);
                }

                vetTermo = aux1;

                vetTermo[tamLinhaIndice - 1].matriz = (tipoTripla*) malloc(sizeof(tipoTripla));

                if(!vetTermo[tamLinhaIndice - 1].matriz){
                    printf("Nao ha memoria suficiente: 7\n");
                    system("pause");
                    exit(1);
                }

                vetTermo[tamLinhaIndice - 1].vetColuna = 1;
                vetTermo[tamLinhaIndice - 1].vetPalavra = palavra;

                vetTermo[tamLinhaIndice - 1].matriz[0].classe = classe;
                vetTermo[tamLinhaIndice - 1].matriz[0].frequencia = frequencia;
                vetTermo[tamLinhaIndice - 1].matriz[0].linha_arquivo = i;
            }
            if(p == '\n') break;
        }
        i++;
    }

        // ORGANIZAR O ÍNDICE INVERTIDO EM ORDEM DO MENOR PARA O MAIOR DE ACORDO COM "vetTermo[x].vetPalavra"
    menorParaMaior_vetTermos(vetTermo, tamLinhaIndice);

    // MÓDULO DE CONSULTA
    do{
            // INICIALIZAÇÃO
        int vet[N], tamTermos = 0, opcao;

            // OPÇÕES DO USUÁRIO
        printf("Se quiser fazer uma consulta digite 1, senao, digite 0\n");

        scanf("%d", &opcao);

        system("cls");

        while(opcao != 1 && opcao != 0){
            printf("Numero invalido!\n");
            printf("Se quiser fazer uma consulta digite 1, senao, digite 0\n");
        
            scanf("%d", &opcao);

            system("cls");
        }

        if(opcao == 1){
            printf("Digite os numeros de termos correspondentes a uma consulta(no maximo %d termos), separados entre si por um espaco:\n", N);
            
            while(scanf("%d", &vet[tamTermos]) != EOF){
                tamTermos++;
            }

            system("cls");

            vetTermos termoConsultado[tamTermos];

            if(!acharTermos(termoConsultado, vetTermo, vet, tamLinhaIndice, tamTermos)){
                printf("Termo(s) nao encontrado(s)\n");
            } else {
                menorParaMaior_vetTermos(termoConsultado, tamTermos);

                interseccaoLinhas(dataColectionLeitura, termoConsultado, tamTermos);
            }

            system("pause");
            system("cls");
        } else {
            break;
        }
    }while(1);
    
    // LIBERAÇÃO DE MEMÓRIA
    for(i = 0; i < tamLinhaIndice; i++){
        free(vetTermo[i].matriz);
    }

    free(vetTermo);

    fclose(dataColectionLeitura);

    return 0;
}

//////////////////////////////////////////////////
// esta função ordena o vetor do menor para o maior
void menorParaMaior_vetTermos(vetTermos *vetor, int tam){
    int i, j;
    vetTermos y;

    for(i = 0; i < tam; i++){
        for(j = i; j < tam; j++){
            if(vetor[i].vetPalavra > vetor[j].vetPalavra){
                y = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = y;
            }
        }
    }

    return;
}

// se retornar x >= 0 é necessário realocar memória para o vetTermo[x].matriz
// caso retorne -1 é necessário realocar memória para o vetTermo
int compararPalavras(vetTermos *vetorPalavra, int tamPalavra, int palavra){
    int i;

    for(i = 0; i < tamPalavra; i++){
        if(vetorPalavra[i].vetPalavra == palavra){
            return i;
        }
    }

    return -1;
}

// esta função procura o termo dentro do índice invertido e o aloca em *termoConsultado
// caso o(s) termo(s) procurado(s) não esteja(m) no índice invertido, será retornado o valor 0
int acharTermos(vetTermos *termoConsultado, vetTermos *vetPalavra, int *vetTermoParaConsultar, int tamVetPalavra, int tamVetTermoParaConsultar){
    int i, j, k = 0, aux = 0;

    for(i = 0; i < tamVetTermoParaConsultar; i++){
        aux = 0;
        for(j = 0; j < tamVetPalavra; j++){
            if(vetTermoParaConsultar[i] == vetPalavra[j].vetPalavra){
                termoConsultado[k] = vetPalavra[j];
                k++;
                aux = 1;
            }
        }
        if(!aux) return aux;
    }

    return aux;
}

// esta função faz a intersecção das linhas e guarda seus valores do menor para o maior e depois
// mostra os arquivos correspondentes.
void interseccaoLinhas(FILE *dataColection, vetTermos *termoConsulta, int tamTermos){
    // INICIALIZAÇÃO
    int i, j, k;
    int *linhasConsultadas, tamLinhaConsultadas = 0;
    int aux = 0;

    linhasConsultadas = (int*) malloc(sizeof(int));

    if(!linhasConsultadas){
        printf("Nao ha memoria suficiente: 9\n");
        system("pause");
        exit(1);
    }

        // PROCURAR LINHAS QUE SE REPETEM DE ACORDO COM A INTERSECÇÃO DAS PALAVRAS
    for(k = 0; k < termoConsulta[0].vetColuna; k++){
        for(i = 1; i < tamTermos; i++){
            for(j = 0; j < termoConsulta[i].vetColuna; j++){
                if(termoConsulta[0].matriz[k].linha_arquivo == termoConsulta[i].matriz[j].linha_arquivo){
                    aux++;
                    break;
                }
            }
        }

        if(aux == tamTermos - 1){
            // ALOCAR LINHAS QUE SE REPETEM
            tamLinhaConsultadas++;

            int *aux2 = realloc(linhasConsultadas, tamLinhaConsultadas * sizeof(int));

            if(!aux2){
                printf("Nao ha memoria suficiente: 10\n");
                system("pause");
                exit(1);
            }

            linhasConsultadas = aux2;

            linhasConsultadas[tamLinhaConsultadas - 1] = termoConsulta[0].matriz[k].linha_arquivo;
        }

        aux = 0;
    }

    if(!tamLinhaConsultadas){
        printf("Nao ha documentos que contenham concomitantemente todos os termos pesquisados\n");
    } else {
        printfDataColection(dataColection, linhasConsultadas, tamLinhaConsultadas);
    }

    // LIBERAÇÃO DE MEMÓRIA
    free(linhasConsultadas);

    return;
}

void printfDataColection(FILE *dataColection, int *linhas, int tamLinhas){
    int i = 0, j = 0, k = 0;
    int classe, palavra, frequencia, aux = 0;
    char p;

    fseek(dataColection, 0, SEEK_SET);

    while(fscanf(dataColection, "%d ", &classe)){
        k = 0;
        aux = 0;
        while(fscanf(dataColection, "%d:%d%c", &palavra, &frequencia, &p)){
            if(i == linhas[j]){
                if(!k){
                    printf("%d ", classe);
                    
                    aux = 1;
                }
            
                printf("%d:%d%c", palavra, frequencia, p);
            }

            if(p == '\n') break;
            k++;
        }
        if(aux) j++;

        if(j == tamLinhas) break;
        
        i++;
    }

    return;
}
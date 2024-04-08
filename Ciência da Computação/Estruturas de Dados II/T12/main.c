#include <stdio.h>
#include <stdlib.h>
#include "tempo.h"

// Lucas Bassedoni
// Bruno Ribas
// Alessandro Catani

/*
Implemente em C um programa para gerar um vetor com milhares de elementos
(funções auxiliares são fornecidas). Implemente em forma de função as
seguintes funções:

a) busca sequencial de um valor
b) busca binária de um valor de forma recursiva
c) busca binária de um valor de forma iterativa

Faça medição do tempo de busca para diversos valores de N (10000, 20000, 40000, 
80mil, 160mil,...). Chegará um ponto que sua máquina não terá memória para
alocar o vetor. Informe isto no relatório.

Considere em suas medições duas situações;
1) busca de um valor aleatório que existe
2) busca de um valor inexistente

*/

// Gerar/alimentar vetor aleatório
int geraVet(int *v, int t)
{
    int i;
    int MAX = 100000;

    for (i = 0; i < t; i++) {
        v[i] = (rand() % (MAX + MAX)) - MAX;
    }
    return (i);
}

// Ordena Vetor
int ordena(int v[], int t)
{
    int i, j;
    int menor;

    for (i = 0; i < t; i++) {
        menor = i;
        for (j = i; j < t; j++) {
            if (v[menor] > v[j]) {
                menor = j;
            }
        }
        j = v[i];
        v[i] = v[menor];
        v[menor] = j;
    }
}

int imprime_vet(int v[], int t)
{
    int i;

    for (i = 0; i < t; i++) {
        printf("%06d ", v[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// Busca Sequencial
int buscaSequencial(int *vetor, int fim, int num){
	int i;
	
	for(i=0; i<fim; i++){
		if(num == vetor[i]){
			return 1;
		}
	}
	return 0;
};

// Busca Binaria Recursiva
int buscaBinRec(int *vetor, int ini, int fim, int num){
	int meio;                    
    meio = (ini + fim)/2; 
		                        
    if (vetor[meio] == num)
		return 1;
	
	if(ini>=fim)
		return 0;
	
	if (vetor[meio] < num)
	  	return buscaBinRec(vetor, meio+1, fim, num);             
    else
	    return buscaBinRec(vetor, ini, meio-1, num);
};

// Busca Binaria Iterativa
int buscaBinIter(int *vetor, int ini, int fim, int num){
	int meio;    
	fim = fim - 1;                     
   	while (ini <= fim) {                          
    	meio = (ini + fim)/2;         
    	if (vetor[meio] == num)
			return 1;
			          
		if (num < vetor[meio]) 
			fim = meio - 1;            
    	else 
			ini = meio + 1;                       
   }
                            
   return 0;
}

int main(int argc, char *argv[]){
	
	int *vetor, tam, i, num, achou;
	ulong f;
	
	if (argc!=2){
		fprintf(stderr, "Erro. Precisa passar o tamanho do vetor\n");
		return(1);
	}
	tam = atoi(argv[1]);
	
	vetor = (int *) malloc(tam * sizeof(int));
	if (vetor == NULL) {
		fprintf(stderr, "ERRO ao tentar alocar %d inteiros\n", tam);
		return(2);
	}
	
	geraVet(vetor, tam);
    ordena(vetor, tam);
    
    //imprime_vet(vetor, tam);
    
	printf("\nBuscar no vetor: ");
	scanf("%d", &num);
	srand(time(NULL));
	
	//Busca Sequencial
	f = tempo();
	achou = buscaSequencial(vetor, tam, num);
	f = tempo();
	if(achou == 0){
		printf("\n\nBuscaSeq: Nao encontrado, tempo: %s", formata(f));
	}else{
		printf("\n\nBuscaSeq: %d encontrado! Tempo: %s", num, formata(f));
	}
	
	//Busca Binaria Recursiva
	f = tempo();
	achou = buscaBinRec(vetor, 0, tam, num);
	f = tempo();
	if(achou == 0){
		printf("\n\nBuscaBinRec: Nao encontrado, tempo: %s", formata(f));
	}else{
		printf("\n\nBuscaBinRec: %d encontrado! Tempo: %s", num, formata(f));
	}
		
	//Busca Binaria Iterativa
	f = tempo();
	achou = buscaBinIter(vetor, 0, tam, num);
	f = tempo();
	if(achou == 0){
		printf("\n\nBuscaBinIter: Nao encontrado, tempo: %s", formata(f));
	}else{
		printf("\n\nBuscaBinIter: %d encontrado! Tempo: %s", num, formata(f));
	}

	system("PAUSE");
}

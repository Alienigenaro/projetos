#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

int incluir(no*);
int remover(no*);
void buscar(no);
void crlf();
void profundidade(no);
void log(no,int);

int main(){
	no a=NULL;
	int avlcont=0;

	for(;;){
		printf("1 incluir elemento\n");
		printf("2 remover elemento\n");
		printf("3 buscar elemento\n");
		printf("4 sair do programa\n");
		fflush(stdin);
		switch(getchar()){
			case '1':
				avlcont += incluir(&a);		//Inserir elemento.
			break;
			case '2':
				avlcont -= remover(&a);		//Remover elemento.
			break;
			case '3':
				buscar(a);		//Buscar elemento.
			break;
			case '4':
				exit(1);		//Sair.
			case '5':
				preO(a);		//Mostra arvre em pre ordem
				crlf();
				break;
            case 'p':
                profundidade(a);//mostra a profundidade da arvore
                break;
		}
		log(a,avlcont);
	}
	return 0;
}

void profundidade(no a){
    printf("%d\n",a?a->prof:0);
}


int inteiro(){                      //Apenas l� um inteiro com scanf
	int i;
	scanf("%d",&i);
	return i;
}

int chave(){                        //Interage com o usu�rio para obter um valor de chave
	printf("Insira uma chave:");
	return inteiro();
}

int valor(){                        //Interage com o usu�rio para obter um valor de registro.
	printf("Insira um valor:");
	return inteiro();
}

int incluir(no * av){              //Interage com o usu�rio pedindo uma chave e um valor e insere o resultado na �rvore
    return insere(av, chave(),valor());    //Chama a fun��o para inserir os dados.
}

int remover(no * av){              //Interage com o usu�rio pedindo uma chave de remo��o.
    return rem(av,chave());
}

void buscar(no av){                 //Efetua a busca da chave obtida atrav�z de intera��o com o usu�rio.
	no aux=NULL;
	aux = busca(av,chave());
	if(aux)                         //Informa caso o elemento for encontrado, juntamente com sua profundidade na �rvore.
		printf("Valor:\t%d\nNivel:\t%d\n",aux->valor,aux->prof);
	else                            //Emite um aviso caso a chave n�o esteja presente na �rvore.
		printf("Elemento inexistente na arvore.\n");
}

void crlf(){                                //Imprime uma quebra de linha
    printf("\n");

}

void log(no a,int avlcont){
    FILE * p=0;
	while(p==NULL)//Tenta abrir o arquivo at� conseguir
		p = fopen ("saida.log","a");
    fprintf(p,"%d %d\n",a?a->prof:0, avlcont);
    fclose(p);
}








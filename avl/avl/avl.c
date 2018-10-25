#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


no novoN(int ch, int val){				    //Retorna endere�o do n� recem criado.
	no N = (no)	malloc(sizeof(struct N));   //Aloca na mem�ria o espa�o necess�rio para um n�.
	N->ch = ch;                             //Registra a chave
	N->valor = val;                         //Registra o valor
	N->es = NULL;                           //Indica que n�o tem filho esquerdo
	N->di = NULL;                           //Indica que n�o tem filho direito
	N->prof = 1;                            //Profundidade padr�o
	return(N);                              //Retorna a referencia para o n� rec�m criado
}

int prof(no N){							    //Retorna a profundidade da �rvore.
	if(N)
		return N->prof;                     //Busca no n� sua profundidade.
    return 0;                               //Retorna 0 caso n�o exista n�.
}

int fatorB(no N){						    //Retorna o fator de balanceamento.
	if(N)
		return prof(N->es) - prof(N->di);   //Calcula e retorna o fator de balanceamento.
    return 0;                               //Caso o n� n�o exista retorna zero.
}

int max(int a, int b){				    	//Retorna o maior.
	return (a >= b)? a : b;                 //Se a>=b retorna a, caso contr�rio retorna b.
}

void ActProf(no x){                         //Atualiza profundidade.
    x->prof = max(prof(x->es), prof(x->di))+1; //Calcula a profundidade baseando-se nas profundidades dos filhos.
}

void giraD(no * N){						    //Rota��o a direita.
	no A = (*N)->es;
	no B = A->di;
    //Efetua a rota��o:
	A->di = *N;
	(*N)->es = B;

	//Atualiza profundidades:
	ActProf(*N);
	ActProf(A);
	*N = A;
}

void giraE(no * N){						    //Rota��o a esquerda.
	no A = (*N)->di;
	no B = A->es;

    //Efetua a rota��o.
	A->es = *N;
	(*N)->di = B;

	//Atualiza profundidades:
	ActProf(*N);
	ActProf(A);
	*N = A;
}

void balancear(no * N){                     //Balanceia a arvore.
    int b;

    if(*N){
        ActProf(*N);
        b = fatorB(*N);
        //return;//Desativa balanceamento
        if(b > 1){
            if(fatorB((*N)->es)>=0)		//Esquerda esquerda
                giraD(N);
            else{						//Esquerda direita
                giraE(&(*N)->es);
                giraD(N);
            }
        }
        if(b < -1){
            if(fatorB((*N)->es)<=0)		//Direita direita
                giraE(N);
            else{						//Direita esquerda
                giraD(&(*N)->di);
                giraE(N);
            }
        }
    }

}

int insere(no * N, int ch, int val){	    //Fun��o recursiva de inser��o em �rvore.
	int retval;
	if(!*N){
    	*N = (novoN(ch, val));              //Se n�o existir nada, apenas cria o novo n�.
        retval = 1;
	}
	else if(ch < (*N)->ch)                  //Se a chave for menor
        retval = insere(&((*N)->es), ch, val);       //procura na prole da esquerda
	else if(ch > (*N)->ch)                  //caso seja maior
		retval = insere(&(*N)->di, ch, val);         //procura na da direita
	else{
        (*N)->valor = val;                  //Apenas atualiza o valor.
        retval = 0;
	}                                   //Se n�o for nem direita nem esquerda, o n� j� existe

	balancear(N);                           //Balanceia a �rvore das folhas para a raiz.
	return retval;
}

no meNOr(no N){                             //Dada uma �rvore, retorna refer�cia de seu menor elemento.
    if(N->es)
		return meNOr(N->es);                //Se ainda h� o que percorrer, continuar a recurs�o.
    return N;                               //Se n�o existe elemento a esquerda, ent�o este j� � o menor.
}

int rem(no * N, int ch){                   //Fun��o de remo��o: dada uma chave, remove o elemento tentando manter a �rvore balanceada.
    int RetVal;
    if(*N){
        if (ch < (*N)->ch )
                RetVal = rem(&(*N)->es, ch);
        else if( ch > (*N)->ch )

                RetVal = rem(&(*N)->di, ch);
        else{
            if(!(((*N)->es) && ((*N)->di))){
                no aux = (*N)->es ? (*N)->es : (*N)->di;//Aux � o filho que existir
                if (!aux) {     //Sem filhos
                    aux = *N;
                    *N = NULL;
                }
                else                    //Filho �nico
                    **N = *aux;         //Copia o conte�do do filho �nico
                free(aux);
                RetVal = 1;
            }
            else{                                   //Dois filhos

                no aux = meNOr((*N)->di);           //Procurar o menor do lado dos maiores

                (*N)->ch = aux->ch;                 //Copia ele para a raiz
                (*N)->valor = aux->valor;           //Copia o valor tamb�m
                RetVal = rem(&(*N)->di, aux->ch);
            }
        }

        if (*N)
            balancear(N);

    }else
        RetVal =  0;

    return RetVal;
}

no busca(no N,int ch){   	                //Fun��o recursiva de busca em �rvore.
	if(!N)return 0;
	if(N->ch == ch)					        //Se o n� em quest�o for igual a chave buscada
    	return N;						    //Retorna resultado positivo

	if(ch < N->ch)
		return busca(N->es,ch);           	//Se a chave � menor, busca � esquerda.
                                            //Caso contr�rio
	return busca(N->di, ch);		        //busca � direita.
}

void preO(no n){						    //Imprime a �rvore em pre ordem.
    if(n){
		printf("<%d %d %d> ", n->ch, n->valor, n->prof); //Imprime a chave, o valor e a profundidade onde o elemento se encontra.
		preO(n->es);
		preO(n->di);
	}
}





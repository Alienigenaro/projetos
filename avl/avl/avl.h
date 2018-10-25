#ifndef __AVL__
#define  __AVL__

typedef struct N{               //TAD da �rvore
   int ch;                      //Chave
   int valor;                   //Valor (registro)
   int prof;                    //Profundidade
   struct N *es;                //Refer�ncia ao filho esquerdo
   struct N *di;                //Refer�ncia ao filho direito
} * no;


int insere(no*, int,int);	    //Insere na �rvore e retorna 1 se conseguir, 0 caso contr�rio. Argumentos: Arvore chave valor
no busca(no, int);		        //Busca chave
int rem(no*, int);		        //Remove chave
void preO(no);				    //Imprime em pr� ordem



#endif



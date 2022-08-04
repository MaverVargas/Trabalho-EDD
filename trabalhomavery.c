#include <stdio.h>
#include <stdlib.h>

//quantidade de elementos
#define MAXTAM 10

typedef struct
{
    int ultimo;
    int elementos[MAXTAM];

} Lista;

//inicializando os valores de controle e criando a lista
Lista inicializaLista()
{
    Lista nova;
    //significa que a lista está vazia
    nova.ultimo = 0;

    return nova;
}

void imprimirLista(Lista *list)
{
	int i;
    for(i = 0; i < list->ultimo; i++)
        printf("%d ", list->elementos[i]);

    printf("\n");
}

void inserirLista(Lista *list, int valor, int pos)
{
	int i;
    //deve haver espaço
    if(list->ultimo < MAXTAM)
    {
        //elementos não podem ser incluidos depois do ultimo
        if(pos <= list->ultimo)
        {
            //desloca os elementos pra frente para liberar espaço na posição escolhida
            for(i = list->ultimo; i >= pos; i--)
                list->elementos[i] = list->elementos[i-1];

            //incluindo e aumentando o indice de ultimo
            list->elementos[pos] = valor;
            list->ultimo++;
        }
    }
}

void removerLista(Lista *list, int pos)
{
	int i;
    //indice não pode estar além do ultimo elemento
    if(pos <= list->ultimo)
    {
        //desloca os elementos pra trás
        for(i = pos; i < list->ultimo; i++)
            list->elementos[i] = list->elementos[i+1];

        //reduzindo o contador de ultimo
        list->ultimo--;
    }
}
////////////////////////////////////////////////////////
//estrutura do nó da Arvore
typedef struct No
{
    int info;
    struct No *esq;
    struct No *dir;
} No;
////////////////////////////////////////////////////////
//operaçõews da Arvore
No * criaNo(int valor)
{
    No * novo = malloc(sizeof(No));
    novo->esq = NULL;
    novo->dir = NULL;
    novo->info = valor;
    return novo;
}

void preOrdem(No * raiz)
{
    if(raiz != NULL)
    {
        printf("%d\n", raiz->info);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

void emOrdem(No * raiz)
{
    if(raiz != NULL)
    {
        emOrdem(raiz->esq);
        printf("%d\n", raiz->info);
        emOrdem(raiz->dir);
    }
}

void posOrdem(No * raiz)
{
    if(raiz != NULL)
    {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d\n", raiz->info);
    }
}

void incluir(No * raiz, int valor)
{
    //se menor
    if(valor < raiz->info)
    {
        //se nao tem filho esqueda
        if(raiz->esq == NULL)
            raiz->esq = criaNo(valor);
        else
            //desce na Ã¡rvore
            incluir(raiz->esq, valor);
    }
    //se maior
    else
    {
        //se nao tem filho direita
        if(raiz->dir == NULL)
            raiz->dir = criaNo(valor);
        else
            //desce na Ã¡rvore
            incluir(raiz->dir, valor);
    }
}

No * removeFolha(No * p)
{
    free (p);
    return NULL;
}

No * removeNo1Filho(No *p)
{
    No *aux;
    if(p->esq == NULL)
        aux = p->dir;
    else
        aux = p->esq;
    free (p);
    return aux;
}

No * menorSubArvDireita(No *p)
{
    No * aux = p->dir;
    while(aux->esq != NULL)
        aux = aux->esq;
    return aux;
}


No* remover(No *p, int x)
{
    if(p == NULL)
        return NULL;
    else if(x < p->info)
        p->esq = remover(p->esq,x);
    else if(x > p->info)
        p->dir = remover(p->dir,x);
    else // achou o no a ser removido
    {
        if((p->esq == NULL) &&
                (p->dir == NULL))
            p = removeFolha(p);
        else if((p->esq == NULL) ||
                (p->dir == NULL))
            p = removeNo1Filho(p);
        else
        {
            // p tem dois filhos
            No *aux = menorSubArvDireita(p);
            // troca as informacoes
            int tmp = p->info;
            p->info = aux->info;
            aux->info = tmp;
            // recursao: para a subarv. direita
            p->dir = remover(p->dir,x);
        }
    }
    return p;
}

void busca(No * raiz, int valor)
{
    if(raiz != NULL)
    {
        if(valor < raiz->info)
        {
            busca(raiz->esq, valor);
        }
        else if(valor > raiz->info)
        {
            busca(raiz->dir, valor);
        }
        else
        {
            printf("elemento %d encontrado", valor);
        }

    }
    else
    {
        printf("elemento %d nÃ£o encontrado", valor);
    }
}


No * insereListaArvore(No * raiz, Lista lst) {
	int i = 0;
    while(lst.elementos[i] != lst.ultimo) {
    	incluir(raiz, lst.elementos[i+1]);
    	i++;
	}
	
	return raiz;
}

////////////////////////////////////////////////////////
//principal

int main()
{
	// Inicializar lista
    Lista lst = inicializaLista();
    
    // Inicializar um contador i para auxiliar as subrotinas abaixo
	int i;
	
	// Inserindo elementos na Lista
    for(i = 0; i <= MAXTAM; i++)
    {
        inserirLista(&lst, i+1, i);
    }   
    
    // Declarando o nó raiz da Árvore
    No *raiz = criaNo(lst.elementos[0]);	
    
    // Inserindo os valores da Lista na Árvore
	raiz = insereListaArvore(raiz,lst);
	
	// Imprimindo os valores em ordem
	emOrdem(raiz);
	
    return 0;
}

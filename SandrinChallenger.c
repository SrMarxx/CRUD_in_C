//Desafio do professor Sandro de montar um CRUD usando arvore binaria.

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define MAX_STR 45

//estrutura de referencia para o CRUD

struct estruturaContato {
    char *email;
    char *nome;
    char *numero;
    struct estruturaContato *esq;
    struct estruturaContato *dir;
    struct estruturaContato *cima;
};
typedef struct estruturaContato Contato;

//cria uma árvore vazia
Contato* inicializa(); //finalizado

//verifica se a arvore está vazia
int estaVazia(Contato* a); //finalizado

//transforma todas as letras em maiusculas
char* verifica_str(char str[MAX_STR]); //finalizado

//verifica se a string digitada possui apenas numeros
char* verifica_int(char str[MAX_STR]); //finalizado

//verifica se o email é validando vendo se possui um @
char* verifica_email(char str[MAX_STR]); //finalizado

//cria um nó, dado a informação e as duas subárvores, semelhante a um método construtor
Contato* criaNo(char* nome, char* numero, char* email, Contato* esq, Contato* dir, Contato* cima); // finalizado

//Mostra os contatos em ordem alfabética
void imprimeIn(Contato* a); //finalizado

//compara duas strings
int compara(char n[MAX_STR], char m[MAX_STR]); //finalizado

//Método responsavel por adicionar os contatos
Contato *adicionar(Contato *atual, Contato novo, Contato* cima);//finalizado

//Método de busca, para encontrar um contato específico na agenda
Contato* buscar(Contato* a, char n[MAX_STR]); //finalizado

//Método interno readiciona os contatos
void readd(Contato* a, Contato* b); //finalizado

//Método que exclui um contato na agenda
Contato *excluir(Contato* a, Contato* b); //finalizado

int main() {

    //criando a arvore base e a que será usada para buscar
    Contato *atual = NULL;
    Contato *b = NULL;

    //criando e alocando uma string de nome para busca
    char* nome;
    nome = (char*)malloc(sizeof(char)*MAX_STR);

    //variaveis usadas para controle dos menus
    int exit;
    char  menu, menu1, menu2, mesmo;

    exit = 0;
    printf("\n======================================\nBem vindo a sua agenda virtual!\n======================================");

    //Cria um menu que estará sempre em execussão até que o usuário feche
    while (exit == 0) {

        printf("\n\nSelecione uma opcao: \n\n1. Adicionar contato. \n2. Listar Contatos. \n3. Buscar Contato. \n0. Sair. \n\nDigite.: ");
        menu = getche();

        while (menu != '0' && menu != '1' && menu != '2' && menu != '3') {

            printf("\n\nValor invalido, por favor digite novamente.: ");
            menu = getche();
        }

        switch(menu) {

        case '1':
            {
                Contato novo;
                novo.nome = (char*) malloc(sizeof(char)*MAX_STR);
                novo.numero = (char*) malloc(sizeof(char)*MAX_STR);
                novo.email = (char*) malloc(sizeof(char)*MAX_STR);

                system("cls");

                printf("\nDigite o nome do contato: ");
                gets(novo.nome);
                *novo.nome = verifica_str(novo.nome);
                fflush(stdin);
                if(*novo.nome == NULL){
                    printf("Contato nao adicionado.\n");
                    break;
                }

                printf("\nDigite o numero do contato: ");
                gets(novo.numero);
                *novo.numero = verifica_int(novo.numero);
                if(*novo.numero == NULL){
                    printf("Numero nao adicionado.\n\nVoce pode adicionar em Buscar Contato > 'nome' > Modificar > Numero.\n\n\n");
                    system("pause");
                }

                printf("\nDigite o email do contato: ");
                gets(novo.email);
                *novo.email = verifica_email(novo.email);
                if(*novo.email == NULL){
                    printf("Email nao adicionado.\n\nVoce pode adicionar em Buscar Contato > 'nome' > Modificar > Email.\n\n\n");
                    system("pause");
                }

                atual = adicionar(atual, novo, inicializa());

                system("cls");
                printf("\nContato %s adicionado com sucesso!\n\n", novo.nome);
            }

            break;

        case '2':

            system("cls");
            imprimeIn(atual);

            break;

        case '3':

            system("cls");

            printf("\n\nPor favor, digite o nome que deseja encontrar: ");
            gets(nome);

            *nome = verifica_str(nome);

            b = buscar(atual, nome);

            system("cls");

            if (b == NULL){
                printf("\n\nContato nao encontrado.\n\n");
            }
            else{
                printf("\n\nContato encontrado!\n\nNome: %s \nNumero: %s \nEmail: %s\n\n", b->nome, b->numero, b->email);
                printf("\nO que deseja fazer? \n\n0. Sair \n1. Modificar \n2. Deletar \n\nDigite: ");
                menu1 = getche();

                while (menu1 != '0' && menu1 != '1' && menu1 != '2') {

                    printf("\n\nValor invalido, por favor digite novamente.: ");
                    menu1 = getche();
                }
                switch(menu1){

                case '1':

                    printf("\n\nO que deseja modificar? \n\n1. Nome \n2. Numero \n3. Email \n0. Cancelar \n\nDigite: ");
                    menu2 = getche();
                    while (menu2 != '0' && menu2 != '1' && menu2 != '2' && menu2 != '3') {

                        printf("\n\nValor invalido, por favor digite novamente.: ");
                        menu2 = getche();
                    }

                    switch(menu2){

                    case '1':

                        {
                            Contato novo;
                            novo.nome = (char*) malloc(sizeof(char)*MAX_STR);


                            printf("\nDigite o novo nome do contato: ");
                            gets(novo.nome);
                            *novo.nome = verifica_str(novo.nome);
                            fflush(stdin);

                            novo.numero = b->numero;
                            novo.email = b->email;

                            atual = excluir(atual, b);

                            atual = adicionar(atual, novo, inicializa());

                            system("cls");
                            printf("\nContato %s modificado com sucesso!\n", novo.nome);
                        }
                        break;

                    case '2':
                        {
                            Contato novo;
                            novo.numero = (char*) malloc(sizeof(char)*MAX_STR);

                            printf("\nDigite o novo numero do contato: ");
                            gets(novo.numero);

                            *novo.numero = verifica_int(novo.numero);

                            b->numero = novo.numero;

                            system("cls");
                            printf("\nContato %s modificado com sucesso!\n", b->nome);
                        }
                        break;

                    case '3':
                        {
                            Contato novo;
                            novo.email = (char*) malloc(sizeof(char)*MAX_STR);

                            printf("\nDigite o novo email do contato: ");
                            gets(novo.email);

                            *novo.email = verifica_email(novo.email);

                            b->email = novo.email;

                            system("cls");
                            printf("\nContato %s modificado com sucesso!\n", b->nome);
                        }
                        break;

                    case '0':
                        system("cls");
                        printf("\n\nNenhuma alteracao efetuada.\n\n");
                        break;

                    }
                    break;

                case '2':
                    printf("\n\nTem certeza que deseja excluir %s da sua lista de contatos?(s ou n) \n\nDigite: ", b->nome);
                    mesmo = getche();

                    while (mesmo != 's' && mesmo != 'S' && mesmo != 'n' && mesmo != 'N') {

                        printf("\n\nValor invalido, por favor digite novamente.: ");
                        mesmo = getche();
                    }

                    if(mesmo == 's' || mesmo == 'S'){
                        atual = excluir(atual, b);
                        system("cls");
                        printf("\n\nContato excluido com sucesso.\n\n");
                    }
                    else{
                        printf("\n\n");
                    }

                    break;

                case '0':
                    printf("\n\n");
                    break;
                }

            }

            break;

        case '0':
            system("cls");
            printf("\n======================================\nObrigado e ate a proxima!\n======================================\n\n");
            exit = 1;

            break;


        }

    system("pause");
    system("cls");

    }

}

Contato* inicializa(){
 return NULL;
}

int estaVazia(Contato* a){
 return a == NULL;
}


char* verifica_str(char str[MAX_STR]){
    int var = 0;
    while (*(str+var) != 0){
        if (*(str+var)>0 && *(str+var)<32){
            printf("\n\nCaractere invalido\n\n");
            return NULL;
        }
        else if (*(str+var)>32 && *(str+var)<65){
            printf("\n\nCaractere invalido\n\n");
            return NULL;
        }
        else if (*(str+var)>90 && *(str+var)<96){
            printf("\n\nCaractere invalido\n\n");
            return NULL;
        }
        else if (*(str+var)>122){
            printf("\n\nCaractere invalido\n\n");
            return NULL;
        }
        else if (123 > *(str+var) && *(str+var) > 96){
            *(str+var) = *(str+var) - 32;
        }
        var++;
    }
    return *str;
}

char* verifica_int(char str[MAX_STR]){
    int var = 0;
    while (*(str+var) != 0){
        if (*(str+var)>0 && *(str+var)<48){
            printf("\n\nCaractere invalido\n\n");
            return NULL;
        }
        else if (*(str+var)>57){
            printf("\n\nCaractere invalido\n\n");
            return NULL;
        }
        var++;
    }
    return *str;
}

char* verifica_email(char str[MAX_STR]){
    int var = 0;
    while (*(str+var) != 0){
        if (*(str+var) == 64){
            return *str;
        }
        var++;
    }
    printf("\n\nEmail invalido\n\n");
    return NULL;
}

Contato* criaNo(char* nome, char* numero, char* email, Contato* esq, Contato* dir, Contato* cima){
    Contato* p = (Contato*) malloc(sizeof(Contato));
    p->nome = nome;
    p->email = email;
    p->numero = numero;
    p->esq = esq;
    p->dir = dir;
    p->cima = cima;
    return p;
}

Contato *adicionar(Contato *a, Contato novo, Contato* cima){
    int var = 0;

    if (estaVazia(a)){ //achou o ponto correto de inserção
        return criaNo(novo.nome, novo.numero, novo.email, inicializa(), inicializa(), cima);
    }
    else{
        if (*novo.nome < *a->nome){
            a->esq = adicionar(a->esq, novo, a);
        }
        if (*novo.nome > *a->nome){
            a->dir = adicionar(a->dir, novo, a);
        }
        while (*(novo.nome+var) == *(a->nome+var)){
            var++;
            if (*(novo.nome+var) < *(a->nome+var)){
                a->esq = adicionar(a->esq, novo, a);
            }
            if (*(novo.nome+var) > *(a->nome+var)){
                a->dir = adicionar(a->dir, novo, a);
            }
        }
        printf("Contato já existente");
        return a; //nó a ser inserido já existe, nada muda!
    }
}

void imprimeIn(Contato* a){
    if(!estaVazia(a)){
        imprimeIn(a->esq); /* mostra esquerda */
        printf("\n%s\n", a->nome); /* mostra raiz */
        imprimeIn(a->dir); /* mostra direita */
    }
}

Contato* buscar(Contato* a, char n[MAX_STR]){
    int var = 0;
    if(estaVazia(a)){
        return NULL;
    }
    if(compara(a->nome, n)){
        return a;
    }
    else{
        if (*n < *a->nome){
            return buscar(a->esq, n);
        }
        if (*n > *a->nome){
            return buscar(a->dir, n);
        }
        while (*(n+var) == *(a->nome+var)){
            var++;
            if (*(n+var) < *(a->nome+var)){
                return buscar(a->esq, n);
            }
            if (*(n+var) > *(a->nome+var)){
                return buscar(a->dir, n);
            }
        }
    }
}

int compara(char n[MAX_STR], char m[MAX_STR]){
    int var = 0;
    while (*(n+var) == *(m+var)){
            var++;
            if(*(n+var) == 0 && *(m+var) == 0 ){
                return 1;
            }
        }
    return 0;
}

Contato* excluir(Contato* a, Contato* b){
    if (estaVazia(b->cima) && estaVazia(b->esq) && estaVazia(b->dir)){
        free(b);
        return NULL;
    }
    else if(a == b){
        if(!estaVazia(a->dir)){
            Contato* c = a->dir;
            readd(c, c->dir);
            readd(c, a->esq);
            free(a);
            return c;
        }
        else{
            Contato* c = a->esq;
            readd(c, c->esq);
            readd(c, a->dir);
            free(a);
            return c;
        }
    }
    else if (estaVazia(b->esq) && estaVazia(b->dir)){
        Contato* c = b->cima;
        if(c->esq == b){
            c->esq = inicializa();
        }
        if(c->dir == b){
            c->dir = inicializa();
        }
        free(b);
    }
    else{
        Contato* c = b->cima;
        if(c->esq == b){
            c->esq = inicializa();
        }
        if(c->dir == b){
            c->dir = inicializa();
        }
        readd(a, b->esq);
        readd(a, b->dir);
        free(b);
    }
    return a;
}

void readd(Contato* a, Contato* b){
    if(!estaVazia(b)){
        readd(a, b->esq);
        readd(a, b->dir);
        adicionar(a, *b, inicializa());
        free(b);
    }
}

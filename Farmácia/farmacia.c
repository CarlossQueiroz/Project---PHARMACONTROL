#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "farmacia.h"

struct usuario{
	char nome[80];
    char email[80];
	char senha[20];
};

struct medicamento{
    int codigo;
    char nome[50];
    int estoque;
    float preco;
};

struct vendas{
    float valor;
    int quantidade;
    Medicamento med;
};

void limpar(){
	system("cls");
}

//__________________________ MEDICAMENTOS __________________________
struct noMed {
    Medicamento dado;
    struct noMed* prox;
};

struct lista{
    No01* inicio;
};

void adicionaMedicamentoFim(ListaMed *lista, Medicamento m) {
    No01* novo = (No01*) malloc(sizeof(No01));
    novo->dado = m;
    novo->prox = NULL;
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    }
    else {
        No01* pi;
        for (pi = lista->inicio; pi->prox != NULL; pi = pi->prox);
        pi->prox = novo;
    }
}

void mostrar(ListaMed *lista) {
    No01* pi;
    printf("Medicamentos\n");
    for (pi = lista->inicio; pi != NULL; pi = pi->prox){
        Medicamento dado = pi->dado;
        printf("%d: %s %d %.2f\n", dado.codigo,dado.nome,dado.estoque,dado.preco);
    }
}

void acrescentarEstoque(ListaMed* lista, int cod, int qtd) {
  if (lista->inicio == NULL) {
    printf("Lista vazia\n");
  }
  else {
    No01* pi;
    for (pi = lista->inicio; pi != NULL && pi->dado.codigo != cod; pi = pi->prox);
    if (pi == NULL) {
      printf("Medicamento não encontrado\n");
    }
    else {
      pi->dado.estoque += qtd;
      printf("Estoque atualizado!\n");
    }
  }  
}

void deletar(ListaMed *lista, int cod) {
  if (lista->inicio == NULL) {
    printf("Lista vazia\n");
  }
  else {
      No01* pa = NULL;
      No01* pi;
      for (pi = lista->inicio; pi->prox != NULL && pi->dado.codigo != cod; pi = pi->prox) {
        pa = pi;
      }
      if (pa == NULL) {
        if (pi->dado.codigo == cod) {
          lista->inicio = pi->prox;
          free(pi);
          printf("Medicamento excluido!\n");
        }
        else {
          printf("Medicamento não encontrado\n");
        }
      }
      else {
        if (pi->dado.codigo == cod) {
          pa->prox = pi->prox;
          free(pi);
          printf("Medicamento excluido!\n");
        }
        else {
          printf("Elemento não encontrado\n");
        }
      }
  }
}

void ler(Medicamento *m) {
    printf("Informe os dados do medicamento:\n");
    scanf("%d %s %d %f", &m->codigo, m->nome, &m->estoque,&m->preco);
}

int tamanho() {
    FILE* file = fopen("medicamentos.b", "rb");
    Medicamento m;
    int cont = 0;
    while (fread(&m, sizeof(Medicamento), 1, file)) {
        cont++;
    }
    fclose(file);
    return cont;
}

void cadastrar() {
    FILE* file = fopen("medicamentos.b", "ab");
    Medicamento m;
    ler(&m);
    fwrite(&m, sizeof(Medicamento), 1, file);
    fclose(file);
    printf("Medicamento cadastrado com sucesso!\n");
}

void listar() {
    FILE* file = fopen("medicamentos.b", "rb");
    int n = tamanho();
	Medicamento m;
    
    printf("Total de medicamentos: %d\n", n);
    while (fread(&m, sizeof(Medicamento), 1, file)) {
        printf("%d: %s %d %.2f\n", m.codigo,m.nome,m.estoque,m.preco);
    }
    fclose(file);
}

No01* pesquisar(ListaMed *lista,int cod){
	No01* pi;
	for (pi = lista->inicio; pi != NULL && pi->dado.codigo != cod; pi = pi->prox);
	return pi;
}

void lerLista(ListaMed *lista) {
  FILE *file = fopen("medicamentos.b", "rb");
  Medicamento m;
  while (fread(&m, sizeof(Medicamento), 1, file)) {
      adicionaMedicamentoFim(lista, m);
  }
  fclose(file);
}

void salvaLista(ListaMed *lista) {
  FILE *file = fopen("medicamentos.b", "wb");
  No01* pi;
  for (pi = lista->inicio; pi != NULL; pi = pi->prox) {
    fwrite(&pi->dado, sizeof(Medicamento), 1, file);
  }
  fclose(file);
}

void buscar (int cod) {
	ListaMed lista;
    lista.inicio = NULL;
    lerLista(&lista);
    No01* pi=pesquisar(&lista,cod);
    if(pi!=NULL){
		printf("%d: %s %d unidades %.2f\n", pi->dado.codigo,pi->dado.nome,pi->dado.estoque,pi->dado.preco);
	}
	else{
		printf("Medicamento não cadastrado!\n");
	}
}

void excluir(int cod) {
    ListaMed lista;
    lista.inicio = NULL;
    lerLista(&lista);
    deletar(&lista, cod);
    salvaLista(&lista);
}

int solicitarCodigo(){
	int cod;
	printf("Informe o código do medicamento:");
	scanf("%d",&cod);
	return cod;
}

//___________________________ VENDAS ___________________________
void RecarregarEstoque(int cod) {
    ListaMed lista;
    lista.inicio = NULL;
    lerLista(&lista);
    int quantidade;
    printf("Informe a quantidade adicionada em estoque:\n");
    scanf("%d", &quantidade);
    acrescentarEstoque(&lista, cod, quantidade);
    salvaLista(&lista);
}

void atualizarEstoque(ListaMed* lista, int cod, int qtd) {
  	if (lista->inicio == NULL) {
    	printf("Lista vazia\n");
  	}
  	else {
    	No01* pi;
    	for (pi = lista->inicio; pi != NULL && pi->dado.codigo != cod; pi = pi->prox);
    	if (pi == NULL) {
    		printf("Medicamento não encontrado\n");
    	}
    	else {
      		pi->dado.estoque -= qtd;
    	}
  	}  
}

void registrarVenda(int cod,char nome[],float valor,int qtd){
	FILE *file = fopen("vendas.b", "ab");
    Vendas venda;
    venda.quantidade=qtd;
    venda.valor=valor*qtd;
    venda.med.codigo=cod;
    strcpy(venda.med.nome,nome);
    fwrite(&venda, sizeof(Vendas), 1, file);
	fclose(file);
}

void venderMedicamentos(int cod) {
    ListaMed lista;
    lista.inicio = NULL;
    lerLista(&lista);
    No01* pi=pesquisar(&lista,cod);
    if(pi!=NULL){
		int qtd;
		printf("Informe a quantidade vendida:\n");
	    scanf("%d", &qtd);
	    atualizarEstoque(&lista, cod, qtd);
	    salvaLista(&lista);
	    registrarVenda(cod,pi->dado.nome,pi->dado.preco,qtd);
	    printf("Venda registrada com sucesso!\n");
	}
	else{
		printf("Medicamento não cadastrado!\n");
	}
}

void ordenar(ListaMed *lista){
	No01* pi;
	No01* pj;
	No01* pfim = NULL;
	if(lista->inicio==NULL){
		return;
	}
	for (pi = lista->inicio; pi->prox != NULL; pi = pi->prox){
		for (pj = lista->inicio; pj->prox != pfim; pj = pj->prox){
			if(pj->dado.estoque>pj->prox->dado.estoque){
				Medicamento temp = pj->dado;
				pj->dado=pj->prox->dado;
				pj->prox->dado=temp;
			}
		}
		pfim=pj;
	}
}

void medicamentoOrdenacao(){
	if(tamanho()>0){
		ListaMed lista;
    	lista.inicio = NULL;
    	lerLista(&lista);
    	ordenar(&lista);
    	mostrar(&lista);
	}
	else{
		printf("Nenhum medicamento encontrado!\n");
	}
}

float totalCaixa(){
	float total;
	FILE *file= fopen("vendas.b","rb");
	Vendas vendas;
	while(fread(&vendas,sizeof(Vendas),1,file)){
		total+=vendas.valor;
	}
	return total;
}

void exibirVendas(){
	limpar();
	printf("Medicamentos vendidos\n");
	FILE* file = fopen("vendas.b", "rb");
    Vendas venda;
    while (fread(&venda, sizeof(Vendas), 1, file)) {
        printf("%d - %s: %d vendidos. Valor: R$%.2f\n",venda.med.codigo,venda.med.nome,venda.quantidade,venda.valor);
    }
    fclose(file);
}

void saudacaoUsuario(){
	FILE* file = fopen("user.b", "rb");
    Usuario userLogin;
    fread(&userLogin, sizeof(Usuario), 1, file);
    printf("\nBem-vindo a PHARMACONTROL, %s\n",userLogin.nome);
    fclose(file);
}

//__________________________ Login __________________________

int validarEmail(char email[]) {
    int i, cont = 0;
    int tam = strlen(email);

	if (tam >= 80)
        return 0;
    
    for (i = 0; i < tam; i++) {
        if (email[i] == '@') {
            cont++;
        }
    }
    
    if (cont == 1 && email[0] != '@' && email[tam - 1] != '@')
        return 1;
    else
        return 0;
}

void cadastrarUsuario() {
	FILE* file = fopen("user.b", "ab");
    Usuario user;
    
    strcpy(user.nome,"Carlos Henrique de Queiroz");
    strcpy(user.email,"user@gmail.com");
    strcpy(user.senha,"user1357");
    
    if(validarEmail(user.email)){
    	fwrite(&user, sizeof(Usuario), 1, file);
	}    
    fclose(file);
}

void verificarUsuario(char email[],char senha[]) {
   	FILE* file = fopen("user.b", "rb");
    Usuario userLogin;
    int validar = 0,cont=0;
    
    while (fread(&userLogin, sizeof(Usuario), 1, file)) {	
		if(strcmp(email,userLogin.email) == 0 && strcmp(senha,userLogin.senha)==0){
			validar=1;
		}
		cont++;
    }
    fclose(file);
    
    if (validar == 0) {
        printf("Verifique seu login e senha!\n");
        if(cont==0){
        	cadastrarUsuario();
    	}
    }
    else{
    	grMenuVendas();
	}
    
}

void login(){
	char email[80];
    char senha[20];
    printf("E-mail: ");
    scanf("%s", email);
    printf("Senha: ");
    scanf("%s", senha);
    
    
    validarEmail(email) > 0 ? verificarUsuario(email,senha) : printf("E-mail inválido.\n");
}

#include <stdio.h>
#include <locale.h>
#include "farmacia.h"

//Menu de opçoes para manipulação dos medicamentos
void menuMed() {
    printf("- - - - - - - - - - - - - -\n");
	printf("Escolha uma opção:\n");
    printf("1 - Cadastar medicamento\n");
    printf("2 - Buscar medicamento\n");
    printf("3 - Excluir um medicamento\n");
    printf("4 - Listar medicamentos\n");
    //printf("5 - Editar medicamentos\n");
    printf("0 - Voltar\n");
    printf("- - - - - - - - - - - - - -\n");
}

//Gerenciador do menu de medicamentos
void grMenuMed(){
	limpar();
	int op,cod;
    menuMed();
    scanf("%d", &op);
    while (op != 0) {
        if (op == 1) {
        	limpar();
           cadastrar();
        }else if(op==2){
        	limpar();
        	cod = solicitarCodigo();
            buscar(cod);
		}else if (op == 3) {
			limpar();
            cod = solicitarCodigo();
            excluir(cod);
        }else if (op == 4) {
        	limpar();
        	int n = tamanho();
        	n > 0 ? listar() : printf("Nenhum medicamento encontrado.\n");
        } /*else if (op == 6) {
            cod = solicitarCodigo();
            editar(cod);
        }*/
		else{
        	printf("Opção inválida. Tente novamente!\n");
		}
        menuMed();
        scanf("%d", &op);
    }
}

//Menu de opções relacionado a vendas
void menuVendas(){
	printf("- - - - - - - - - - - - - - - - -\n");
	printf("Escolha uma opção:\n");
    printf("1 - Medicamentos\n");
    printf("2 - Recarregar estoque\n");
    printf("3 - Ordenar medicamento por estoque\n");
    printf("4 - Total caixa\n");
    printf("5 - Vender medicamento\n");
    printf("6 - Exibir Vendas\n");
    printf("0 - Sair\n");
    printf("- - - - - - - - - - - - - - - - -\n");

}

//Gerenciador do menu de opções relacionado a vendas
void grMenuVendas() {
	limpar();
	saudacaoUsuario();
	menuVendas();
    int op,cod; 
    scanf("%d", &op);
    
    while (op != 0){
    	if(op==1){
    		grMenuMed();
		}
		else if(op==2){
			limpar();
			cod = solicitarCodigo();
            RecarregarEstoque(cod);
		}
		else if(op==3){
			limpar();
			medicamentoOrdenacao();
		}
		else if(op==4){
			limpar();
			float resultado = totalCaixa();
			printf("CAIXA\nValor: R$%.2f\n\n",resultado);
		}
		else if(op==5){
			limpar();
			cod = solicitarCodigo();
			venderMedicamentos(cod);
		}
		else if(op==6){
			limpar();
			exibirVendas();
		}
        else{
        	printf("Opção inválida. Tente novamente!\n");
		}
    	menuVendas();
    	scanf("%d", &op);
        
    }
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	
    int op;
   	do {
   		printf("PHARMACONTROL\n\n");
        printf("1 - Login\n0 - Sair\n");
    	scanf("%d", &op);
    	
    	if (op == 1) {
           login();
        }
        system("pause");
        limpar();
    } while (op != 0);
    
    return 0;
}

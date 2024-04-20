#ifndef H_FARMACIA
#define H_FARMACIA

typedef struct usuario Usuario;
typedef struct medicamento Medicamento;
typedef struct vendas Vendas;
typedef struct lista ListaMed;
typedef struct noMed No01;

void limpar();

void adicionaMedicamentoFim(ListaMed *lista, Medicamento m);

void mostrar(ListaMed *lista);

void acrescentarEstoque(ListaMed* lista, int cod, int qtd);

void deletar(ListaMed *lista, int cod);

void ler(Medicamento *m);

int tamanho();

void cadastrar();

void listar();

No01* pesquisar(ListaMed *lista,int cod);

void lerLista(ListaMed *lista);

void salvaLista(ListaMed *lista);

void buscar (int cod);

void excluir(int cod);

int solicitarCodigo();

void RecarregarEstoque(int cod);

void atualizarEstoque(ListaMed* lista, int cod, int qtd);

void registrarVenda(int cod,char nome[],float valor,int qtd);

void venderMedicamentos(int cod);

void ordenar(ListaMed *lista);

void medicamentoOrdenacao();

float totalCaixa();

void exibirVendas();

void saudacaoUsuario();

int validarEmail(char email[]);

void cadastrarUsuario();

void verificarUsuario(char email[],char senha[]);

void login();

#endif

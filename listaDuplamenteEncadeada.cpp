#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado;

class Noh{
	friend class ListaDup;
	private:
		Dado dado;
		Noh* proximo;
		Noh* anterior;
	public:
		Noh(Dado d=0);
};
Noh::Noh(Dado d){
	dado = d;
	proximo = NULL;
	anterior = NULL;
}

class ListaDup{
	private:
		Noh* primeiro;
		Noh* ultimo;
		int tamanho;
		void removeTodos();
	public:
		ListaDup();
		ListaDup(const ListaDup& umaLista);
		~ListaDup();
		ListaDup& operator =(const ListaDup& umaLista);
		inline void insere(Dado dado);
		void insereNoFim(Dado dado);
		void insereNoInicio(Dado dado);
		void insereNaPosicao(int posicao, Dado dado);
		int procura(Dado valor);
		void imprime();
		inline bool vazia();
		void removeNoInicio();
		void removeNoFim();
		void removeValor(Dado valor);
};
ListaDup::ListaDup(){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}
ListaDup::ListaDup(const ListaDup& umaLista){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
	Noh* aux = umaLista.primeiro;
	while(aux != NULL){
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
}
ListaDup::~ListaDup(){
	removeTodos();
}
void ListaDup::removeTodos(){
	Noh* aux = primeiro;
	Noh* temp;
	while (aux != NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}
ListaDup&ListaDup::operator =(const ListaDup& umaLista){
	removeTodos();
	Noh* aux = umaLista.primeiro;
	while(aux != NULL){
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
	return* this;
}
void ListaDup::insere(Dado dado){
	insereNoFim(dado);
}
void ListaDup::insereNoFim(Dado dado){
	Noh* novo = new Noh(dado);
	if (vazia()){
		primeiro = novo;
		ultimo = novo;
	}
	else{
		ultimo->proximo = novo;
		novo->anterior = ultimo;
		ultimo = novo;
	}
	tamanho++;
}
void ListaDup::insereNoInicio(Dado dado){
	Noh* novo = new Noh(dado);
	if (vazia()){
		primeiro = novo;
		ultimo = novo;
	}
	else {
		novo->proximo = primeiro;
		primeiro->anterior = novo;
		primeiro = novo;
	}
	tamanho++;
}
void ListaDup::insereNaPosicao(int posicao, Dado dado){
	Noh* novo = new Noh(dado);
	if ((posicao <= tamanho) and (posicao >= 0)){
		if (vazia()){
			primeiro = novo;
			ultimo = novo;
		}
		else if(posicao == 0){
			novo->proximo = primeiro;
			primeiro->anterior = novo;
			primeiro = novo;
		}
		else if(posicao == tamanho){
			ultimo->proximo = novo;
			novo->anterior = ultimo;
			ultimo = novo;
		}
		else{
			Noh* aux = primeiro;
			int posAux = 0;
			while(posAux < (posicao-1)){
				aux = aux->proximo;
				posAux++;
			}
			novo->proximo = aux->proximo;
			aux->proximo->anterior = novo;
			aux->proximo = novo;
			novo->anterior = aux;
		}
		tamanho++;
	}
	else {
		cerr << "Posicao inexistente" << endl;
		exit(EXIT_FAILURE);
	}
}
int ListaDup::procura(Dado valor){
	Noh* aux = primeiro;
	int posAux = 0;
	while((aux != NULL) and (aux->dado != valor)){
		posAux++;
		aux = aux->proximo;
	}
	if(aux == NULL){
		posAux = -1;
	}
	return posAux;
}
void ListaDup::imprime(){
	Noh* aux = primeiro;
	while(aux != NULL){
		cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout << endl;
	aux = ultimo;
	while(aux != NULL){
		cout << aux->dado << " ";
		aux = aux->anterior;
	}
	cout << endl;
}
inline bool ListaDup::vazia(){
	return (primeiro == NULL);
}
void ListaDup::removeNoInicio(){
	if (vazia()){
		cerr << "Remocao em lista vazia" << endl;
		exit(EXIT_FAILURE);
	}
	Noh* removido = primeiro;
	primeiro = primeiro->proximo;
	if (primeiro != NULL){
		primeiro->anterior = NULL;
	}
	delete removido;
	tamanho--;
	if (tamanho == 0){
		ultimo = NULL;
	}
}
void ListaDup::removeNoFim(){
	if (vazia()){
		cerr << "Remocao em lista vazia" << endl;
		exit(EXIT_FAILURE);
	}
	Noh* removido = ultimo;
	ultimo = ultimo->anterior;
	if (ultimo != NULL){
		ultimo->proximo = NULL;
	}
	delete removido;
	tamanho--;
	if (tamanho == 0){
		primeiro = NULL;
	}
}
void ListaDup::removeValor(Dado valor){
	Noh* aux = primeiro;
	while((aux != NULL) and (aux->dado != valor)){
		aux = aux->proximo;
	}
	if (aux == NULL){
		cerr << "Erro: Remocao de valor nao encontrado" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		Noh* anterior = aux->anterior;
		Noh* proximo = aux->proximo;
		if (anterior != NULL){
			anterior->proximo = proximo;
		}
		else{
			primeiro = aux->proximo;
		}
		if (proximo != NULL){
			proximo->anterior = anterior;
		}
		else{
			ultimo = aux->anterior;
		}
		delete aux;
	}
	tamanho--;
	if (vazia()){
		primeiro = NULL;
		ultimo = NULL;
	}
}

int main (){
	ListaDup *elementos;
	elementos = new ListaDup();
	Dado capacidade = 10;
	Dado valor;
	for (int i=0; i<capacidade; i++){
		cin >> valor;
		elementos->insere(valor);
	}
	elementos->imprime();
	return 0;
}

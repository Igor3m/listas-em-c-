#include <iostream>

using namespace std;

typedef int Dado;

class Noh{
	friend class Lista;
	private:
	    Dado dado;
		Noh* proximo;
	public:
		Noh(Dado d = 0);
};
Noh::Noh(Dado d){
	dado = d;
	proximo = NULL;
}

class Lista{
	private:
		Noh* primeiro;
		Noh* ultimo;
		int tamanho;
		void removeTodos();
		void imprimeReversoAux(Noh* umNoh);
	public:
		Lista();
		Lista(const Lista& umaLista);
		~Lista();
		Lista& operator =(const Lista& umaLista);
		inline void insere(Dado dado);
		void insereNoFim(Dado dado);
		void insereNoInicio(Dado dado);
		void insereNaPosicao(int posicao, Dado dado);
		int procura(Dado valor);
		void imprime();
		void imprimeReverso();
		inline bool vazia();
		void removeNoFim();
		void removeNoInicio();
		void removeValor(int valor);
		void removeNaPosicao(int posicao);
};
Lista::Lista(){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}
Lista::Lista(const Lista& umaLista){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
	Noh* aux = umaLista.primeiro;
	while (aux != NULL){
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
}
Lista::~Lista(){
	removeTodos();
}
void Lista::removeTodos(){
	Noh* aux = primeiro;
	Noh* temp;
	while(aux != NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}
Lista&Lista::operator =(const Lista& umaLista){
	removeTodos();
	Noh* aux = umaLista.primeiro;
	while(aux != NULL){
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
	return* this;
}
void Lista::insere(Dado dado){
	insereNoFim(dado);
}
void Lista::insereNoFim(Dado dado){
	Noh* novo = new Noh(dado);
	if (vazia()){
		primeiro = novo;
		ultimo = novo;
	}
	else {
		ultimo->proximo = novo;
		ultimo = novo;
	}
	tamanho++;
}
void Lista::insereNoInicio(Dado dado){
	Noh* novo = new Noh(dado);
	if (vazia()){
		primeiro = novo;
		ultimo = novo;
	}
	else {
		novo->proximo = primeiro;
		primeiro = novo;
	}
	tamanho++;
}
void Lista::insereNaPosicao(int posicao, Dado dado){
	Noh* novo = new Noh(dado);
	if ((posicao <= tamanho) and (posicao >= 0)){
		if (vazia()){
			primeiro = novo;
			ultimo = novo;
		}
		else if (posicao == 0){
			novo->proximo = primeiro;
			primeiro = novo;
		}
		else if (posicao == tamanho){
			ultimo->proximo = novo;
			ultimo = novo;
		}
		else {
			Noh* aux = primeiro;
			int posAux = 0;
			while(posAux < (posicao-1)){
				aux = aux->proximo;
				posAux++;
			}
			novo->proximo = aux->proximo;
			aux->proximo = novo;
		}
		tamanho++;
	}
	else{
		cerr << "Posicao inexistente" << endl;
		exit(EXIT_FAILURE);
	}
}
int Lista::procura(Dado valor){
	Noh* aux = primeiro;
	int posAux = 0;
	while ((aux != NULL) and (aux->dado != valor)){
		posAux++;
		aux = aux->proximo;
	}
	if (aux == NULL){
		posAux = -1;
	}
	return posAux;
}
void Lista::imprime(){
	Noh* aux = primeiro;
	while (aux != NULL){
		cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout << endl;
}
void Lista::imprimeReverso(){
	imprimeReversoAux(primeiro);
	cout << endl;
}
void Lista::imprimeReversoAux(Noh* umNoh){
	if (umNoh != NULL){
		imprimeReversoAux(umNoh->proximo);
		cout << umNoh->dado << " ";
	}
}
inline bool Lista::vazia(){
	return (primeiro == NULL);
}
void Lista::removeNoFim(){
	if (vazia()){
		cerr << "Remocao em lista vazia" << endl;
		exit(EXIT_FAILURE);
	}
	Noh* aux = primeiro;
	Noh* anterior;
	while(aux->proximo != NULL){
		anterior = aux;
		aux = aux->proximo;
	}
	delete ultimo;
	anterior->proximo = NULL;
	ultimo = anterior;
	tamanho--;
	if (tamanho == 0){
		primeiro = NULL;
	}
}
void Lista::removeNoInicio(){
	if (vazia()){
		cerr << "Remocao em lista vazia" << endl;
		exit(EXIT_FAILURE);
	}
	Noh* removido = primeiro;
	primeiro = primeiro->proximo;
	delete removido;
	tamanho--;
	if (tamanho == 0){
		ultimo = NULL;
	}
}
void Lista::removeValor(int valor){
	if (vazia()){
		cerr << "Remocao em lista vazia" << endl;
		exit(EXIT_FAILURE);
	}
	Noh* auxiliar = primeiro;
	Noh* anterior;
	while((auxiliar != NULL) and (auxiliar->dado != valor)){
		anterior = auxiliar;
		auxiliar = auxiliar->proximo;
	}
	if (auxiliar != NULL){
		if(auxiliar->dado == primeiro->dado){
			removeNoInicio();
		}else if(auxiliar->dado == ultimo->dado){
			removeNoFim();
		}
		else{
			anterior->proximo = auxiliar->proximo;
			tamanho--;
			delete auxiliar;
		}
	}
	else{
		cerr << "Valor nao esta na lista" << endl;
		exit(EXIT_FAILURE);
	}
}
void Lista::removeNaPosicao(int posicao){
	if (vazia()){
		cerr << "Remocao em lista vazia" << endl;
		exit(EXIT_FAILURE);
	}
	Noh* auxiliar = primeiro;
	Noh* anterior;
	int pos = 0;
	while((auxiliar != NULL) and (pos < posicao)){
		anterior = auxiliar;
		auxiliar = auxiliar->proximo;
		pos++;
	}
	if (auxiliar != NULL){
		if (auxiliar->dado == primeiro->dado){
			removeNoInicio();
		}else if(auxiliar->dado == ultimo->dado){
			removeNoFim();
		}
		else{
			anterior->proximo = auxiliar->proximo;
			tamanho--;
			delete auxiliar;
		}
	}
	else{
		cerr << "Posicao nao esta na lista" << endl;
		exit(EXIT_FAILURE);
	}
	
}

int main(){
	Lista minhaLista;
	cout << "teste da lista" << endl;
	cout << "quantidade de valores a inserir: " << endl;
	int valor;
	int num;
	cin >> num;
	for (int i=0; i<num; i++){
		cin >> valor;
		minhaLista.insere(valor);
	}
	minhaLista.imprime();
	int v;
	cin >> v;
	cout << minhaLista.procura(v) << endl;;
	return 0;
}

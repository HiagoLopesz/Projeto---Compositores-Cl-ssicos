/*

	Tema : Compositores Clássicos
	Grupo: 33
	Membros: 
		- Marco Túlio Franco Silva
		- Hiago Anthony Lopes de Jesus
		- Lucas Reis Silvino

*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct compositores{
	int id;
	string nome, periodoVida, estilo, principalObra;
	bool ativo;
};

//Função que verifica o tamanho do arquivo e o retorna.
int verificaTamanho() {
	ifstream leitura("compositores.csv");
	string linha;
	int tamanho = 0;
	while (getline (leitura, linha)) {
		tamanho++;
	}
	return tamanho;
}

//Função que lê o arquivo e o armazena em um vetor de compositores.
int leitura (compositores *comp) {
	
	compositores compositor;
	ifstream leitura("compositores.csv");
	string linha;
	int tamanho = 0;
	while (getline (leitura, linha)) {

		/*
			istringstream linhaStream(linha) -> Transforma a linha em um stream.
			Ref: https://stackoverflow.com/questions/2323929/istringstream-how-to-do-this

			stringstream streamId(item) -> Transforma a string em um inteiro.
			Ref: https://www.javatpoint.com/convert-string-to-integer-in-cpp
		*/
		istringstream linhaStream(linha);
		string item;

		getline(linhaStream, item, ',');
		stringstream streamId(item);
		streamId >> compositor.id;

		getline(linhaStream, item, ',');
		compositor.nome = item;

		getline(linhaStream, item, ',');
		compositor.periodoVida = item;

		getline(linhaStream, item, ',');
		compositor.principalObra = item;

		getline(linhaStream, item, ',');
		compositor.estilo = item;

		getline(linhaStream, item, ',');
		stringstream streamAtivo(item);
		streamAtivo >> compositor.ativo;

		comp[tamanho] = compositor;
		tamanho++;
	}
	return tamanho;
}

//Função que diminue a letra de uma string para comparações.
string diminuirLetra(string frase){
	string novaFrase;
	for (int i = 0; i < (int) frase.size(); i++) {
		novaFrase += tolower(frase[i]);
	}
	return novaFrase;
}

//Função que imprime um compositor em alguma posicao.
void imprimirCompositor (compositores *comp, int posicao) {

	if (posicao == -1 ) {
		cout << "Compositor não encontrado!" << endl;
	} else {
		cout << endl;
		cout << "Compositor: " << endl;
		cout << "Id: " << comp[posicao].id << endl;
		cout << "Nome: " << comp[posicao].nome << endl;
		cout << "Ano de Nascimento e Morte: " << comp[posicao].periodoVida << endl;
		cout << "Estilo: " << comp[posicao].estilo << endl;
		cout << "Principal Obra: " << comp[posicao].principalObra << endl;
	}
}

//Função que lista todos os compositores.
void listarCompositoresAtivos (compositores *comp, int tamanho) {

	for(int i = 0; i < tamanho; i++) {
		if (comp[i].ativo) {
			imprimirCompositor(comp, i);
		}
	}
}

//Função que busca um compositor por id e retorna a posição dele no vetor.
int buscarPosicaoPorId (compositores *comp, int tamanho) {

	int idProcurado;
	cin >> idProcurado;
	for(int i = 0; i < tamanho; i++) {
		if (comp[i].id == idProcurado and comp[i].ativo) {
			return i;
		}
	}
	return -1;
}

//Função que busca um compositor por nome e chama a função imprimeCompositor, para todas as ocorrencias.
void buscaPorNome (compositores *comp, int tamanho){

	string nomeProcurado;
	bool achou = false;
	cin.ignore();
	getline(cin,nomeProcurado);
	for(int i = 0; i < tamanho; i++){
		/*
			Verifica se o nome procurado está contido no nome do compositor e tem que ser diferente
			do valor npos,que é o valor retornado quando não é encontrado o nome procurado.
			Ref: https://cplusplus.com/reference/string/string/find/
		*/
		if(diminuirLetra(comp[i].nome).find(diminuirLetra(nomeProcurado)) != string::npos && comp[i].ativo){
			imprimirCompositor(comp, i);
			achou = true;
		}
	}
	if (achou == false) {
		cout << "Nome não encontrado!" << endl;
	}
}

//Função que busca um compositor por estilo e chama a função imprimeCompositor, para todas as ocorrencias.
void buscarPorEstilo (compositores *comp, int tamanho){

	string qualEstilo;
	bool achou = false;
	cin.ignore();
	getline(cin,qualEstilo);
	for(int i = 0; i < tamanho; i++){
		if(diminuirLetra(comp[i].estilo) == diminuirLetra(qualEstilo) and comp[i].ativo){
			imprimirCompositor(comp, i);
			achou = true;
		}
	}
	if (achou == false) {
		cout << "Estilo não encontrado!" << endl;
	}
	
}

//Função que grava no arquivo os compositores.
void gravar(compositores *comp, int tamanho) {

	ofstream escrita("compositores.csv");
	
	for(int i=0; i< tamanho; i++) {
		escrita << comp[i].id << "," 
		<< comp[i].nome << "," 
		<< comp[i].periodoVida << "," 
		<< comp[i].principalObra << ","
		<< comp[i].estilo << "," 
		<< comp[i].ativo << endl;
	}

	escrita.close();
}

//Função que edita um compositor no vetor.
compositores* editar(compositores *comp, int posicao) {
	if (posicao == -1) {
		cout << "Não existe esse compositor" << endl;
		return comp;
	}

	string nome, ano, estilo, obra;
	cin.ignore();
	cout << "Insira o nome : ";
	getline(cin, nome);
	cout << "Insira o ano de nascimento : ";
	cin >> ano;
	cout << "Insira o estilo : ";
	cin>> estilo;
	cin.ignore();
	cout << "Insira a principal obra : ";
	getline(cin, obra);

	comp[posicao].nome = nome;
	comp[posicao].periodoVida = ano;
	comp[posicao].estilo = estilo;
	comp[posicao].principalObra = obra;

	cout << "Editado com sucesso!!" << endl;

	return comp;
}

//Função que exclui logicamente um compositor do vetor.
compositores* excluir(compositores *comp, int posicao) {

	if (posicao == -1) {
		cout << "Não existe esse compositor" << endl;
		return comp;
	}

	comp[posicao].ativo = false;
	cout << "Excluido com sucesso!!" << endl;
	return comp;
}

//Função que aumenta o tamanho do vetor.
compositores* aumenta(compositores *c, int &tamanho) {
	compositores *novo = new compositores [tamanho+1];
	//origem, quantidade, destino
	copy(c, c+tamanho, novo);
	tamanho += 1;
	delete [] c;
	return novo;
}

//Função que insere um compositor no vetor.
compositores* inserir (compositores *comp, int &tamanho) {
	comp = aumenta(comp, tamanho);
	compositores compositor;
	int id = tamanho;
	string nome, ano, estilo, obra;

	cin.ignore();
	cout << "Insira o nome : ";
	getline(cin, nome);
	cout << "Insira o ano de nascimento : ";
	cin >> ano;
	cout << "Insira o estilo : ";
	cin>> estilo;
	cin.ignore();
	cout << "Insira a principal obra : ";
	getline(cin, obra);

	compositor.id = id;
	compositor.nome = nome;
	compositor.periodoVida = ano;
	compositor.estilo = estilo;
	compositor.principalObra = obra;

	comp[tamanho-1] = compositor;
	cout << "Inserido com sucesso!!" << endl;

	return comp;
}

void menu_principal(compositores *comp, int &tamanho) {
	int escolha, busca;
	bool loop = true;
	while (loop) {
		cout << endl;
		cout << "Escolha uma opcao:" << endl
			  << "  1 - Inserir" << endl
			 << "  2 - Busca" << endl
			 << "  3 - Editar" << endl
			 << "  4 - Excluir" << endl
			 << "  5 - Gravar" << endl
			 << "  6 - Sair" << endl
			 <<"Digite sua escolha: ";
		cin >> escolha;
		switch (escolha) {
			case 1:
				cout << endl;
				comp = inserir(comp, tamanho);
				break;
			case 2:
				cout << endl;
				cout << "Escolha uma opcao:" << endl
					<< "  1 - Buscar todos " << endl
					<< "  2 - ID " << endl
					<< "  3 - Nome " << endl
					<< "  4 - Estilo " << endl
					<<"Digite sua escolha: ";
				cin >> busca;
				switch (busca) {
					case 1:
						cout << endl;
						cout << "Todos encontrados: " << endl;
						listarCompositoresAtivos(comp, tamanho);
						cout << endl;
						break;
					case 2:
						cout << endl;
						cout << "Busca por ID: ";
						cout<<"Diga-me o ID que quer procurar?";
						cout<<endl<<"--> ";
						imprimirCompositor(comp, buscarPosicaoPorId(comp, tamanho));
						cout << endl;
						break;
					case 3:
						cout << endl;
						cout << "Busca por nome: " << endl;
						cout<<"Diga-me o nome que quer procurar?";
						cout<<endl<<"--> ";
						buscaPorNome(comp, tamanho);
						cout << endl;
						break;
					case 4:
						cout << endl;
						cout << "Busca por estilo musical: " << endl;
						cout<<"Diga-me o estilo do compositor que você deseja?";
						cout<<endl<<"--> ";
						buscarPorEstilo(comp, tamanho);
						cout << endl;
						break;
				}
				break;
			case 3:
				cout << endl;
				cout << "Insira o ID do compositor que deseja editar: ";
				comp = editar(comp, buscarPosicaoPorId(comp, tamanho));
				break;
			case 4:
				cout << endl;
				cout << "Coloque o ID do compositor que deseja excluir: ";
				comp = excluir(comp, buscarPosicaoPorId(comp, tamanho));
				break;
			case 5:
				cout << endl;
				cout << "Gravando.." << endl;
				gravar(comp, tamanho);
				break;
			case 6:
				cout << endl;
				cout << "Saindo..." << endl;
				loop = false; // Definir ward como false para sair do loop
				break;
				
			default:
				cout << "OPCAO INVALIDA!!!" << endl;
				break; 
		}
	}
}

int main () {

	int tamanho = verificaTamanho();
	compositores *comp = new compositores[tamanho];

	tamanho = leitura(comp);

	menu_principal(comp, tamanho); 

	return 0;
}

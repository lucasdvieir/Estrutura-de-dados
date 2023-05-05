#include <iostream>
#include <string>
#include <cstdlib> // para usar a fun��o system

using namespace std;

// Struct que representa um funcion�rio
struct Funcionario {
    int prontuario;
    string nome;
    double salario;
    Funcionario* proximo; // Ponteiro para o pr�ximo funcion�rio na lista
};

// Fun��o que exibe o menu e retorna a op��o escolhida
int exibirMenu() {
    int opcao;
    cout << "Menu:" << endl;
    cout << "0. Sair" << endl;
    cout << "1. Incluir" << endl;
    cout << "2. Excluir" << endl;
    cout << "3. Pesquisar" << endl;
    cout << "4. Listar" << endl;
    cout << "Digite a op��o desejada: ";
    cin >> opcao;
    return opcao;
}

// Fun��o que busca um funcion�rio na lista pelo prontu�rio
Funcionario* buscarFuncionario(int prontuario, Funcionario* lista) {
    Funcionario* atual = lista;
    while (atual != NULL) {
        if (atual->prontuario == prontuario) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL; // Retorna NULL se o funcion�rio n�o foi encontrado
}

// Fun��o que insere um novo funcion�rio na lista
void inserirFuncionario(Funcionario** lista) {
    Funcionario* novo = new Funcionario;

    // L� os dados do novo funcion�rio
    cout << "Digite o prontu�rio do funcion�rio: ";
    cin >> novo->prontuario;
    cout << "Digite o nome do funcion�rio: ";
    cin.ignore();
    getline(cin, novo->nome);
    cout << "Digite o sal�rio do funcion�rio: ";
    cin >> novo->salario;

    // Verifica se j� existe um funcion�rio com o mesmo prontu�rio na lista
    if (buscarFuncionario(novo->prontuario, *lista) != NULL) {
        cout << "J� existe um funcion�rio com o mesmo prontu�rio na lista!" << endl;
        delete novo; // Libera a mem�ria alocada para o novo funcion�rio
    }
    else {
        novo->proximo = *lista; // O novo funcion�rio aponta para o in�cio da lista
        *lista = novo; // Atualiza o in�cio da lista para o novo funcion�rio
        cout << "Funcion�rio inclu�do com sucesso!" << endl;
    }
}

// Fun��o que remove o funcion�rio mais antigo da lista
void removerFuncionario(Funcionario** lista) {
    // Verifica se a lista est� vazia
    if (*lista == NULL) {
        cout << "N�o h� funcion�rios cadastrados!" << endl;
    }
    else {
        Funcionario* antigo = *lista; // O funcion�rio mais antigo � o primeiro da lista
        Funcionario* aux = NULL;
        while (antigo->proximo != NULL) {
            aux = antigo;
            antigo = antigo->proximo; // Atualiza o in�cio da lista para o pr�ximo funcion�rio
        }
        aux->proximo = NULL;
        delete antigo; // Libera a mem�ria alocada para o funcion�rio mais antigo
        cout << "Funcion�rio removido com sucesso!" << endl;
    }
}

// Fun��o que lista todos os funcion�rios da lista
void listarFuncionarios(Funcionario* lista) {
    // Verifica
    if (lista == NULL) {
        cout << "N�o h� funcion�rios cadastrados!" << endl;
    }
    else {
        double totalSalarios = 0.0;
        Funcionario* atual = lista;
        while (atual != NULL) {
            cout << "Prontu�rio: " << atual->prontuario << endl;
            cout << "Nome: " << atual->nome << endl;
            cout << "Sal�rio: " << atual->salario << endl;
            totalSalarios += atual->salario;
            atual = atual->proximo;
        }
        cout << "Total de sal�rios: " << totalSalarios << endl;
    }
}

// Fun��o principal
int main() {
    Funcionario* lista = NULL; // Inicia a lista vazia
    Funcionario* encontrado;
    int opcao = -1;
    while (opcao != 0) {
        opcao = exibirMenu();

        switch (opcao) {
        case 0:
            cout << "Encerrando o programa..." << endl;
            break;
        case 1:
            inserirFuncionario(&lista);
            break;
        case 2:
            removerFuncionario(&lista);
            break;
        case 3:
            int prontuario;
            cout << "Digite o prontu�rio do funcion�rio a ser pesquisado: ";
            cin >> prontuario;
            encontrado = buscarFuncionario(prontuario, lista);
            if (encontrado != NULL) {
                cout << "Prontu�rio: " << encontrado->prontuario << endl;
                cout << "Nome: " << encontrado->nome << endl;
                cout << "Sal�rio: " << encontrado->salario << endl;
            }
            else {
                cout << "Funcion�rio n�o encontrado!" << endl;
            }
            break;
        case 4:
            listarFuncionarios(lista);
            break;
        default:
            cout << "Op��o inv�lida!" << endl;
            break;
        }

        system("pause"); // Pausa o programa para o usu�rio ver a mensagem
        system("cls"); // Limpa o prompt
    }

    // Libera a mem�ria alocada para todos os funcion�rios da lista
    Funcionario* atual = lista;
    while (atual != NULL) {
        Funcionario* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }

    return 0;
}
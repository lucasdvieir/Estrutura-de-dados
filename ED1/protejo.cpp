#include <iostream>
#include <string>
#include <cstdlib> // para usar a função system

using namespace std;

// Struct que representa um funcionário
struct Funcionario {
    int prontuario;
    string nome;
    double salario;
    Funcionario* proximo; // Ponteiro para o próximo funcionário na lista
};

// Função que exibe o menu e retorna a opção escolhida
int exibirMenu() {
    int opcao;
    cout << "Menu:" << endl;
    cout << "0. Sair" << endl;
    cout << "1. Incluir" << endl;
    cout << "2. Excluir" << endl;
    cout << "3. Pesquisar" << endl;
    cout << "4. Listar" << endl;
    cout << "Digite a opção desejada: ";
    cin >> opcao;
    return opcao;
}

// Função que busca um funcionário na lista pelo prontuário
Funcionario* buscarFuncionario(int prontuario, Funcionario* lista) {
    Funcionario* atual = lista;
    while (atual != NULL) {
        if (atual->prontuario == prontuario) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL; // Retorna NULL se o funcionário não foi encontrado
}

// Função que insere um novo funcionário na lista
void inserirFuncionario(Funcionario** lista) {
    Funcionario* novo = new Funcionario;

    // Lê os dados do novo funcionário
    cout << "Digite o prontuário do funcionário: ";
    cin >> novo->prontuario;
    cout << "Digite o nome do funcionário: ";
    cin.ignore();
    getline(cin, novo->nome);
    cout << "Digite o salário do funcionário: ";
    cin >> novo->salario;

    // Verifica se já existe um funcionário com o mesmo prontuário na lista
    if (buscarFuncionario(novo->prontuario, *lista) != NULL) {
        cout << "Já existe um funcionário com o mesmo prontuário na lista!" << endl;
        delete novo; // Libera a memória alocada para o novo funcionário
    }
    else {
        novo->proximo = *lista; // O novo funcionário aponta para o início da lista
        *lista = novo; // Atualiza o início da lista para o novo funcionário
        cout << "Funcionário incluído com sucesso!" << endl;
    }
}

// Função que remove o funcionário mais antigo da lista
void removerFuncionario(Funcionario** lista) {
    // Verifica se a lista está vazia
    if (*lista == NULL) {
        cout << "Não há funcionários cadastrados!" << endl;
    }
    else {
        Funcionario* antigo = *lista; // O funcionário mais antigo é o primeiro da lista
        Funcionario* aux = NULL;
        while (antigo->proximo != NULL) {
            aux = antigo;
            antigo = antigo->proximo; // Atualiza o início da lista para o próximo funcionário
        }
        aux->proximo = NULL;
        delete antigo; // Libera a memória alocada para o funcionário mais antigo
        cout << "Funcionário removido com sucesso!" << endl;
    }
}

// Função que lista todos os funcionários da lista
void listarFuncionarios(Funcionario* lista) {
    // Verifica
    if (lista == NULL) {
        cout << "Não há funcionários cadastrados!" << endl;
    }
    else {
        double totalSalarios = 0.0;
        Funcionario* atual = lista;
        while (atual != NULL) {
            cout << "Prontuário: " << atual->prontuario << endl;
            cout << "Nome: " << atual->nome << endl;
            cout << "Salário: " << atual->salario << endl;
            totalSalarios += atual->salario;
            atual = atual->proximo;
        }
        cout << "Total de salários: " << totalSalarios << endl;
    }
}

// Função principal
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
            cout << "Digite o prontuário do funcionário a ser pesquisado: ";
            cin >> prontuario;
            encontrado = buscarFuncionario(prontuario, lista);
            if (encontrado != NULL) {
                cout << "Prontuário: " << encontrado->prontuario << endl;
                cout << "Nome: " << encontrado->nome << endl;
                cout << "Salário: " << encontrado->salario << endl;
            }
            else {
                cout << "Funcionário não encontrado!" << endl;
            }
            break;
        case 4:
            listarFuncionarios(lista);
            break;
        default:
            cout << "Opção inválida!" << endl;
            break;
        }

        system("pause"); // Pausa o programa para o usuário ver a mensagem
        system("cls"); // Limpa o prompt
    }

    // Libera a memória alocada para todos os funcionários da lista
    Funcionario* atual = lista;
    while (atual != NULL) {
        Funcionario* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }

    return 0;
}
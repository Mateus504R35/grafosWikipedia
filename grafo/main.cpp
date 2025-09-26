#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include "grafo.h"

// Trim in-place: remove espaços iniciais/finais e '\r' do fim
static inline void trim_inplace(std::string& s) {
    while (!s.empty() && (s.back() == '\r' || std::isspace(static_cast<unsigned char>(s.back())))) s.pop_back();
    size_t i = 0;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) i++;
    s.erase(0, i);
}

static int ler_opcao() {
    std::string entrada;
    std::getline(std::cin, entrada);
    trim_inplace(entrada);
    if (entrada.empty()) return -1;
    for (char c : entrada) {
        if (!std::isdigit(static_cast<unsigned char>(c)) && !(c == '-' && &c == &entrada[0])) {
            return -1;
        }
    }
    try {
        return std::stoi(entrada);
    } catch (...) {
        return -1;
    }
}

int main() {
    grafo g;

    // 1) Pergunta o caminho do arquivo
    std::cout << "Digite o caminho do arquivo .txt (TSV com 3 colunas separadas por TAB):\n> ";
    std::string caminho;
    std::getline(std::cin, caminho);
    trim_inplace(caminho);

    std::ifstream wikipedia(caminho, std::ios::in);
    if (!wikipedia.is_open()) {
        std::cerr << "Nao foi possivel abrir o arquivo: [" << caminho << "]\n";
        std::cerr << "Verifique se o caminho existe e se voce tem permissao de leitura.\n";
        return 1;
    }

    // 2) Carrega o grafo
    std::string linha;
    size_t numeroLinha = 0;
    while (std::getline(wikipedia, linha)) {
        ++numeroLinha;
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        std::string parte1, parte2, parte3;

        // Espera-se: origem \t link \t destino
        if (!std::getline(ss, parte1, '\t')) continue;
        if (!std::getline(ss, parte2, '\t')) continue;
        if (!std::getline(ss, parte3, '\t')) continue;

        trim_inplace(parte1);
        trim_inplace(parte2);
        trim_inplace(parte3);

        if (parte1.empty() || parte3.empty()) {
            std::cerr << "Aviso: linha " << numeroLinha << " ignorada (origem/destino vazio).\n";
            continue;
        }

        g.addAresta(std::move(parte1), std::move(parte3), std::move(parte2));
    }
    wikipedia.close();

    // 3) Menu interativo
    while (true) {
        std::cout << "\n===== MENU =====\n"
                     "1) Imprimir grafo inteiro\n"
                     "2) Encontrar menor caminho (BFS)\n"
                     "0) Sair\n"
                     "Escolha uma opcao: ";
        int op = ler_opcao();

        if (op == 0) {
            std::cout << "Encerrando...\n";
            break;
        } else if (op == 1) {
            g.printaGrafo();
        } else if (op == 2) {
            std::string origem, destino;
            std::cout << "Digite o titulo de origem:\n> ";
            std::getline(std::cin, origem);
            trim_inplace(origem);

            std::cout << "Digite o titulo de destino:\n> ";
            std::getline(std::cin, destino);
            trim_inplace(destino);

            if (origem.empty() || destino.empty()) {
                std::cout << "Origem/Destino nao pode ser vazio.\n";
                continue;
            }

            g.bfs(origem, destino);
        } else {
            std::cout << "Opcao invalida. Tente novamente.\n";
        }
    }

    return 0;
}

#include "grafo.h"

grafo::grafo() {}

void grafo::addAresta(const string &tituloOrigem, const string &tituloDestino, const string &link) {
    // cria a aresta direção origem -> destino
    listaAdjacencia[tituloOrigem].push_back({tituloDestino, link});
    // garante que o destino também exista como chave (mesmo que sem vizinhos)
    (void)listaAdjacencia[tituloDestino];
}

void grafo::bfs(const string &tituloOrigem, const string &tituloDestino) {
    unordered_map<string, bool> visitado;              // Para marcar os vértices visitados
    unordered_map<string, string> pai;                 // Para guardar o pai de cada nó
    queue<string> fila;

    // ---- Diagnóstico útil: existência de origem/destino ----
    if (!listaAdjacencia.count(tituloOrigem)) {
        cout << "Aviso: origem nao existe/nao tem vizinhos: [" << tituloOrigem << "]\n";
    }
    bool destinoExiste = listaAdjacencia.count(tituloDestino) > 0;
    for (auto & [orig, viz] : listaAdjacencia) {
        for (auto & [dst, _] : viz) if (dst == tituloDestino) destinoExiste = true;
    }
    if (!destinoExiste) {
        cout << "Aviso: destino nao aparece no grafo (nem como origem, nem como destino): ["
             << tituloDestino << "]\n";
    }
    // --------------------------------------------------------

    fila.push(tituloOrigem);
    visitado[tituloOrigem] = true;
    pai[tituloOrigem] = "";                            // O nó inicial não tem pai

    while (!fila.empty()) {
        string v = fila.front();
        fila.pop();

        if (v == tituloDestino) {
            // Se chegamos ao destino, reconstrua o caminho
            vector<string> caminho;
            for (string at = tituloDestino; !at.empty(); at = pai[at]) {
                caminho.push_back(at);
            }
            reverse(caminho.begin(), caminho.end());    // Inverte o caminho para ficar da origem até o destino

            cout << "Menor caminho: " << endl;
            for (const string &vertice : caminho) {
                cout << "-> " << vertice << " ";
            }
            cout << endl;
            return;
        }

        for (auto &vizinho : listaAdjacencia[v]) {
            if (!visitado[vizinho.first]) {
                fila.push(vizinho.first);
                visitado[vizinho.first] = true;
                pai[vizinho.first] = v;                // Registra o pai do vizinho
            }
        }
    }

    cout << "Caminho não encontrado!" << endl;
}

void grafo::printaGrafo() {
    for (auto &[vertice, vizinhos] : listaAdjacencia) {
        cout << "Vertice [  " << vertice << "  ] esta conectado a: " << endl;
        for (const auto& [vizinho, peso] : vizinhos) {
            cout << "  -> {  " << vizinho << "  } com link >> " << peso << endl;
        }
    }
}

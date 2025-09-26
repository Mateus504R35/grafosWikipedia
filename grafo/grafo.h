#ifndef TREINAMENTO_GRAFO_H
#define TREINAMENTO_GRAFO_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int MAX_V = 1010;

class grafo {
private:
        int numVertices;
        unordered_map<string, vector<pair<string, string>>> listaAdjacencia;
public:
        grafo();

        void addAresta(const string &tituloOrigem, const string &tituloDestino, const string &link);

        void bfs(const string &tituloOrigem, const string &tituloDestino);

        void printaGrafo();
};

#endif //TREINAMENTO_GRAFO_H

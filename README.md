# Projeto Wikipedia Scraper & Graph Builder

Este projeto realiza **web scraping** de páginas da Wikipedia usando **R** e, em seguida, constrói um **grafo de conexões** entre os artigos coletados utilizando **C++**.  

## Autores
Mateus Eurípedes Malaquias Soares
Marcella Silva Figueredo

## Estrutura do Projeto

- **`R/`** → Contém os scripts em R responsáveis por:
  - Fazer o scraping das páginas da Wikipedia.
  - Extrair links e conteúdos relevantes.
  - Salvar os dados processados em um arquivo `.txt` para uso posterior.

- **`Cpp/`** → Contém os códigos em C++ responsáveis por:
  - Ler o arquivo `.txt` gerado pelo R.
  - Construir um grafo direcionado/não-direcionado com base nas conexões entre páginas.
  - Possibilitar análises e visualizações da rede.

## Fluxo de Execução

1. **Coleta de Dados (R)**  
   - O script em R acessa páginas da Wikipedia.  
   - Extrai links/artigos relacionados.  
   - Salva o resultado em um arquivo `.txt`.  

2. **Construção do Grafo (C++)**  
   - O código em C++ lê o arquivo `.txt`.  
   - Monta um grafo em memória, onde os nós representam artigos e as arestas representam links entre eles.  
   - Permite exportar ou processar esse grafo para análises posteriores.  

## Como Usar

### Pré-requisitos
- **R** (≥ 4.0) com os pacotes necessários (ex.: `rvest`, `dplyr`, `stringr`).  
- **Compilador C++** compatível com C++11 ou superior (ex.: `g++`, `clang++`).  

### Passos
1. Execute o script em R para gerar o arquivo de saída:
   ```bash
   Rscript wikipedia_scraper.R
   ```
   → Isso criará um arquivo `links.txt`.

2. Compile o código C++:
   ```bash
   g++ main.cpp -o graph
   ```

3. Rode o programa para montar o grafo:
   ```bash
   ./graph links.txt
   ```

## Saídas
- **`links.txt`** → Arquivo intermediário com os dados do scraping.  
- **Estrutura de Grafo** em memória (ou exportada para arquivo, dependendo da implementação em C++).  


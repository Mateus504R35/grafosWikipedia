library(stringr)
library(WikipediR)
library(future.apply)

plan(multisession)  # Habilitar processamento paralelo

pagina_inicial <- "Teoria dos grafos"

# Função para guardar links já visitados
visited_links <- list()

# Função para verificar se o título é válido
is_valid_title <- function(title) {
  # Verifica se o título contém HTML ou caracteres inválidos
  invalid_patterns <- c("<span", "<i>", "</i>", "<", ">", "&", ";", "=")
  for (pattern in invalid_patterns) {
    if (grepl(pattern, title)) {
      return(FALSE)  # Se encontrar qualquer padrão inválido, retorna FALSE
    }
  }
  return(TRUE)  # Se nenhum padrão inválido for encontrado, retorna TRUE
}

scrape_page <- function(pagina_inicial) {
  if (pagina_inicial %in% visited_links) {
    return(data.frame(Origem=character(), Link=character(), Destino=character()))
  }
  
  visited_links <<- append(visited_links, pagina_inicial)
  
  Sys.sleep(1)  # Pausa de 1 segundo antes de cada requisição
  
  grafo_wikipedia <- data.frame(Origem=character(), Link=character(), Destino=character(), stringsAsFactors=FALSE)
  
  page_metadata <- page_info("pt", "wikipedia", page = pagina_inicial)
  page_metadata_unlist <- unlist(page_metadata)
  page_title <- as.vector(page_metadata_unlist[length(page_metadata_unlist)])
  page_url <- as.vector(page_metadata_unlist[length(page_metadata_unlist)-1])
  
  links <- page_backlinks("pt", "wikipedia", page = pagina_inicial, limit = 10)
  titulos <- lapply(links$query$backlinks, function(backlink) {
    backlink$title
  })
  vec <- unlist(titulos)
  
  # Filtrar links indesejados
  vec <- grep("(Usuári.+)", vec, value = TRUE, invert = TRUE)
  vec <- grep("Wikipédia|Livro|Portal|Discussão|Predefinição|Ajuda:Perguntas frequentes", vec, value = TRUE, invert = TRUE)
  
  
  for (k in 1:length(vec)) {
    Sys.sleep(1)
    
    if (!is_valid_title(vec[k])) {
      next  # Pula este título se for inválido
    }
    
    page <- page_info("pt", "wikipedia", page = vec[k])
    page_unlist <- unlist(page)
    
    if (length(page_unlist) >= 2) {
      title <- as.vector(page_unlist[length(page_unlist)])
      url <- as.vector(page_unlist[length(page_unlist)-1])
      
      # Remover itálico e HTML do título
      titulo_tratado <- str_replace_all(title, "<i>|</i>|<span.*?>|</span>", "")
      
      if (length(titulo_tratado) > 0 && length(url) > 0) {
        grafo <- data.frame(Origem = pagina_inicial, Link = url, Destino = titulo_tratado, stringsAsFactors = FALSE)
        grafo_wikipedia <- rbind(grafo_wikipedia, grafo)
      }
    }
  }
  
  return(grafo_wikipedia)
}

scrape_page_profundidade <- function(pagina_inicial, profundidade = 5) {
  grafo_wikipedia <- scrape_page(pagina_inicial)
  
  for (i in 1:profundidade) {
    novos_links <- unique(grafo_wikipedia$Destino)
    novos_grafos <- future_lapply(novos_links, function(destino) {
      scrape_page(destino)
    })
    
    grafo_wikipedia <- do.call(rbind, c(list(grafo_wikipedia), novos_grafos))
  }
  
  return(grafo_wikipedia)
}

# Salvar o resultado no arquivo .txt
resultado <- scrape_page_profundidade(pagina_inicial, profundidade = 6)
write.table(resultado, "resultado_scraping.txt", row.names = FALSE, sep = "\t", quote = FALSE)




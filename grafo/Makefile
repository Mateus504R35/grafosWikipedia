# ---- Configuração -----------------------------------------------------------
APP      := grafo_cli
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic
LDFLAGS  :=

SRC      := main.cpp grafo.cpp
OBJDIR   := build
OBJ      := $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))
DEPS     := $(OBJ:.o=.d)

# ---- Alvos padrão -----------------------------------------------------------
.PHONY: all release debug run clean dirs

all: release

release: CXXFLAGS += -O3
release: dirs $(APP)

debug: CXXFLAGS += -Og -g -DDEBUG
debug: dirs $(APP)

# ---- Linkagem ---------------------------------------------------------------
$(APP): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# ---- Compilação com geração de dependências --------------------------------
$(OBJDIR)/%.o: %.cpp grafo.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# ---- Utilidades -------------------------------------------------------------
run: $(APP)
	./$(APP)

clean:
	rm -rf $(OBJDIR) $(APP)

dirs: | $(OBJDIR)

$(OBJDIR):
	mkdir -p $@

# ---- Inclui dependências geradas -------------------------------------------
-include $(DEPS)

CC=g++
BUILD_DIR= ./build
SRC_DIR= ./
directorio_actual=$(pwd)

all: ej1 ej2 ej3 ej4 kruskal prim dijkstra
	@echo "Compilado."

.PHONY: ej1
ej1:
	mkdir -p $(BUILD_DIR)
# Si no cambio el directorio antes de compilar, el .o lo pone en la carpeta
# con los fuentes.
	cd $(BUILD_DIR)
	$(CC) $(SRC_DIR)ej1-Combustible.cpp -o $(BUILD_DIR)/$@
	cd $(directorio_actual)

.PHONY: ej2
ej2:
	mkdir -p $(BUILD_DIR)
# Si no cambio el directorio antes de compilar, el .o lo pone en la carpeta
# con los fuentes.
	cd $(BUILD_DIR)
	$(CC) $(SRC_DIR)ej2-Latencia.cpp -o $(BUILD_DIR)/$@
	cd $(directorio_actual)

.PHONY: ej3
ej3:
	mkdir -p $(BUILD_DIR)
# Si no cambio el directorio antes de compilar, el .o lo pone en la carpeta
# con los fuentes.
	cd $(BUILD_DIR)
	$(CC) $(SRC_DIR)ej3-Intervalos.cpp -o $(BUILD_DIR)/$@
	cd $(directorio_actual)

.PHONY: ej4
ej4:
	mkdir -p $(BUILD_DIR)
# Si no cambio el directorio antes de compilar, el .o lo pone en la carpeta
# con los fuentes.
	cd $(BUILD_DIR)
	$(CC) $(SRC_DIR)ej4-Cables.cpp -o $(BUILD_DIR)/$@
	cd $(directorio_actual)

.PHONY: kruskal
kruskal:
	mkdir -p $(BUILD_DIR)
# Si no cambio el directorio antes de compilar, el .o lo pone en la carpeta
# con los fuentes.
	cd $(BUILD_DIR)
	$(CC) $(SRC_DIR)ejKruskal.cpp -o $(BUILD_DIR)/$@
	cd $(directorio_actual)

.PHONY: prim
prim:
	mkdir -p $(BUILD_DIR)
# Si no cambio el directorio antes de compilar, el .o lo pone en la carpeta
# con los fuentes.
	cd $(BUILD_DIR)
	$(CC) $(SRC_DIR)ejPrim.cpp -o $(BUILD_DIR)/$@
	cd $(directorio_actual)

.PHONY: dijkstra
dijkstra:
	mkdir -p $(BUILD_DIR)
# Si no cambio el directorio antes de compilar, el .o lo pone en la carpeta
# con los fuentes.
	cd $(BUILD_DIR)
	$(CC) $(SRC_DIR)ejDijkstra.cpp -o $(BUILD_DIR)/$@
	cd $(directorio_actual)

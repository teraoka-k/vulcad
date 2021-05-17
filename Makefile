CFLAGS = -std=c++2a -O2
DIR_SHADER = ./shaders/
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SRC_DIR = ./src
BIN_DIR = ./bin

MAIN_NAME = main
MAIN_SRC = ${SRC_DIR}/${MAIN_NAME}.cc
EXE_MAIN = ${BIN_DIR}/${MAIN_NAME}

LIB_NAME = vulcad
LIB_SRC = ${SRC_DIR}/${LIB_NAME}.cc
LIB_DIR = ${BIN_DIR}/lib

build: 
	g++ $(CFLAGS) -o $(EXE_MAIN) $(MAIN_SRC) -L${LIB_DIR} -l${LIB_NAME} $(LDFLAGS) 

clean:
	rm -f $(EXE_MAIN)

lib: 
	g++ -c $(CFLAGS) ${LIB_SRC} $(LDFLAGS) 
	ar rcs ${LIB_DIR}/lib${LIB_NAME}.a ${LIB_NAME}.o
	rm ${LIB_NAME}.o
	
run: build
	clear && $(EXE_MAIN)

sh:
	glslc ${DIR_SHADER}shader.vert -o ${DIR_SHADER}vert.spv
	glslc ${DIR_SHADER}shader.frag -o ${DIR_SHADER}frag.spv

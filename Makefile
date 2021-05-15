CFLAGS = -std=c++2a -O2
EXE_NAME = ./bin/main
MAIN_FILE = ./src/main.cc
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
SHADER_DIR = ./shaders/

build: $(MAIN_FILE)
	g++ $(CFLAGS) -o $(EXE_NAME) $(MAIN_FILE) $(LDFLAGS)

clean:
	rm -f $(EXE_NAME)
	
sh:
	glslc ${SHADER_DIR}shader.vert -o ${SHADER_DIR}vert.spv
	glslc ${SHADER_DIR}shader.frag -o ${SHADER_DIR}frag.spv

run: build
	clear && $(EXE_NAME)

CFLAGS = -std=c++2a -O2
EXE_NAME = ./bin/main
MAIN_FILE = ./src/main.cc
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

build: $(MAIN_FILE)
	g++ $(CFLAGS) -o $(EXE_NAME) $(MAIN_FILE) $(LDFLAGS)

clean:
	rm -f $(EXE_NAME)

run: build
	$(EXE_NAME)

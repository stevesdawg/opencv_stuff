all:
	mkdir -p bin/
	g++ src/main.cpp -o bin/output `pkg-config --cflags --libs opencv4`

clean:
	rm -rf bin/

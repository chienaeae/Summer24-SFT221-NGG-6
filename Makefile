.PHONY: run debug build build-debug

run: build
	./Debug/main

debug: build-debug
	./Debug/main

build:
	cmake -S SourceCode -B Debug -DCMAKE_BUILD_TYPE=Release && \
	cmake --build Debug

build-debug:
	cmake -S SourceCode -B Debug -DCMAKE_BUILD_TYPE=Debug && \
	cmake --build Debug  

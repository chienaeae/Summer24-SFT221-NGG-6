run: build
	./Debug/main

build:
	cmake -S SourceCode -B Debug && \
	cmake --build Debug

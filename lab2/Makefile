.PHONY: all clean build run coverage

all: build run coverage

build:
	mkdir -p build
	cd build && cmake -DCMAKE_CXX_FLAGS="--coverage" ..
	$(MAKE) -C build

run:
	./build/run_tests

coverage:
	$(MAKE) -C build coverage
	@echo "Отчет готов в папке build/out/index.html"

clean:
	rm -rf build
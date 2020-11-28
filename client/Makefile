SHELL := /bin/bash
QMAKE = ~/Qt/5.15.1/wasm_32/bin/qmake
QMAKE_FLAGS = -spec wasm-emscripten CONFIG+=debug CONFIG+=qml_debug
GCC_QMAKE = ~/Qt/5.15.1/gcc_64/bin/qmake
GCC_QMAKE_FLAGS = -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug
PYTHON = /bin/python3
EMRUN = emsdk/upstream/emscripten/emrun.py
EMRUN_FLAGS = --browser 'firefox' --no_emrun_detect  --serve_after_close

all: emsdk/emsdk_env.sh build/index.html
	$(PYTHON) $(EMRUN) $(EMRUN_FLAGS) --port '8888' build/

emsdk/emsdk_env.sh:
	git clone https://github.com/emscripten-core/emsdk.git && cd emsdk && git pull && ./emsdk install sdk-1.39.8-64bit && ./emsdk activate sdk-1.39.8-64bit

build/index.html: emsdk/emsdk_env.sh build source/* headers/*
	source emsdk/emsdk_env.sh && cd build && $(QMAKE) .. $(QMAKE_FLAGS) && make && cp ../resource/Symulator_Wieloagentowy.html index.html

build:
	mkdir build
	
tests: generate_tests
	cd tests && ./run_tests.sh
	
generate_tests: tests/build source/* headers/*
	cd tests/build && $(GCC_QMAKE) .. $(QCC_QMAKE_FLAGS) && make
	
tests/build:
	mkdir tests/build

wasm_tests: emsdk/emsdk_env.sh tests/build_wasm/index.html source/* headers/*
	$(PYTHON) $(EMRUN) $(EMRUN_FLAGS) --port '8889' tests/build_wasm/
	
tests/build_wasm/index.html: tests/build_wasm tests/make_index_html.sh
	source emsdk/emsdk_env.sh && cd tests/build_wasm && $(QMAKE) .. && make && cd .. && ./make_index_html.sh

tests/build_wasm:
	mkdir tests/build_wasm
	
clean:
	$(RM) -r build
	$(RM) -r tests/build
	$(RM) -r tests/build_wasm


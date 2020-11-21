SHELL := /bin/bash
QMAKE = ~/Qt/5.15.1/wasm_32/bin/qmake
PYTHON = /bin/python3
EMRUN = emsdk/upstream/emscripten/emrun.py
EMRUN_FLAGS = --browser 'firefox' --no_emrun_detect  --serve_after_close

all: emsdk/emsdk_env.sh build/index.html
	$(PYTHON) $(EMRUN) $(EMRUN_FLAGS) --port '8888' build/

emsdk/emsdk_env.sh:
	git clone https://github.com/emscripten-core/emsdk.git && cd emsdk && git pull && ./emsdk install sdk-1.39.8-64bit && ./emsdk activate sdk-1.39.8-64bit

build/index.html: emsdk/emsdk_env.sh build
	source emsdk/emsdk_env.sh && cd build && $(QMAKE) .. -spec wasm-emscripten CONFIG+=debug CONFIG+=qml_debug && make && cp ../resource/Symulator_Wieloagentowy.html index.html && cp ../resource/qtloader* ./ && mv Symulator_Wieloagentowy.html index.html

build:
	mkdir build

tests: emsdk/emsdk_env.sh tests/build/index.html
	$(PYTHON) $(EMRUN) $(EMRUN_FLAGS) --port '8889' tests/build/
	
tests/build/index.html: tests/build
	source emsdk/emsdk_env.sh && cd tests/build && $(QMAKE) .. && make && cd .. && ./make_index_html.sh

tests/build:
	mkdir tests/build
	
clean:
	$(RM) -r build
	$(RM) -r tests/build


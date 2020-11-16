SHELL := /bin/bash

all: emsdk/emsdk_env.sh build build/index.html
	/bin/python3 emsdk/upstream/emscripten/emrun.py --browser 'firefox' --port '8888' --no_emrun_detect --serve_after_close build/


emsdk/emsdk_env.sh:
	git clone https://github.com/emscripten-core/emsdk.git && cd emsdk && git pull && ./emsdk install sdk-1.39.8-64bit && ./emsdk activate sdk-1.39.8-64bit


build/index.html: emsdk/emsdk_env.sh build
	source emsdk/emsdk_env.sh && cd build && ~/Qt/5.15.1/wasm_32/bin/qmake .. -spec wasm-emscripten CONFIG+=debug CONFIG+=qml_debug && make && cp ../resource/Symulator_Wieloagentowy.html index.html && cp ../resource/qtloader* ./ && mv Symulator_Wieloagentowy.html index.html

build:
	mkdir build

clean:
	rm -r build


SHELL := /bin/bash
QMAKE_FLAGS = -spec wasm-emscripten CONFIG+=debug CONFIG+=qml_debug
GCC_QMAKE_FLAGS = -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug
PYTHON = /bin/python3
EMRUN_FLAGS = --browser 'firefox' --no_emrun_detect  --serve_after_close
PWD = $(shell pwd)
SED_ARGUMENT = "s|"$(PWD)"/Qt/5.15.1/wasm_32/qml/Qt/WebSockets/libdeclarative_qmlwebsockets.a||g"
GCC_QMAKE = $(PWD)/Qt/5.15.1/gcc_64/bin/qmake
QMAKE = $(PWD)/Qt/5.15.1/wasm_32/bin/qmake
EMRUN = $(PWD)/emsdk/upstream/emscripten/emrun.py


all: emsdk/emsdk_env.sh build/index.html
	$(PYTHON) $(EMRUN) $(EMRUN_FLAGS) --port '8888' build/

emsdk/emsdk_env.sh:
	git clone https://github.com/emscripten-core/emsdk.git && cd emsdk && git pull && ./emsdk install sdk-1.39.8-64bit && ./emsdk activate sdk-1.39.8-64bit

build/index.html: emsdk/emsdk_env.sh build source/* headers/* qml/* Qt build/Makefile
	source emsdk/emsdk_env.sh && cd build && make && cp ../resource/Symulator_Wieloagentowy.html index.html
	
build/Makefile: Symulator_Wieloagentowy.pro build qml.qrc
	ource emsdk/emsdk_env.sh && cd build && $(QMAKE) .. $(QMAKE_FLAGS) && sed -i $(SED_ARGUMENT) Makefile && sed -i 's|LFLAGS        = |LFLAGS        = -s TOTAL_MEMORY=33554432 |' Makefile

run:
	$(PYTHON) $(EMRUN) $(EMRUN_FLAGS) --port '8888' build/

Qt: qt-unified-linux-x64-4.0.0-online.run
	./qt-unified-linux-x64-4.0.0-online.run install qt.qt5.5151.wasm_32 --root $(PWD)/Qt --auto-answer telemetry-question=Yes,AssociateCommonFiletypes=Yes --accept-licenses --accept-obligations --email 300198@pw.edu.pl --pw fYBaX2CvzxaSZkewmpWg --confirm-command --nd --nf

qt-unified-linux-x64-4.0.0-online.run:
	wget https://d13lb3tujbc8s0.cloudfront.net/onlineinstallers/qt-unified-linux-x64-4.0.0-online.run
	chmod +x qt-unified-linux-x64-4.0.0-online.run

build:
	mkdir build
	
tests: generate_tests
	cd tests && ./run_tests.sh
	
generate_tests: tests/build source/* headers/* qml/*
	cd tests/build && $(GCC_QMAKE) .. $(QCC_QMAKE_FLAGS) && make
	
tests/build:
	mkdir tests/build

wasm_tests: emsdk/emsdk_env.sh tests/build_wasm/index.html source/* headers/* qml/*
	$(PYTHON) $(EMRUN) $(EMRUN_FLAGS) --port '8889' tests/build_wasm/
	
tests/build_wasm/index.html: tests/build_wasm tests/make_index_html.sh
	source emsdk/emsdk_env.sh && cd tests/build_wasm && $(QMAKE) .. && make && cd .. && ./make_index_html.sh

tests/build_wasm:
	mkdir tests/build_wasm
	
clean:
	$(RM) -r build
	$(RM) -r tests/build
	$(RM) -r tests/build_wasm
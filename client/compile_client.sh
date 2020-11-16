#!/bin/sh
mkdir build
cd build
#cd client_build && 
#~/emscripten/emsdk/emsdk_env.sh
~/Qt/5.15.1/wasm_32/bin/qmake .. -spec wasm-emscripten CONFIG+=debug CONFIG+=qml_debug
make
cp ../resource/Symulator_Wieloagentowy.html index.html
cp ../resource/qtloader* ./


mv Symulator_Wieloagentowy.html index.html
/bin/python3 ../emsdk/emrun.py --browser 'firefox' --port '8888' --no_emrun_detect --serve_after_close . &

Dependencies:
sudo apt-get install build-essential libgl1-mesa-dev git python

Additional dependecies - Qt and Emscripten are automaticly downloaded with Makefile.

To make automatic compilation to WebAssembly work, please change values of QT_LOGIN_EMAIL and QT_LOGIN_PASSWORD in Makefile to your Qt account details.

Afterwards, while in directory client, type in command make.
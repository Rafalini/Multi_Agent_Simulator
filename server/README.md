Do skompilowania części serwerowej jest potrzebne narzędzie Scons, można je zainstalować za pomocą:

sudo apt-get install scons

Oraz biblioteka Boost

sudo apt-get install libboost-all-dev

Korzystamy z pythona w wersji 3.8, w razie konieczności użycia innej werji Pythona, należy zmienić stosowne linijki w plik SConstruct

Po zainstalowaniu wszystkich narzędzi należy w katalogu server uruchomić polecenie make aby skompilować aplikację. Następnie należy uruchomić poleceniem:
python3 server.py

Polecenie make test skompiluje testy jednostkowe. Uruchomić można je poleceniem make runtests

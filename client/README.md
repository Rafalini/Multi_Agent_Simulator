Instrukcja kompilacji:

Należy zainstalować następujące, wymagane pakiety:
sudo apt-get install build-essential libgl1-mesa-dev git python

następnie należy w katalogu client wykonać komendę make, pobierze one wymagane biblioteki Emscripten i Qt w odpowiednich wersjach i zainstaluje w podkatalogach katalogu client, przez co pierwsze uruchomienie może potrwać dosyć długo. Pobranie biblioteki Qt jest konieczne, gdyż zawarta w repozytoriach ubuntu wersja Qt5.12 nie zawiera prekompilowanej wersji dla WebAssembly.

Skrypt skompiluje program oraz uruchomi server http słuchający na porcie 8888 i od razu uruchomi sesję w przeglądarce firefox. W razie konieczności uruchomienia na innym porcie należy podmienić w stosownym miejscu w pliku Makefile.

W celu przetestowania za pomocą webassembly, należy użyć komendy 'make wasm_tests', która uruchomi stronę, pozwalającą obejrzeć testy jednostkowe poszczególnych klas. Test ten skorzysta z portu 8889.

W celu wygodniejszego odpalenia wszystkich testów należy wykonać komendę make tests, przetestuje ona klasy korzystając z kompilatora gcc, wymaga jednak zaznaczenia podczas pobierania qt również wersji dla kompilatora gcc. Wymaga to usunięcia flag  --nd --nf z linijki Makefile w katalogu client odpowiadającej za pobranie Qt, jednak znacząco zwiększy wielkość pobranej biblioteki
Instrukcja kompilacji:

Należy pobrać instalator Qt z poniższej strony:
https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4
pobieramy za pomocą przycisku Download wersję na platformę linux
Po pobraniu należy dodać do pliku prawa wykonywalności (chmod +x) i uruchomić skrypt
Należy się zalogować
Następnie potwierdzić przeczytanie postanowień licencyjnych i zaznaczyć, że jesteśmy osobą indywidualną oraz kliknąć "next"
Instalujemy w domyślnym katalogu, tj. /home/username/Qt
Wybieramy Custom instalation
odnaczamy wszystkie pakiety domyślne (również narzędzia pomocnicze)
zaznaczamy wyłącznie pakiet: Qt -> Qt 5.15.1 -> WebAssembly
Klikamy next (pobrane zostanie ok 1.2GB, może to potrwać chwilę)

Czekając na instalację qt, można zainstalować pozostałę wymagane pakiety:
sudo apt-get install build-essential libgl1-mesa-dev git python

następnie należy w katalogu client wykonać komendę make

skrypt skompiluje oraz uruchomi server http słuchający na porcie 8888 i od razu uruchomi sesję w przeglądarce firefox. W razie konieczności uruchomienia na innym porcie należy podmienić w stosownym miejscu w pliku Makefile.

W celu przetestowania za pomocą webassembly, należy użyć komendy 'make wasm_tests', która uruchomi stronę, pozwalającą obejrzeć testy jednostkowe poszczególnych klas. Test ten skorzysta z portu 8889.

W celu wygodniejszego odpalenia wszystkich testów należy wykonać komendę make tests, przetestuje ona klasy korzystając z kompilatora gcc, wymaga jednak zaznaczenia podczas pobierania qt również wersji dla kompilatora gcc.
#!/bin/bash
cd build_wasm
echo '<html><head><meta http-equiv="Content-Type" content="text/html; charset=utf-8"><title>Testy Jednostkowe</title></head><body><h1>Testy jednostkowe poszczególnych klas:</h1><hr><ul>' > index.html
for htmlfile in */*.html
do
	echo "<li><a href =\"$htmlfile\">${htmlfile%/*} </a></li>" >> index.html
done
echo '</ul><hr>Wyniki widoczne w konsoli</body></html>' >> index.html

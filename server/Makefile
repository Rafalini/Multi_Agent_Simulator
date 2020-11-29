server:
	mkdir -p build
	scons

run: server
	python3 server.py

clean:
	rm -r -f build
	rm -f .sconsign.dblite
	rm -f */*.so
	rm -f */*.os

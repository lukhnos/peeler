csvgen: csvgen.cpp Mandarin.o
	g++ -I../lib/OpenVanilla -I../lib/Formosana -O3 -o $@ csvgen.cpp Mandarin.o

Mandarin.o: ../lib/Formosana/Mandarin.cpp
	g++ -DMANDARIN_USE_MINIMAL_OPENVANILLA=1 -I../lib/OpenVanilla -I../lib/Formosana -O3 -c $<

clean:
	rm -f csvgen Mandarin.o

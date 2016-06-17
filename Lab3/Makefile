OCC = ocamlc
OCO = ocamlopt 

all: cons main.ml clean

.PHONY : src/%.mli
	  $(OCC) -c $<

main.ml :
	cd src; $(OCC) -c deck.mli player.mli round.mli; $(OCO) -o la_guerra_funcional deck.ml player.ml round.ml main.ml; mv la_guerra_funcional ../bin/

.PHONY : clean
clean :
	rm -f *~ *# *.byte .#*; rm -f src/*.cmx src/*.cmi src/*.o

.PHONY : cons
cons :
	mkdir bin

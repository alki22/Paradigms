JFLAGS = -g -cp src/
JC = javac
JAR = jar
JARFLAGS = cfe
DEST = -d bin/

JAVAS = \
	src/Translator.java \
	src/translator/DictTrans.java \
	src/translator/DictIgnore.java \
	src/helpers/GetOpt.java \
	src/helpers/Helpers.java \
	
BINCLASSES = \
	bin/Translator.class \
	bin/translator/DictTrans.class \
	bin/translator/DictIgnore.class \
	bin/helpers/GetOpt.class \
	bin/helpers/Helpers.class \

jar: $(BINCLASSES)
	cd bin; $(JAR) $(JARFLAGS) translator.jar Translator *

bin/Translator.class: $(JAVAS)
	mkdir -p bin; $(JC) $(JFLAGS) $(DEST) src/Translator.java

clean:
	rm -rf bin/

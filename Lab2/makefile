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

bin/Translator.class: src/Translator.java
	mkdir -p bin; $(JC) $(JFLAGS) $(DEST) src/Translator.java

bin/translator/DictTrans.class: src/translator/DictTrans.java
	mkdir -p bin; $(JC) $(JFLAGS) $(DEST) src/translator/DictTrans.java

bin/translator/DictIgnore.class: src/translator/DictIgnore.java
	mkdir -p bin; $(JC) $(JFLAGS) $(DEST) src/translator/DictIgnore.java

bin/helpers/GetOpt.class: src/helpers/GetOpt.java
	mkdir -p bin; $(JC) $(JFLAGS) $(DEST) src/helpers/GetOpt.java

bin/helpers/Helpers.class: src/helpers/Helpers.java
	mkdir -p bin; $(JC) $(JFLAGS) $(DEST) src/helpers/Helpers.java

clean:
	rm -rf bin/

JFLAGS = -g -cp src/
JC = javac
JAR = jar
JARFLAGS = cvfe
DEST = -d bin/

JAVAS = \
	src/Translator.java \
	src/translator/DictTrans.java \
	src/translator/DictIgnore.java \
	src/helpers/GetOpt.java \
	src/helpers/Helpers.java \
	
CLASSES = \
	bin/Translator.class \
	bin/translator/DictTrans.class \
	bin/translator/DictIgnore.class \
	bin/helpers/GetOpt.class \
	bin/helpers/Helpers.class \

default: $(JAVAS)
	$(JC) $(JFLAGS) $(DEST) $(JAVAS)
	
jar: $(CLASSES)
	$(JAR) $(JARFLAGS) translator.jar $(CLASSES)
	

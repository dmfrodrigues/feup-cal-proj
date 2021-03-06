PROG   =main
GROUP  =CAL1920_Turma6_G5
all: $(PROG) data

FORCE:

CC     =g++

LIB		=$(PROG)
TDIR   =./test
TEXE   =$(ODIR)/test

data: FORCE
	make -C map

clean:
	rm -rf $(ODIR)
	rm -rf $(LDIR)
	rm -f $(PROG)
	make -C resources clean

test: $(TEXE)
	$(TEXE)

$(TEXE): $(PROG) $(TDIR)/test.cpp $(LREQUIREMENTS)
	$(CC) $(CFLAGS) -I$(TDIR)/Catch2/single_include/catch2 $(TDIR)/test.cpp -o $(TEXE) $(LFLAGS)

doc/report1/report_delivery1.pdf:
	cd doc/report1 && ./compile_report1.sh

doc/report2/report_delivery2.pdf:
	cd doc/report2 && ./compile_report2.sh

# Create zip file to submit
zip: $(GROUP).zip

$(GROUP).zip: doc/report2/report_delivery2.pdf
	zip -q --symlinks $(GROUP).zip -r algorithms empirical GraphViewerCpp include map resources src structures lib test utils makefile README.md CMakeLists.txt
	zip -q $(GROUP).zip -j doc/report2/report_delivery2.pdf

DEST=~/Documents

# Test zip file to submit
testzip: $(GROUP).zip
	rm -rf $(DEST)/$(GROUP)
	mkdir -p $(DEST)/$(GROUP)
	unzip $(GROUP).zip -d $(DEST)/$(GROUP)
	mkdir $(DEST)/$(GROUP)/build
	cd $(DEST)/$(GROUP)/build && cmake ..
	cd $(DEST)/$(GROUP)/build && cmake --build .
	cd $(DEST)/$(GROUP)/build && make tests && ./tests

GROUP  =CAL1920_Turma6_G5

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

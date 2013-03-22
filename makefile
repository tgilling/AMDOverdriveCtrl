
OUTPUT_DIR = ./Release

EXECUTABLE = AMDOverdriveCtrl

SOURCES = $(wildcard ./src/*.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

DESTDIR =
PREFIX = $(DESTDIR)/usr

ifndef OPTFLAGS
       OPTFLAGS = -O3 -Wall
endif

CC = g++
CFLAGS = -c -I./ADL_SDK/include -fexpensive-optimizations -W $(shell wx-config --cxxflags --unicode=yes --debug=no) -DLINUX $(OPTFLAGS)
LDFLAGS = -s $(shell wx-config --debug=no --libs --unicode=yes) -ldl

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

all: $(SOURCES) $(OUTPUT_DIR)/$(EXECUTABLE)

$(OUTPUT_DIR)/$(EXECUTABLE): $(OBJECTS) 
	@rm -rf $(OUTPUT_DIR)
	@mkdir $(OUTPUT_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@echo ...
	@echo build completed.
	@echo ...

clean:
	@rm -rf ./src/*o
	@rm -rf $(OUTPUT_DIR)
	@echo ...
	@echo cleaning done.
	@echo ...

install: $(OUTPUT_DIR)/$(EXECUTABLE)
	@rm -f $(PREFIX)/bin/$(EXECUTABLE)
	@rm -rf $(PREFIX)/share/$(EXECUTABLE)	
	@mkdir -p $(PREFIX)/share/$(EXECUTABLE)/images
	@mkdir -p $(PREFIX)/share/doc/packages/amdovdrvctrl/
	@mkdir -p $(PREFIX)/share/applications/
	@mkdir -p $(PREFIX)/share/menu/
	@mkdir -p $(PREFIX)/share/man/man1/
	@mkdir -p $(PREFIX)/bin/
	@chmod a-x create_deb/*.png create_deb/*.xpm create_deb/AUTHORS create_deb/LICENSE
	@chmod a-x create_deb/copyright create_deb/changelog create_deb/manpage readme.txt
	@cp $(OUTPUT_DIR)/$(EXECUTABLE) $(PREFIX)/bin/ 
	@cp -pr ./create_deb/*.png $(PREFIX)/share/$(EXECUTABLE)/images/
	@cp -pr ./create_deb/*.xpm $(PREFIX)/share/$(EXECUTABLE)/images/
	@cp -pr ./create_deb/AUTHORS $(PREFIX)/share/doc/packages/amdovdrvctrl/
	@cp -pr ./create_deb/LICENSE $(PREFIX)/share/doc/packages/amdovdrvctrl/
	@cp -pr ./create_deb/copyright $(PREFIX)/share/doc/packages/amdovdrvctrl/
	@cp -pr ./readme.txt $(PREFIX)/share/doc/packages/amdovdrvctrl/
	@gzip -c -9 ./create_deb/changelog > $(PREFIX)/share/doc/packages/amdovdrvctrl/changelog.gz
	@gzip -c -9 ./create_deb/manpage > $(PREFIX)/share/man/man1/$(EXECUTABLE).1.gz
	@rm -rf $(PREFIX)/share/applications/$(EXECUTABLE).desktop
	@cp -rf create_deb/$(EXECUTABLE).desktop $(PREFIX)/share/applications/$(EXECUTABLE).desktop
	@chmod a+x $(PREFIX)/share/applications/$(EXECUTABLE).desktop
	@echo ...
	@echo $(EXECUTABLE) installed.
	@echo ...

uninstall:
	@rm -f $(PREFIX)/bin/$(EXECUTABLE)
	@rm -rf $(PREFIX)/share/$(EXECUTABLE)
	@rm -rf $(PREFIX)/share/doc/amdoverdrivectrl
	@rm -f $(PREFIX)/share/man/man1/amdoverdrivectrl.1.gz
	@rm -rf $(PREFIX)/share/applications/$(EXECUTABLE).desktop	
	@echo ...
	@echo $(EXECUTABLE) uninstalled.
	@echo ...

dist:
	@rm -f ./temp.tar.bz2
	@rm -rf ./AMDOverdriveCtrl
	@mkdir ./AMDOverdriveCtrl
	@mkdir ./AMDOverdriveCtrl/src
	@mkdir ./AMDOverdriveCtrl/create_deb
	@mkdir ./AMDOverdriveCtrl/documentation
	@mkdir ./AMDOverdriveCtrl/screenshots
	@mkdir ./AMDOverdriveCtrl/scripts
	@mkdir ./AMDOverdriveCtrl/ADL_SDK
	@echo 'Please insert AMD ADL files here. (http://developer.amd.com/gpu/adlsdk/Pages/default.aspx)' > ./AMDOverdriveCtrl/ADL_SDK/readme.txt
	@cp ./makefile ./AMDOverdriveCtrl
	@cp ./configure ./AMDOverdriveCtrl
	@cp ./*.workspace ./AMDOverdriveCtrl
	@cp ./*.project ./AMDOverdriveCtrl
	@cp ./*.txt ./AMDOverdriveCtrl
	@cp ./*.sh ./AMDOverdriveCtrl
	@cp ./bin2h ./AMDOverdriveCtrl
	@cp -r ./src/* ./AMDOverdriveCtrl/src
	@cp -r ./create_deb/* ./AMDOverdriveCtrl/create_deb
	@cp -r ./documentation/* ./AMDOverdriveCtrl/documentation
	@cp -r ./screenshots/* ./AMDOverdriveCtrl/screenshots
	@tar cfj ./temp.tar.bz2 ./AMDOverdriveCtrl/*
	@rm -rf ./AMDOverdriveCtrl
	@sh ./rename_bz2.sh temp AMDOverdriveCtrl

dist_adl:
	@rm -f ./temp.tar.bz2
	@rm -rf ./AMDOverdriveCtrl
	@mkdir ./AMDOverdriveCtrl
	@mkdir ./AMDOverdriveCtrl/src
	@mkdir ./AMDOverdriveCtrl/create_deb
	@mkdir ./AMDOverdriveCtrl/documentation
	@mkdir ./AMDOverdriveCtrl/screenshots
	@mkdir ./AMDOverdriveCtrl/scripts
	@mkdir ./AMDOverdriveCtrl/ADL_SDK
	@cp ./makefile ./AMDOverdriveCtrl
	@cp ./configure ./AMDOverdriveCtrl
	@cp ./*.workspace ./AMDOverdriveCtrl
	@cp ./*.project ./AMDOverdriveCtrl
	@cp ./*.txt ./AMDOverdriveCtrl
	@cp ./*.sh ./AMDOverdriveCtrl
	@cp ./bin2h ./AMDOverdriveCtrl
	@cp -r ./src/* ./AMDOverdriveCtrl/src
	@cp -r ./create_deb/* ./AMDOverdriveCtrl/create_deb
	@cp -r ./documentation/* ./AMDOverdriveCtrl/documentation
	@cp -r ./screenshots/* ./AMDOverdriveCtrl/screenshots
	@cp -r ./ADL_SDK/* ./AMDOverdriveCtrl/ADL_SDK
	@tar cfj ./temp.tar.bz2 ./AMDOverdriveCtrl/*
	@rm -rf ./AMDOverdriveCtrl
	@sh ./rename_bz2.sh temp AMDOverdriveCtrl_ADL

deb:
	@sh ./make_deb.sh
	





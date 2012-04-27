
OUTPUT_DIR = ./Release

EXECUTABLE = AMDOverdriveCtrl

SOURCES = $(wildcard ./src/*.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

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
	@rm -f /usr/bin/$(EXECUTABLE)
	@rm -rf /usr/share/$(EXECUTABLE)
	@cp $(OUTPUT_DIR)/$(EXECUTABLE) /usr/bin/
	@mkdir -p /usr/share/$(EXECUTABLE)/images
	@mkdir -p /usr/share/doc/amdoverdrivectrl/
	@mkdir -p /usr/share/applications/
	@mkdir -p /usr/share/menu/
	@cp -pr ./create_deb/*.png /usr/share/$(EXECUTABLE)/images/
	@cp -pr ./create_deb/*.xpm /usr/share/$(EXECUTABLE)/images/
	@cp -pr ./create_deb/AUTHORS /usr/share/$(EXECUTABLE)/
	@cp -pr ./create_deb/LICENSE /usr/share/$(EXECUTABLE)/
	@cp -pr ./create_deb/copyright /usr/share/doc/amdoverdrivectrl/copyright
	@gzip -c -9 ./create_deb/changelog > /usr/share/doc/amdoverdrivectrl/changelog.gz
	@gzip -c -9 ./create_deb/manpage > /usr/share/man/man1/amdoverdrivectrl.1.gz
	@rm -rf /usr/share/applications/$(EXECUTABLE).desktop
	@cp -rf create_deb/$(EXECUTABLE).desktop /usr/share/applications/$(EXECUTABLE).desktop
	@chmod a+x /usr/share/applications/$(EXECUTABLE).desktop
	@echo ...
	@echo $(EXECUTABLE) installed.
	@echo ...

uninstall:
	@rm -f /usr/bin/$(EXECUTABLE)
	@rm -rf /usr/share/$(EXECUTABLE)
	@rm -rf /usr/share/doc/amdoverdrivectrl
	@rm -f /usr/share/man/man1/amdoverdrivectrl.1.gz
	@rm -rf /usr/share/applications/$(EXECUTABLE).desktop
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
	





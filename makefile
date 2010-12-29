
OUTPUT_DIR=./Release

EXECUTABLE=AMDOverdriveCtrl

SOURCES=$(wildcard *.cpp)

OBJECTS=$(SOURCES:.cpp=.o) ./adl/adl.o

CC=g++
CFLAGS=-c -I./ADL_SDK/include -O3 -fexpensive-optimizations -W -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DLINUX -D__WX__
LDFLAGS=-mwindows -s $(shell wx-config --debug=no --libs --unicode=yes) -ldl -o$(EXECUTABLE)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	@rm -rf $(OUTPUT_DIR)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@mkdir $(OUTPUT_DIR)
	@cp $(EXECUTABLE) $(OUTPUT_DIR)/$(EXECUTABLE)
	@echo ----------------
	@echo build completed.
	@echo ----------------

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf *o
	@rm -f ./adl/adl.o
	@rm -rf $(OUTPUT_DIR)
	@rm -f $(EXECUTABLE)
	@echo --------------
	@echo cleaning done.
	@echo --------------

install:
	@rm -f /usr/bin/$(EXECUTABLE)
	@rm -rf /usr/share/$(EXECUTABLE)
	@cp $(OUTPUT_DIR)/$(EXECUTABLE) /usr/bin/
	@mkdir -p /usr/share/AMDOverdriveCtrl/images
	@mkdir -p /usr/share/applications/
	@mkdir -p /usr/share/menu/
	@cp -pr ./create_deb/*.png /usr/share/AMDOverdriveCtrl/images/
	@cp -pr ./create_deb/AUTHORS /usr/share/AMDOverdriveCtrl/
	@cp -pr ./create_deb/LICENSE /usr/share/AMDOverdriveCtrl/
	@rm -rf /usr/share/applications/AMDOverdriveCtrl.desktop
	@cp -rf create_deb/AMDOverdriveCtrl.desktop /usr/share/applications/AMDOverdriveCtrl.desktop
	@chmod a+x /usr/share/applications/AMDOverdriveCtrl.desktop
	@echo ---------------------------
	@echo AMDOverdriveCtrl installed.
	@echo ---------------------------

uninstall:
	@rm -f /usr/bin/$(EXECUTABLE)
	@rm -rf /usr/share/$(EXECUTABLE)
	@rm -rf /usr/share/applications/AMDOverdriveCtrl.desktop
	@echo -----------------------------
	@echo AMDOverdriveCtrl uninstalled.
	@echo -----------------------------

	




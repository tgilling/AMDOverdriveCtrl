
OUTPUT_DIR = ./Release

EXECUTABLE = AMDOverdriveCtrl

SOURCES = $(wildcard ./src/*.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

CC = g++
CFLAGS = -c -I./ADL_SDK/include -O3 -fexpensive-optimizations -W -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DLINUX
LDFLAGS = -mwindows -s $(shell wx-config --debug=no --libs --unicode=yes) -ldl -o$(OUTPUT_DIR)/$(EXECUTABLE)

all: $(SOURCES) $(OUTPUT_DIR)/$(EXECUTABLE)

$(OUTPUT_DIR)/$(EXECUTABLE): $(OBJECTS) 
	@rm -rf $(OUTPUT_DIR)
	@mkdir $(OUTPUT_DIR)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@echo ----------------
	@echo build completed.
	@echo ----------------

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf ./src/*o
	@rm -rf $(OUTPUT_DIR)
	@echo --------------
	@echo cleaning done.
	@echo --------------

install:
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
	@echo ---------------------------
	@echo $(EXECUTABLE) installed.
	@echo ---------------------------

uninstall:
	@rm -f /usr/bin/$(EXECUTABLE)
	@rm -rf /usr/share/$(EXECUTABLE)
	@rm -rf /usr/share/doc/amdoverdrivectrl
	@rm -f /usr/share/man/man1/amdoverdrivectrl.1.gz
	@rm -rf /usr/share/applications/$(EXECUTABLE).desktop
	@echo -----------------------------
	@echo $(EXECUTABLE) uninstalled.
	@echo -----------------------------

	




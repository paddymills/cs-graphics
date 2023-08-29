// see https://makefiletutorial.com/

CXXFLAGS = -I"$(CURDIR)/include"
LOADLIBES = -L"$(CURDIR)/lib"
LDLIBS = 

BUILD_DIR := $(CURDIR)/build
SRC_DIR := $(CURDIR)/src

ifeq ($(OS),Windows_NT)
    LDLIBS = -lfreeglut -lopengl32 -lGlu32 -W"l,--subsystem,windows"
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LDLIBS = -lglut -lGL -lGLU
    endif
endif


build_dir:
ifeq (,$(wildcard $(BUILD_DIR)))
	mkdir $(BUILD_DIR)
endif

compile: build_dir $(SRC_DIR)/main.cpp

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@


main.exe: $(BUILD_DIR)/main.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $(BUILD_DIR)/$@

main: main.exe

run:
	$(BUILD_DIR)/main.exe

clean:
ifneq (,$(wildcard $(BUILD_DIR)/*))
	rm -r $(BUILD_DIR)/*
endif

all: clean main run
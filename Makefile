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

init: ../build
../build:
	mkdir $(BUILD_DIR)

$(SRC_DIR)/%.c:
	echo $@ not found

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c*
	$(CXX) -c $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

main: $(BUILD_DIR)/main
hello: $(BUILD_DIR)/hello

run: main
	$(BUILD_DIR)/main


clean:
ifneq (,$(wildcard $(BUILD_DIR)/*))
	rm -r $(BUILD_DIR)/*
endif

all: main run
// see https://makefiletutorial.com/

CXXFLAGS = -I"$(CURDIR)/include"
LOADLIBES = -L"$(CURDIR)/lib"
LDLIBS = -lfreeglut -lopengl32 -lGlu32 -W"l,--subsystem,windows"

BUILD_DIR := $(CURDIR)/build
SRC_DIR := $(CURDIR)/src

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
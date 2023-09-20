
CXXFLAGS = -I"$(CURDIR)/include"
LDLIBS = -L"$(CURDIR)/lib"
LOADLIBES =

ifeq ($(OS),Windows_NT)
    LOADLIBES += -lfreeglut -lopengl32 -lGlu32 -W"l,--subsystem,windows" -lglew32
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LOADLIBES += -lglut -lGL -lGLU -lGLEW
    endif
endif

SRCDIR := src
OBJDIR := build

SRCS := $(wildcard $(SRCDIR)/*.c $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o, $(SRCS))
OBJS += $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o, $(SRCS))
BINS := $(patsubst $(OBJDIR)/%.o,$(OBJDIR)/%, $(OBJS))

# create build directory if it doesn't exist
$(OBJDIR):
	@echo "Creating build directory"
	mkdir "$(OBJDIR)"

# source code compiling
$(OBJDIR)/%.o : $(SRCDIR)/%.c* | $(OBJDIR)
	@echo "compiling: ($@) from ($^)"
	$(CXX) -c $(CXXFLAGS) $^ -o $@

# binary linking
$(OBJDIR)/%.exe: $(OBJDIR)/%
$(OBJDIR)/%: $(OBJDIR)/%.o
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) $(LOADLIBES) -o $@

# compile all binaries
all: $(BINS)
	@echo "binaries created: $^"

.PHONY: clean
clean:
ifneq (,$(wildcard $(BUILD_DIR)/*))
	@echo "cleaning build directory"
	rm -r $(OBJDIR)/*
endif

# catch-all for launching a binary not explicity listed
%: $(OBJDIR)/%
	$(OBJDIR)/$@

GENERATED_SOURCES=src/ice/parser/_parser.cc src/ice/parser/_scanner.cc
GENERATED_HEADERS=src/ice/parser/_parser.hh
SOURCES=$(filter-out $(GENERATED_SOURCES), \
		$(wildcard src/ice/*.cc \
				   src/ice/parser/*.cc \
				   src/ice/ast/*.cc \
				   src/ice/codegen/*.cc))

OBJECTS=$(patsubst %.cc,%.o,$(SOURCES) $(GENERATED_SOURCES))
CXXFLAGS=-Wall -O0 -g -Iinclude -Isrc
LDFLAGS=
BINARY=ice
BISON=bison
FLEX=flex

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cc
	$(CXX) -o $@ $(CXXFLAGS) -c $<

src/ice/parser/_parser.cc: src/ice/parser/_parser.yy
	$(BISON) -o $@ -d $<

src/ice/parser/_parser.hh: src/ice/parser/_parser.cc

src/ice/parser/_scanner.ll: src/ice/parser/_parser.hh

src/ice/parser/_scanner.cc: src/ice/parser/_scanner.ll
	$(FLEX) -o $@ $<

clean:
	- rm -f $(BINARY)
	- find . -name '*.o' -exec rm -f {} \;
	- rm -f $(GENERATED_SOURCES) $(GENERATED_HEADERS)

.PHONY: clean all


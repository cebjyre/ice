GENERATED_SOURCES=parser.cc scanner.cc
GENERATED_HEADERS=parser.hh
SOURCES=$(filter-out $(GENERATED_SOURCES),$(wildcard *.cc))
OBJECTS=$(patsubst %.cc,%.o,$(SOURCES) $(GENERATED_SOURCES))
CXXFLAGS=-Wall -O0 -g -Iinclude
LDFLAGS=
BINARY=ice
BISON=bison
FLEX=flex

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cc
	$(CXX) -o $@ $(CXXFLAGS) -c $<

parser.cc: parser.yy
	$(BISON) -o $@ -d $<

parser.hh: parser.cc

scanner.l: parser.hh

scanner.cc: scanner.l
	$(FLEX) -o $@ $<

clean:
	- rm -f $(BINARY)
	- find . -name '*.o' -exec rm -f {} \;
	- rm -f $(GENERATED_SOURCES) $(GENERATED_HEADERS)

.PHONY: clean all


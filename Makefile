INCLUDES = /usr/include/node
CXX_FLAGS = -g -Wall -fPIC -DPIC -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -I$(INCLUDES) -D_WITH_NODE

NODE_TARGET = node_modules/cl.node
NODE_GLUE = src/node/node_glue.cpp

INPUTS = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,build/%.o,$(INPUTS))
NODE_GLUE_OBJECTS = $(patsubst src/%.cpp,build/%.o,$(NODE_GLUE))


TESTS = $(wildcard tests/*.js)
TESTS_OUTPUTS = $(patsubst tests/%.js,build/%.txt,$(TESTS))

.PHONY: node_tests all

all: $(NODE_TARGET) node_tests
	node tests/axpy.js


$(NODE_TARGET): $(OBJECTS) $(NODE_GLUE_OBJECTS)
	@mkdir -p $(dir $(NODE_TARGET))
	g++ $^ -o $@ -shared -L/usr/lib

node_tests: $(TESTS_OUTPUTS)

#$(TESTS_OUTPUTS) : $(NODE_TARGET)

build/%.txt : tests/%.js #src/%.cpp
	@echo #node $<
#| tee $@

build/%.o : src/%.cpp
	@mkdir -p $(dir $@)
	g++ $(CXX_FLAGS) $< -c -o $@

clean:
	rm -rf node_modules build

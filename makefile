SOURCES=$(shell find . -name "*.cpp")
OBJECTS=$(SOURCES:%.cpp=%.o)
TARGET=foo

.PHONY: all
all: old $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS)  -o $@ -lboost_filesystem -lboost_system

.PHONY: clean

old:
	rm -f foo

clean:
	rm -f $(TARGET) $(OBJECTS)

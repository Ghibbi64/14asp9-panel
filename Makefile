TARGET := 14asp9-panel

SRCS := main.cpp $(wildcard src/*.cpp src/*/*.cpp)
OBJS := $(SRCS:%.cpp=build/%.o)
DEPS := $(OBJS:.o=.d)

CXXFLAGS ?= -O2 -Wall
CXXFLAGS += -Iinclude -MMD -MP

.DEFAULT_GOAL := all

.PHONY: all clean
all: $(TARGET)
	@echo Target $(TARGET) build finished.

$(TARGET): $(OBJS)
	@echo "  LD  $@"
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "  CXX $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(DEPS) $(TARGET)
	@echo Cleaned.

-include $(DEPS)
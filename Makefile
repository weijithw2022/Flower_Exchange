CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 \
	-I./src/app -I./src/domain -I./src/validation -I./src/interfaces -I./src/io -I./src/services
TARGET := ExchangeAppMain

SRCS := src/main.cpp \
	src/domain/InputOrder.cpp \
	src/domain/OrderBook.cpp \
	src/services/OrderIDGenerator.cpp \
	src/app/OrderProcessor.cpp \
	src/app/FileCleanupService.cpp \
	src/validation/OrderValidator.cpp \
	src/io/ReadInputOrderCSV.cpp \
	src/io/GenerateCSV.cpp
OBJS := $(SRCS:.cpp=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET := ExchangeApp

SRCS := ExchangeApp.cpp InputOrder.cpp OrderBook.cpp OrderIDGenerator.cpp
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

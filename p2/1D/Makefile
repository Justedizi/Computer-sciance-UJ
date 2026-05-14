CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = test

all: $(TARGET)

$(TARGET): Sum.cpp Mult.cpp Operation.cpp main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) Sum.cpp Mult.cpp Operation.cpp main.cpp

clean:
	rm -f $(TARGET)

zip: clean
	zip ../1D.zip Sum.cpp Mult.cpp Operation.cpp

.PHONY: all clean zip

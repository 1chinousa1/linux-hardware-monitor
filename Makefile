CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = hw_monitor

all: $(TARGET)

$(TARGET): main.cpp
	g++ -Wall -std=c++11 main.cpp -o hw_monitor

clean:
	rm -f hw_monitor
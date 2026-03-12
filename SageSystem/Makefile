CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET   = sage
SRC      = main.cpp

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC) classes/*.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@echo "Build successful → ./$(TARGET)"

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

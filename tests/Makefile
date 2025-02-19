CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic
LDFLAGS = -pthread  # Needed for Google Test

GTEST_DIR = /usr/local/include/gtest  # System-wide installation path
GTEST_LIBS = -lgtest -lgtest_main

TARGET = test
SOURCES =  test.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(GTEST_LIBS) -o $(TARGET) $(OBJECTS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

format:
	astyle -A1 -s4 *.cpp *.hpp





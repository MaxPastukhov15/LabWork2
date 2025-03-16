CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic
LDFLAGS = -pthread  # Required for Google Test

# Google Test installation paths
GTEST_LIB = /usr/local/lib
GTEST_INCLUDE = /usr/local/include

# Source files and include directory
SRCS = ../src/test.cpp ../src/Characters.cpp ../src/Game.cpp ../src/Location.cpp ../src/Quests.cpp ../src/Thing.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = test_runner

# Include directory for the src folder
INCLUDE_DIR = ../src

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE) -I$(INCLUDE_DIR) $^ -o $@ -L$(GTEST_LIB) -lgtest -lgtest_main $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE) -I$(INCLUDE_DIR) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

format:
	astyle -A1 -s4 ../src/*.cpp ../src/*.hpp

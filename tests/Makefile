CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic
LDFLAGS = -pthread  # Required for Google Test

# Google Test installation paths
GTEST_LIB = /usr/local/lib
GTEST_INCLUDE = /usr/local/include

# Source files and include directories
SRCS = ../src/Characters.cpp ../src/Game.cpp ../src/Location.cpp ../src/Quests.cpp ../src/Thing.cpp test.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = test_runner

# Include directories (add all possible header locations)
INCLUDE_DIRS = -I../src -I../include

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -I$(GTEST_INCLUDE) $^ -o $@ -L$(GTEST_LIB) -lgtest -lgtest_main $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -I$(GTEST_INCLUDE) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

format:
	astyle -A1 -s4 ../src/*.cpp ../src/*.hpp

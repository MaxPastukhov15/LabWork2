CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic -Iinclude
TARGET = run_game

# List all source files 
SOURCES = src/main.cpp src/Characters.cpp src/Game.cpp \
          src/Location.cpp src/Quests.cpp src/Thing.cpp

# Generate object files in current directory
OBJECTS = $(notdir $(SOURCES:.cpp=.o))

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# Pattern rule to compile from src/ to current dir
%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

format:
	astyle -A1 -s4 src/*.cpp include/*.hpp

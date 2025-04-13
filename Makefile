CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic -Iinclude
TARGET = run_game

SOURCES = src/main.cpp src/Characters.cpp src/Game.cpp \
          src/Location.cpp src/Quests.cpp src/Thing.cpp

OBJECTS = $(notdir $(SOURCES:.cpp=.o))

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

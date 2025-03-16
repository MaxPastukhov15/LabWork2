CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic 
TARGET = run_game
SOURCES = main.cpp   Characters.cpp Game.cpp Location.cpp Quests.cpp Thing.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

format:
	astyle -A1 -s4 *.cpp *.hpp

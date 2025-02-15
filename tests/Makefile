
CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic 

SRCDIR = src
TESTDIR = tests
BUILDDIR = build

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
TESTFILES = $(wildcard $(TESTDIR)/*.cpp)
OBJFILES = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCFILES))


GTEST_DIR = tests/googletest
GTEST_LIB = $(BUILDDIR)/gtest_main.a

TARGET = $(BUILDDIR)/MyGame
TEST_TARGET = $(BUILDDIR)/runTests

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TESTFILES) $(GTEST_LIB) $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ -pthread


$(GTEST_LIB):
	cd $(GTEST_DIR) && cmake . && make
	cp $(GTEST_DIR)/lib/libgtest_main.a $(BUILDDIR)/


$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Очистка
clean:
	rm -rf $(BUILDDIR)/*.o $(TARGET) $(TEST_TARGET)


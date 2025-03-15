CXX = g++
EXEC = SO2-Projekt
SRC = main.cpp
CXXFLAGS = -pthread
all: $(EXEC)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

clean:
	rm -f $(EXEC)

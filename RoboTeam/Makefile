CXX = g++
CXXFLAGS = -ansi -Wall -pipe
BIN = test
SOURCES = ExtPlayer.cpp MyPoint.cpp PlayerAction.cpp PlayerState.cpp Scenario.cpp WorldInfo.cpp RoboTeam.cpp
LDFLAGS = $(CXXFLAGS) -Wl,-O1
OBJS = $(notdir $(SOURCES:.cpp=.o))

all: $(OBJS)
	$(CXX) $(OBJS) -o $(BIN) $(LDFLAGS)

.PHONY: clean
clean:
	@rm -fr $(OBJS) $(BIN)


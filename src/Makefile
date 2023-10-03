CXX=g++
CXXFLAGS=-std=c++14 -MMD -g
OBJECTS=subject.o observer.o game.o card.o gamestate.o deck.o player.o computer.o concretestrategyA.o concretestrategyB.o controller.o view.o main.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=straights

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = bb7k
OBJECTS = main.o Human.o Player.o Computer.o Computer1.o RegularMode.o TestingMode.o Mode.o board.o cell.o building.o academic.o slc.o iraNeedles.o cup.o tuition.o
DEPENDS = ${OBJECTS:.o=.d} 

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

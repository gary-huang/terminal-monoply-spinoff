CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = bb7k
OBJECTS = main.o controller.o player.o gameboard.o die.o monopolytile.o renttile.o collectOSAP.o tile.o propertytile.o nonpropertytile.o cups.o dctimsline.o goosenesting.o gototims.o tuition.o coopfee.o slc.o needleshall.o view.o textview.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

CXX = u++										# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -DIMPLTYPE_${TYPE}
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

# object files forming 1st executable with prefix "q1"
OBJECTS = student.o vendingMachine.o printer.o nameServer.o main.o config.o bottlingPlant.o truck.o watCard.o watCardOffice.o bank.o
DEPENDS = ${OBJECTS:.o=.d}						# substitute ".o" with ".d"
EXEC = soda

.PHONY : clean

all : ${EXEC} 									# build all executables

${EXEC} : ${OBJECTS}
	${CXX} $^ -o $@

${OBJECTS} : ${MAKEFILE_NAME}					# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}

clean :											# remove files that can be regenerated
	rm -f *.d *.o ${EXEC}

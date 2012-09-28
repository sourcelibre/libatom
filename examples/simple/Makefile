DEPS=atom-0.1 liblo
CXXFLAGS=`pkg-config --cflags $(DEPS)` -g -Wall -Werror -Wfatal-errors -Wextra
LIBS=`pkg-config --libs $(DEPS)`
OBJS=main.o

all: run

%.o : %.cpp %.h
	$(CC) -c  $< -o $@ $(CXXFLAGS)

run: $(OBJS)
	g++  $^ -o $@ -Wall -g $(LIBS)

.PHONY: clean

clean:
	rm -f run *.o


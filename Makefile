CC = g++
TARGET = build/bin/main
FILENAMES = dft wavio main
SRCS = $(addprefix src/,$(addsuffix .cpp,$(FILENAMES)))
OBJS = $(addprefix build/obj/,$(addsuffix .o,$(FILENAMES)))
INCDIR = -I./include
LIBS = -lm

$(TARGET): $(OBJS)
	mkdir -p build/bin
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

build/obj/%.o: src/%.cpp
	mkdir -p build/obj
	$(CC) $(INCDIR) -c $< -o $@

clean:
	rm -r build

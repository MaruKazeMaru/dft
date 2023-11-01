CC = g++
TARGETNAMES = create_time_graph
TARGETS = $(addprefix build/bin/, $(TARGETNAMES))
FILENAMES = dft iwav opng linegraph $(TARGETNAMES)
SRCS = $(addprefix src/,$(addsuffix .cpp,$(FILENAMES)))
OBJS = $(addprefix build/obj/,$(addsuffix .o,$(FILENAMES)))
INCDIR = -I./include
LIBS = -lm -lpng

$(TARGETS): $(OBJS)
	mkdir -p build/bin
	$(CC) $(OBJS) $(LIBS) -o $(TARGETS)

build/obj/%.o: src/%.cpp
	mkdir -p build/obj
	$(CC) $(INCDIR) -c $< -o $@

clean:
	rm -r build

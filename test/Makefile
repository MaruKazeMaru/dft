CC = g++
TARGETNAME =
FILENAMES = $(TARGETNAME) $(TARGETNAME)_test
SRCS = $(addprefix ../src/,$(addsuffix .cpp,$(FILENAMES)))
OBJS = $(addprefix ../build/obj/,$(addsuffix .o,$(FILENAMES)))
INCDIR = -I../include
LIBS = -lm

$(TARGETNAME): $(OBJS)
	mkdir -p bin
	$(CC) $(OBJS) $(LIBS) -o ./bin/$(TARGETNAME)

../build/obj/%.o: ../src/%.cpp
	mkdir -p ../build/obj
	$(CC) $(INCDIR) -c $< -o $@

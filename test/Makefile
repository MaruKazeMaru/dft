CC = g++
OBJDIR = ../build/obj
SRCDIR = ../src
INCDIR = -I../include

opng: $(OBJDIR)/opng.o $(OBJDIR)/opng_test.o
	mkdir -p bin
	$(CC) $^ -lpng -o ./bin/$@

dft: $(OBJDIR)/dft.o $(OBJDIR)/dft_test.o
	mkdir -p bin
	$(CC) $^ -lm -o ./bin/$@

wavio: $(OBJDIR)/wavio.o $(OBJDIR)/wavio_test.o
	mkdir -p bin
	$(CC) $^ -o ./bin/$@

../build/obj/%.o: ../src/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(INCDIR) -c $< -o $@

clean:
	rm -r bin

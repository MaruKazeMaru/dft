CC = g++

SRCDIR = src
OBJDIR = build/obj
BINDIR = build/bin

TARGETNAME1 = create_info
TARGET1 = $(BINDIR)/$(TARGETNAME1)
OBJNAMES1 = iwav $(TARGETNAME1)
OBJS1 = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(OBJNAMES1)))

TARGETNAME2 = create_time_graph
TARGET2 = $(BINDIR)/$(TARGETNAME2)
OBJNAMES2 = iwav linegraph $(TARGETNAME2)
OBJS2 = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(OBJNAMES2)))

TARGETNAME3 = create_spectrogram
TARGET3 = $(BINDIR)/$(TARGETNAME3)
OBJNAMES3 = iwav opng heatmap dft $(TARGETNAME3)
OBJS3 = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(OBJNAMES3)))

INCDIR = -I./include

all: t1 t2 t3

t1: $(TARGET1)
t2: $(TARGET2)
t3: $(TARGET3)

$(TARGET1): $(OBJS1)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@

$(TARGET2): $(OBJS2)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@

$(TARGET3): $(OBJS3)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@  -lm -lpng

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(INCDIR) -c $< -o $@

clean:
	rm -r build

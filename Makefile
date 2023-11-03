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

INCDIR = -I./include

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJS1)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@

$(TARGET2): $(OBJS2)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(INCDIR) -c $< -o $@

clean:
	rm -r build

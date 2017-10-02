.DEFAULT_GOAL := all
# ==========================  CONST MACROS  ====================================
CC = g++
RES = windres
OBJDIR = obj
BINDIR = bin
SRCDIR = src
DEPDIR = dep

# ============================  LIBS  ==========================================
LIBI = -IC:\Dev
LIBL = -LC:\Dev\lib

#-lglfw3 -lgdi32 -lopengl32


LIBL += -lglfw3
LIBL += -lgdi32
LIBL += -lglad

# ==============================  Other  ======================================
SRCS = $(wildcard $(SRCDIR)/*.cpp)
# SRCS = $(patsubst %    , $(SRCDIR)/%  , $(_SRC))
OBJS = $(patsubst %, $(OBJDIR)/%.o, $(basename $(notdir $(SRCS))))
DEPS = $(patsubst %, $(DEPDIR)/%.d, $(basename $(notdir $(SRCS))))

CFLAGS = $(DEBUG) -std=c++17 -c
LFLAGS = $(DEBUG)

EXE = debug.exe

# ============================ RECEPIES ========================================

$(DEPDIR)/%.d: $(SRCDIR)/%.cpp 
	$(CC) -MM -MF $@ $< -MT $(patsubst %, $(OBJDIR)/%.o, $(basename $(notdir $<)))
	
-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPDIR)/%.d
	$(CC) $< -o $@ $(CFLAGS) $(LIBI)

$(OBJDIR)/res.o: ./res.rc ./info.h
	$(RES) $<  $@
	
# Link	
.PHONY: debug
debug: DEBUG = -Og -g
debug: $(OBJS)
	@echo $(SRCS)
	$(CC) ./$^ -o $(BINDIR)/$(EXE) $(LFLAGS) $(LIBL)

# Link	
$(BINDIR)/main: $(OBJ)
	$(CC) $^ -o $@ $(LFLAGS) $(L_SDLLM)

# ============================= PHONY RECEPIES =================================
.PHONY: all
all: clean $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) $(L_SDLL) -o $(BINDIR)/final.exe

.PHONY: install
install: DEBUG = -O3 -s -DNDEBUG
install: GRAPHICS = -w -Wl,-subsystem,windows
install: all Runner.cpp $(OBJDIR)/res.o
	$(CC) ./Runner.cpp $(OBJDIR)/res.o -static -o Play_GinRummy.exe
	Play_GinRummy.exe
	
.PHONY: clean
clean:
	del .\*.exe
	del .\obj\*.o
	del .\bin\*.exe
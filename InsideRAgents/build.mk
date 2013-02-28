CXX = g++
CXXFLAGS = -pthread -ansi -Wall -pipe
LD = $(CXX)
LDFLAGS = $(CXXFLAGS) -Wl,-O1
STRIP = strip

ifeq ($(BINDIR),)
    BINDIR = bin
endif
ifeq ($(OBJDIR),)
    OBJDIR = obj
endif
ifeq ($(DEPDIR),)
    DEPDIR = .deps
endif

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPS = $(addprefix $(DEPDIR)/, $(notdir $(SOURCES:.cpp=.d)))
CXXFLAGS += $(INCLUDEPATH:%=-I%) $(DEFINES:%=-D%)
LDFLAGS += $(LIBPATH:%=-L%) $(LIBS:%=-l%)
VPATH = $(sort $(dir $(SOURCES)))

.PHONY: all clean distclean prepare

all: prepare $(BINDIR)/$(TARGET)

clean:
	@rm -f $(OBJS) $(DEPS)

distclean:
	@rm -rf $(BINDIR) $(OBJDIR) $(DEPDIR)

prepare:
	@test -d $(BINDIR) || mkdir $(BINDIR)
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@test -d $(DEPDIR) || mkdir $(DEPDIR)

$(BINDIR)/$(TARGET): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@
	@$(STRIP) $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MD -MF $(DEPDIR)/$(notdir $(@:.o=.d)) -c -o $@ $<

-include $(DEPS)

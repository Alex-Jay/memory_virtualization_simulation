# Global Variables
CC			= gcc
CFLAGS	= -c #-Wall
LIBDIR	= lib
DISTDIR	= dist
OBJECTS	= dist/main.o\
		  		dist/utils.o\

# Use incremental build as default target
default: link

link: $(OBJECTS)
	$(CC) $? -o $(DISTDIR)/main.sim

$(DISTDIR)/main.o: main.c
	$(CC) $(CFLAGS) main.c -o $(DISTDIR)/main.o

$(DISTDIR)/utils.o: $(LIBDIR)/utils.c
	$(CC) $(CFLAGS) $(LIBDIR)/utils.c -o $(DISTDIR)/utils.o

clean:
	rm -rf ./$(DISTDIR) && mkdir $(DISTDIR) && touch ./$(DISTDIR)/.keep

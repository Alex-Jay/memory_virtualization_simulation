# Global Variables
EXECNAME		=	main.sim
CC				= 	gcc
CFLAGS			= 	-c #-Wall
LIBDIR			= 	lib
DISTDIR			= 	dist
BUILDOBJECTS	= 	$(DISTDIR)/main.o\
					$(DISTDIR)/utils.o\

# Use incremental build as default target
default: run

link: $(BUILDOBJECTS)
	$(CC) $? -o $(DISTDIR)/simulate
$(DISTDIR)/main.o: main.c
	$(CC) $(CFLAGS) main.c -o $(DISTDIR)/main.o

$(DISTDIR)/utils.o: $(LIBDIR)/utils.c
	$(CC) $(CFLAGS) $(LIBDIR)/utils.c -o $(DISTDIR)/utils.o

clean:
	rm -rf ./$(DISTDIR) && mkdir $(DISTDIR) && touch ./$(DISTDIR)/.keep

run: link
	./$(DISTDIR)/simulate
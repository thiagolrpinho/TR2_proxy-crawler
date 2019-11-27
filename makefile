	
#	Name	of	the	project
PROJ_NAME=Proxy
	
#	.c	files
C_SOURCE=$(wildcard	./src/*.c)
	
#	.h	files
IDIR	=./include
SDIR	=./src

_DEPS=$(wildcard	*.h)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
	
#	Object	files
OBJ=$(subst	.c,.o,$(subst	src,objects,$(C_SOURCE)))
	
#	Compiler	and	linker
CC=gcc
	
#	Flags	for	compiler
CFLAGS  = -Wall -I$(IDIR) -c
	
#	Command	used	at	clean	target
RM	=	rm	-rf
	
#
#	Compilation	and	linking
#
all:	objFolder	$(PROJ_NAME)
	
$(PROJ_NAME):	$(OBJ)
	@	echo	'Building	binary	using	GCC	linker:	$@'
	$(CC)	$^	-o	$@
	@	echo	'Finished	building	binary:	$@'
	@	echo	'	'
	
./objects/%.o:	./src/%.c	$(DEPS)
	@	echo	'Building	target	using	GCC	compiler:	$<'
	$(CC)	$<	$(CFLAGS)	-o	$@
	@	echo	'	'
	
./objects/main.o:	./src/main.c	$(DEPS)
	@	echo	'Building	target	using	GCC	compiler:	$<'
	$(CC)	$<	$(CFLAGS)	-o	$@
	@	echo	'	'
	
objFolder:
	@	mkdir	-p	objects
	
clean:
	@	$(RM)	./objects/*.o	$(PROJ_NAME)	*~
	@	rmdir	objects
	
.PHONY:	all	clean
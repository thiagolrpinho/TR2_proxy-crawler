	
#	Name	of	the	project
PROJ_NAME=Proxy

#Directories
INCLUDE_DIRECTORY	=./include
SOURCE_DIRECTORY	=./src
OBJECTS_DIRECTORY = ./objects

#	.c	files
_C_SOURCE=$(wildcard	$(patsubst %,$(SOURCE_DIRECTORY)/%,*.c))

#	.h	files
_DEPS=$(wildcard	$(patsubst %,$(INCLUDE_DIRECTORY)/%, *.h))
	
#	Object	files
OBJ=$(subst	.c,.o,$(subst	src,objects,$(_C_SOURCE)))
	
#	Compiler	and	linker
CC=gcc
	
#	Flags	for	compiler
CFLAGS  = -Wall -I$(INCLUDE_DIRECTORY) -c
	
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
	
$(patsubst %,$(OBJECTS_DIRECTORY)/%,%.o):	$(patsubst %,$(SOURCE_DIRECTORY)/%,%.c)	$(_DEPS)
	@	echo	'Building	target	using	GCC	compiler:	$<'
	$(CC)	$<	$(CFLAGS)	-o	$@
	@	echo	'	'
	
$(patsubst %,$(OBJECTS_DIRECTORY)/%,main.o):	$(patsubst %,$(SOURCE_DIRECTORY)/%,main.c)	$(_DEPS)
	@	echo	'Building	target	using	GCC	compiler:	$<'
	$(CC)	$<	$(CFLAGS)	-o	$@
	@	echo	'	'
	
objFolder:
	@	mkdir	-p	objects
	
clean:
	@	$(RM)	./objects/*.o	$(PROJ_NAME)	*~
	@	rmdir	objects
	
.PHONY:	all	clean
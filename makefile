	#	Name	of	the	project
PROJ_NAME=Proxy

#Directories
INCLUDE_DIRECTORY	=./include
SOURCE_DIRECTORY	=./src
OBJECTS_DIRECTORY = ./objects

#	.c	files
_C_SOURCE=$(wildcard	$(patsubst %,$(SOURCE_DIRECTORY)/%,*.cpp))

#	.h	files
_DEPS=$(wildcard	$(patsubst %,$(INCLUDE_DIRECTORY)/%, *.hpp))

#	Object	files
OBJECT_SOURCES=$(subst	.cpp,.o,$(subst	$(SOURCE_DIRECTORY),$(OBJECTS_DIRECTORY),$(_C_SOURCE)))

# Variables to make the code more legible	

OBJECT_FILES= $(patsubst %,$(OBJECTS_DIRECTORY)/%,%.o)
C_FILES = $(patsubst %,$(SOURCE_DIRECTORY)/%,%.cpp)

#	Compiler	and	linker
CC=g++
	
#	Flags	for	compiler
CFLAGS  = -Wall -I$(INCLUDE_DIRECTORY) -c
	
#	Command	used	at	clean	target
RM	=	rm	-rf
	
#
#	Compilation	and	linking
#
#This is the first rule, it verfies if objFolder rule was done and if PROJ_NAME rule was done
all:	objFolder	$(PROJ_NAME)

# Then it looks for the PROJ_NAME rule and it verifies if the OBJ_SOURCES files exists, if not it follows that rule
# If they do exist, it compiles using the chosen compiler, the proj_name as the program name and using the obj_sources files
$(PROJ_NAME):	$(OBJECT_SOURCES)
	@	echo	'Building	binary	using	GCC	linker:	$@'
	$(CC)	$^	-o	$@
	@	echo	'Finished	building	binary:	$@'
	@	echo	'	'

# If not done, then it verifies if the source files exists and then compiles the source files	
$(OBJECT_FILES):	$(C_FILES)	$(_DEPS)
	@	echo	'Building	target	using	GCC	compiler:	$<'
	$(CC)	$<	$(CFLAGS)	-o	$@
	@	echo	'	'
	
objFolder:
	@	mkdir	-p	objects
	
clean:
	@	$(RM)	./objects/*.o	$(PROJ_NAME)	*~
	@	rmdir	objects
	
.PHONY:	all	clean
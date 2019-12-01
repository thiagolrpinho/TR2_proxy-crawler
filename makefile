	#	Name	of	the	project
PROJ_NAME=Proxy

#Directories
INCLUDE_DIRECTORY	=./include
SOURCE_DIRECTORY	=./src
TEST_SOURCE_DIRECTORY	=./test_src
OBJECTS_DIRECTORY = ./objects

#	.cpp	files
_C_SOURCE=$(wildcard	$(patsubst %,$(SOURCE_DIRECTORY)/%,*.cpp))

#	test .cpp	files
TEST_C_SOURCE= ./src/estrutura_helper.cpp ./test_src/testa_estrutura_helper.cpp ./test_src/tests_main.cpp

#	.hpp	files
_DEPS=$(wildcard	$(patsubst %,$(INCLUDE_DIRECTORY)/%, *.hpp))


#	Object	files
OBJECT_SOURCES=$(subst	.cpp,.o,$(subst	$(SOURCE_DIRECTORY),$(OBJECTS_DIRECTORY),$(_C_SOURCE)))
TEST_OBJECT_SOURCES= ./objects/estrutura_helper.o ./objects/testa_estrutura_helper.o ./objects/tests_main.o

# Variables to make the code more legible	

OBJECT_FILES= $(patsubst %,$(OBJECTS_DIRECTORY)/%,%.o)
C_FILES = $(patsubst %,$(SOURCE_DIRECTORY)/%,%.cpp)
TEST_C_FILES = $(patsubst %,$(TEST_SOURCE_DIRECTORY)/%,%.cpp)

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
all:	objFolder cleanCached	$(PROJ_NAME) 

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

$(OBJECT_FILES):	$(TEST_C_FILES)	$(_DEPS)
	@	echo	'Building	target	using	GCC	compiler:	$<'
	$(CC)	$<	$(CFLAGS)	-o	$@
	@	echo	'	'

testes:	$(TEST_OBJECT_SOURCES)
	@	echo	'Building	binary	using	GCC	linker:	$@'
	$(CC)	$^	-o	$@
	@	echo	'Finished	building	binary:	$@'
	@	echo	'	'

objFolder:
	@	mkdir	-p	objects
	
clean:
	@	$(RM)	./objects/*.o ./cached_files/*	$(PROJ_NAME)	*~

cleanCached:
	@	$(RM)	-r ./cached_files/*

.PHONY:	all	clean
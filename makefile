TARGET_OBJECT := chp
rebuildables = ${TARGET_OBJECT}

 # source and include tree locations
SOURCE_TREE := src
INCLUDE_TREE := include

vpath %.c ${SOURCE_TREE}
vpath %.h ${INCLUDE_TREE}

# compilation driver variables
CCD := gcc
CCD_FLAGS := -g -w -std=gnu99 -I${INCLUDE_TREE}
LIBS :=

# list of source files
source = $(wildcard ${SOURCE_TREE}/*.c)

# list of object files
objects = $(subst .c,.o,${source})
rebuildables += ${objects}

# list of external programs
ECHO := echo
CP := cp
GZIP := gzip
RM := rm
SED := sed
MAKE := make
AWK := awk
SORT := sort
PR := pr
CAT := cat

.PHONY: all
all: ${TARGET_OBJECT}


${TARGET_OBJECT}: ${objects} ${LIBS}
	@${ECHO} "Linking executable object \"${TARGET_OBJECT}\"..."
	${CCD} ${CCD_FLAGS}  -o $@ $^
	@${ECHO} "Done linking \"${TARGET_OBJECT}\"."	
	
%.o: %.c
	@${ECHO} "Building \"$@\" object..."
	${CCD} -c ${CCD_FLAGS}  -o $@ $<
	@${ECHO} "Done building \"$@\"."

%.d: %.c
	@${ECHO} "Generating include dependency file \"$@\"..."
	$(CCD) -M  ${CCD_FLAGS} $< > $@
	@${ECHO} "Done generating \"$@\"."
	
# automatically manage include dependencies for the source files
include_dependency_files := $(subst .c,.d,${source})
ifneq ($(MAKECMDGOALS),clean)
include ${include_dependency_files}
endif

rebuildables += ${include_dependency_files}

.PHONY: install
install:
	@${ECHO} "Copying configuration files to home directory..."
	${CP} -r .chp ~/
	@${ECHO} "Done copying configuration files to home directory."
	
	@${ECHO} "Appending contents of include file to end of ~/.bashrc ..."
	${CAT} inc >> ~/.bashrc
	@${ECHO} "Done appending contents of include file to end of ~/.bashrc."
		
	@${ECHO} "Compressing manual page..."		
	${GZIP} -k -f doc/chp.1
	@${ECHO} "Done compressing manual page."
	
	@${ECHO} "Copying compressed man page to a directory searched by \"man\"..."	
	${CP} doc/chp.1.gz "/usr/local/man/man1/chp.1.gz"
	@${ECHO} "Done copying compressed man page to a directory searched by \"man\"."	
	
	@${ECHO} "Copying binary executable to a PATH directory..."	
	${CP} ${TARGET_OBJECT} /usr/local/bin
	@${ECHO} "Done copying binary executable to a PATH directory."	

.PHONY: clean
clean:
	@${ECHO} "Removing rebuildable files..."	
	${RM} -f ${rebuildables}
	@${ECHO} "Done removing rebuildable files."	

define display-help
${MAKE} --print-data-base --question | \
${AWK} '/^[^.%][-A-Za-z0-9_]*:/ \
{ print substr($$1, 1, length($$1)-1) }' | \
${SORT} | \
${PR} --omit-pagination --width=80 --columns=4
endef

.PHONY: help
help:
	@${ECHO} "List of targets:"	
@${display-help}

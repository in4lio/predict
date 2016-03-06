#                  _ _     _
#    ___ ___ ___ _| |_|___| |_
#   |   |  _   _|   | |  _   _|
#   |  _|_| |___ ___|_|___  |
#   |_|                   |_|
#   makefile ( yupp, gcc )

# -- binary name (without extension)
BIN = predict

# -- creating MAP file
MAP = 0

# -- platform (core)
ifeq ($(OS),Windows_NT)
# ARM Cortex-M: __CORTEX_M__
# MSDOS: __DJGPP__
# WIN32: __MINGW__
# UNIX: __UNIX__
PLATFORM = __MINGW__
else
# UNIX
PLATFORM = __UNIX__
endif

TOP = .

# -- compilers
ifeq ($(PLATFORM),__DJGPP__)
CC = $(DJGPP_HOME)/bin/gcc.exe
CXX = $(DJGPP_HOME)/bin/gxx.exe
LINK = $(CC)
else
ifeq ($(PLATFORM),__CORTEX_M__)
CC = armcc
CXX = armcc
LINK = armlink
else
CC = gcc
CXX = g++
LINK = $(CC)
endif
endif

# -- yupp preprocessor
YUPP_HOME = $(TOP)/yupp

# -- perform preprocessing
SKIP_PP = 0
# -- skip preprocessing
# SKIP_PP = 1

ifeq ($(SKIP_PP),0)
PP = python -u $(YUPP_HOME)/yup.py
else
PP = @echo makefile: warning: preprocessing step is skipped,
endif

# -- command to create 'object' and 'bin' directories and subdirectories
MKDIR = mkdir -p

# -- output subdirectory
ifeq ($(PLATFORM),__DJGPP__)
D_PLATFORM = djgpp
else
ifeq ($(PLATFORM),__MINGW__)
D_PLATFORM = mingw
else
ifeq ($(PLATFORM),__CORTEX_M__)
D_PLATFORM = cm3
else
D_PLATFORM = .
endif
endif
endif

# -- yupp import directories
D_YU = source/app source/app/ut source/app/debug source/core source/core/debug source/core/ut
D_YU := $(D_YU) source/platform/$(D_PLATFORM)

# -- source directories
D_C = $(D_YU)
D_CXX = $(D_C)
D_ASM = source

# -- include directories
D_H = $(D_C) $(YUPP_HOME)/lib

# -- binary directory
D_BIN = bin
D_BIN := $(if $(D_PLATFORM), $(D_BIN)/$(D_PLATFORM), $(D_BIN))

# -- object directory
D_OBJ = object
ifeq ($(PLATFORM),__CORTEX_M__)
D_OBJ := $(D_BIN)
else
D_OBJ := $(if $(D_PLATFORM), $(D_OBJ)/$(D_PLATFORM), $(D_OBJ))
endif

# -- LIST and MAP directories
D_MAP = object
D_LIST = object

# -- source code suffix
E_YU = .yu
E_YUH = .yu-h
E_YUC = .yu-c
E_YUCXX = .yu-cpp

E_H = .h
E_C = .c
E_CXX = .cpp
E_ASM = .asm

# -- object suffix
E_OBJ = .o

# -- binary suffix
ifeq ($(PLATFORM),__CORTEX_M__)
E_BIN = .axf
else
ifeq ($(OS),Windows_NT)
E_BIN = .exe
else
E_BIN =
endif
endif

# -- binary full name
F_BIN = $(D_BIN)/$(BIN)$(E_BIN)

# -- LIST and MAP suffixes
E_MAP = .map
E_LIST = .listing

# -- link options
LIBS = -lm

ifeq ($(PLATFORM),__MINGW__)
# LIBS := $(LIBS) -lws2_32
endif

LFLAGS =

ifeq ($(MAP),1)
LFLAGS := $(LFLAGS) -Wl,-Map,$(D_MAP)/$(BIN)$(E_MAP)
endif

# -- preprocessor flags
PPFLAGS = -q --pp-browse -Wno-unbound $(addprefix -d, $(D_YU))

# -- compiler flags
CFLAGS = $(addprefix -I, $(D_H)) -O2 -std=gnu99 -W -Wall -Wno-comment
CXXFLAGS = $(addprefix -I, $(D_H)) -O2 -ffast-math -funroll-loops -fno-exceptions -fomit-frame-pointer -g -W -Wall -Wno-comment
ASMFLAGS = -Wall

# -- platform specific options
ifeq ($(PLATFORM),__DJGPP__)
BUFSIZE = 16k
MINSTACK = 1024k
endif

# ---------------------------------
#   files lists
# ---------------------------------

S_YU = $(wildcard $(addsuffix /*$(E_YU), $(D_YU)))
S_YUH = $(wildcard $(addsuffix /*$(E_YUH), $(D_H)))
S_YUC = $(wildcard $(addsuffix /*$(E_YUC), $(D_C)))
S_YUCXX = $(wildcard $(addsuffix /*$(E_YUCXX), $(D_CXX)))

G_CXX = $(addsuffix $(E_CXX), $(basename $(S_YUCXX)))
G_C = $(addsuffix $(E_C), $(basename $(S_YUC)))
G_H = $(addsuffix $(E_H), $(basename $(S_YUH)))

S_C = $(sort $(wildcard $(addsuffix /*$(E_C), $(D_C))) $(G_C))
S_CXX = $(sort $(wildcard $(addsuffix /*$(E_CXX), $(D_CXX))) $(G_CXX))
S_ASM = $(wildcard $(addsuffix /*$(E_ASM), $(D_ASM)))

O_CXX = $(addprefix $(D_OBJ)/, $(addsuffix $(E_OBJ), $(basename $(notdir $(S_CXX)))))
O_C = $(addprefix $(D_OBJ)/, $(addsuffix $(E_OBJ), $(basename $(notdir $(S_C)))))
O_ASM = $(addprefix $(D_OBJ)/, $(addsuffix $(E_OBJ), $(basename $(notdir $(S_ASM)))))

O = $(O_CXX) $(O_C) $(O_ASM)

# ---------------------------------
#   commands
# ---------------------------------

# -- wrap compiler arguments
ifeq ($(OS),Windows_NT)
# -- too long command line workaround
define wrap
	echo $2 > args
	$1 @args
	-rm args
endef
else
define wrap
	$1 $2
endef
endif

# -- call compiler
ifeq ($(PLATFORM),__CORTEX_M__)
# -- use Keil arguments from .__i file
define cc
	cd project && \
	$(CC) --via ../$(basename $2).__i && \
	cd ..
endef

define cxx
	cd project && \
	$(CXX) --via ../$(basename $2).__i
	cd ..
endef

define asm
	cd project && \
	$(ASM) --via ../$(basename $2)._ia
	cd ..
endef

define link
	cd project && \
	$(LINK) --via ../$(basename $2).lnp
	cd ..
endef
else
define cc
	$(call wrap,$(CC),$(CFLAGS) -c $1 -o $2)
endef

define cxx
	$(call wrap,$(CXX),$(CXXFLAGS) -c $1 -o $2)
endef

define asm
	$(call wrap,$(CC),$(ASMFLAGS) -c $1 -o $2)
endef

define link
	$(call wrap,$(LINK),$1 -o $2 $(LIBS) $(LFLAGS))
endef
endif

# -- optional final tools
ifeq ($(PLATFORM),__DJGPP__)
define final
	stubedit $1 minstack=$(MINSTACK) bufsize=$(BUFSIZE)
endef
else
define final
endef
endif

# -- removal list
R_BIN = $(F_BIN) $(O)
R = $(R_BIN)

ifeq ($(SKIP_PP),0)
R := $(R) $(G_H) $(G_C) $(G_CXX)
endif

ifeq ($(MAP),1)
R := $(R) $(D_MAP)/$(BIN)$(E_MAP)
endif

ifeq ($(OS),Windows_NT)
#CLEAN = cmd /c "del $(subst /,\,$(R))"
CLEAN = rm -rf $(R)
else
CLEAN = rm -rf $(R)
endif

CLEAN_BIN = rm -rf $(R_BIN)

# -- install
define install

endef

# ---------------------------------
#   make rules
# ---------------------------------

vpath %$(E_CXX) $(D_CXX)
vpath %$(E_C) $(D_C)
vpath %$(E_ASM) $(D_ASM)
vpath %$(E_YUCXX) $(D_CXX)
vpath %$(E_YUC) $(D_C)

# -- build project
.PHONY: all

all: bindirs $(F_BIN)

$(F_BIN): $(O)
	$(call link,$^,$@)
	$(call final,$@)
	@echo "*** $(F_BIN) ***"

$(G_C) $(G_CXX) $(G_H): $(S_YU)

$(G_C): %$(E_C): %$(E_YUC)
	$(call wrap,$(PP),$(PPFLAGS) $<)

$(G_CXX): %$(E_CXX): %$(E_YUCXX)
	$(call wrap,$(PP),$(PPFLAGS) $<)

$(G_H): %$(E_H): %$(E_YUH)
	$(call wrap,$(PP),$(PPFLAGS) $<)

$(S_C) $(S_CXX): $(G_H)

$(O_C): $(D_OBJ)/%$(E_OBJ): %$(E_C)
	$(call cc,$<,$@)

$(O_CXX): $(D_OBJ)/%$(E_OBJ): %$(E_CXX)
	$(call cxx,$<,$@)

$(O_ASM): $(D_OBJ)/%$(E_OBJ): %$(E_ASM)
	$(call asm,$<,$@)

# -- create 'object' and 'bin' directories
bindirs: $(D_OBJ) $(D_BIN)

$(D_OBJ):
	${MKDIR} ${D_OBJ}

$(D_BIN):
	${MKDIR} ${D_BIN}

# -- perform preprocessing only
.PHONY: yupp

yupp: $(G_C) $(G_CXX) $(G_H)

# -- remove temporary files
.PHONY: clean

clean:
	$(CLEAN)

# -- remove binary files
.PHONY: clean-binary

clean-binary:
	$(CLEAN_BIN)

# -- install project
.PHONY: install

install:
	$(call install)

# -- EOF

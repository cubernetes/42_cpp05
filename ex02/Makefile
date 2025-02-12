# config
NAME := ex02
# change to c for C projects and cpp for C++ projects
# source files must still be specified with their extension
EXT := cpp

# tools
# Not using CXX since it defaults to g++, thus making it impossible to use another default while also using ?= assignment
_CXX ?= c++
#_CXX := clang++ # TODO: @all: make sure it compiles with this
#_CXX := g++     # TODO: @all: make sure it compiles with this
RM := /bin/rm -f
MKDIR := /bin/mkdir -p

# Don't touch below, always configure via _CXX
# WILL break on non-POSIX systems, so hm sucks I guess
CXX := $(notdir $(shell ls -l $$(which $(_CXX)) | awk '{print $$NF}'))

# flags
CFLAGS += -O3
CFLAGS += -Werror # TODO: @all: Add back
CFLAGS += -MMD
CFLAGS += -MP
# warnings
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wshadow
CFLAGS += -Wconversion
CFLAGS += -Wunreachable-code
CFLAGS += -Wnon-virtual-dtor
CFLAGS += -Wold-style-cast
CFLAGS += -Wcast-align
CFLAGS += -Wunused
CFLAGS += -Woverloaded-virtual
CFLAGS += -Wsign-conversion
CFLAGS += -Wnull-dereference
CFLAGS += -Wdouble-promotion
CFLAGS += -Wformat=2

ifeq ($(CPP23), 1)
CFLAGS += -std=c++23
CPPFLAGS += -DCOMPILING_FOR_CPP23=1
else
CFLAGS += -std=c++98
endif

CFLAGS += -fdiagnostics-color=always
ifeq ($(strip $(CXX)),clang++)
CFLAGS += -ferror-limit=1
# clang-specific warnings
CFLAGS += -Wreturn-stack-address
CFLAGS += -Wdangling-gsl
else ifeq ($(strip $(CXX)),g++)
CFLAGS += -fmax-errors=1
# gcc-specific warnings
CFLAGS += -Wduplicated-cond
CFLAGS += -Wduplicated-branches
CFLAGS += -Wlogical-op
CFLAGS += -Wuseless-cast
endif

CXXFLAGS += -Weffc++

CPPFLAGS += -I.
CPPFLAGS += -Ilib

# LDLIBS +=

# DEBUG=1 make re # include debugging information in the binary
ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb3 -O0 -DPP_DEBUG=true
	LDFLAGS += -ggdb3 -O0
endif

# ASAN=1 make re # check for memory corruptions and some leaks
ifeq ($(ASAN), 1)
	CFLAGS += -fsanitize=address
	LDFLAGS += -fsanitize=address
endif

# TSAN=1 make re # check for thread errors and data races
ifeq ($(TSAN), 1)
	CFLAGS += -fsanitize=thread
	LDFLAGS += -fsanitize=thread
endif

# sources
SRC :=

vpath %.$(EXT) .
SRC += Bureaucrat.cpp
SRC += AForm.cpp
SRC += ShrubberyCreationForm.cpp
SRC += RobotomyRequestForm.cpp
SRC += PresidentialPardonForm.cpp
SRC += main.cpp

vpath %.$(EXT) lib
SRC += Ansi.cpp
SRC += Constants.cpp
SRC += Logger.cpp
SRC += Options.cpp
SRC += Reflection.cpp
SRC += Repr.cpp
SRC += Utils.cpp

# object vars
OBJ := $(SRC:.$(EXT)=.o)
OBJDIR := obj
OBJ := $(addprefix $(OBJDIR)/,$(OBJ))

# deps (relink also when header files change)
DEPS := $(OBJ:.o=.d)
-include $(DEPS)

# rules
.DEFAULT_GOAL := all

## Build project
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJDIR)/%.o: %.$(EXT) | $(OBJDIR)
	$(CXX) $< $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c -o $@

$(OBJDIR):
	$(MKDIR) $@

# Cleanup
## Remove intermediate files
clean:
	$(RM) $(OBJ)
	$(RM) $(DEPS)
	$(RM) -r $(OBJDIR)

## Remove intermediate files as well as well as build artefacts
fclean: clean
	$(RM) $(NAME)

## Remove intermediate files, build artefacts, and untracked files (interactively)
pristine: fclean
	git clean -dfi

## Rebuild project
re: fclean
	$(MAKE) all

## Build project, then run
run: all
	@printf '\n'
	@# This allows $(NAME) to be run using either an absolute, relative or no path.
	@# You can pass arguments like this: make run ARGS="hello ' to this world ! ' ."
	@PATH=".$${PATH:+:$${PATH}}" && $(NAME) $(ARGS)

## Build project, then run using valgrind memcheck
valrun: all
	@printf '\n'
	@PATH=".$${PATH:+:$${PATH}}" && valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--track-fds=yes \
		$(NAME) \
		$(ARGS)

# Convenience
## Rebuild project, then run
rerun: re
	$(MAKE) run

## Rebuild project, then run using valgrind memcheck
leakcheck: re
	$(MAKE) valrun

### Display this helpful message
h help:
	@printf '\033[31m%b\033[m\n\nTARGETs:\n' "USAGE:\n\tmake <TARGET> [ARGS=\"\"]"
	@<Makefile python3 -c 'exec('"'"'import re\n\nWIDTH = 8\nregex_self_doc = r"## [\\s\\S]*?\\n([a-z_][a-zA-Z -_]*):"\nmatches = list(re.finditer(regex_self_doc, open(0).read()))\nformatted_targets = []\nfor match in matches:\n    target = match.groups()[0]\n    doc_str = "\\n".join(match.group().split("\\n")[:-1]).replace("\\n", " ").replace("## ", "")\n    doc_str_words = doc_str.split()\n    doc_str_words_folded = [doc_str_words[i:i+WIDTH] for i in range(0, len(doc_str_words), WIDTH)]\n    formatted_doc_str = "\\n\\t".join([" ".join(words) for words in doc_str_words_folded])\n    formatted_targets.append(f"\\033[36m{target}\\033[m:\\n\\t{formatted_doc_str}")\nhelp_str = "\\n".join(formatted_targets)\nprint(help_str)\n'"'"')'
	@printf '\n\033[33mNOTES:\n\t%s\033[m\n' 'ARGS only makes sense when the target runs the program'

.PHONY: all
.PHONY: clean fclean
.PHONY: re
.PHONY: run rerun
.PHONY: valrun leakcheck

# keep intermediate (*.h, *.o, *.d, *.a) targets
.SECONDARY:

# delete failed targets
.DELETE_ON_ERROR:

CFLAGS ?=-Wextra -g -fsanitize=address -fno-elide-constructors -Wall -fstack-protector-all -fno-stack-protector -pedantic -fwrapv --param ssp-buffer-size=4 -fvisibility=hidden -Wcast-align -Wmissing-field-initializers -Wshadow -Wswitch-enum -O0

C_SRCS := $(sort $(wildcard *.cpp))
C_OBJS := ${C_SRCS:.cpp=.o}
OBJS := $(C_OBJS)

INCLUDE_DIRS := .

CFLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))

#SHARED_LIB := -lsfml-graphics -lsfml-window -lsfml-system

all: lib run

lib:
	clang++ $(CFLAGS) $(C_SRCS) -lgtest  -o do
run:
	ASAN_OPTIONS=detect_leaks=1 ./do


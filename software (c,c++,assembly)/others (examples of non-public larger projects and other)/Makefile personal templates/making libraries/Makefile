COMPILATOR := g++
COMPILATOR_STATIC_LIB := ar 

SRC_FILES_CPP := $(wildcard *.cpp)
SRC_FILES_C := $(wildcard *.c)
SRC_FLAGS := -m32 -O2 -s

BINARY_SRC_FILES := $(SRC_FILES_CPP:%.cpp=src/%.o) $(SRC_FILES_C:%.c=src/%.o)
BINARY_SRC_FLAGS := -m32 -O2 -s

STATIC_LIBS := libhelp_library.a
STATIC_LIBS_FLAGS := --target=pe-i386


library/${STATIC_LIBS}: ${BINARY_SRC_FILES}
	${COMPILATOR_STATIC_LIB} rcsu ${STATIC_LIBS_FLAGS} $@ $^ 

src/%.o: %.c
	${COMPILATOR} $< -c ${BINARY_SRC_FLAGS} -o $@

src/%.o: %.cpp
	${COMPILATOR} $< -c ${BINARY_SRC_FLAGS} -o $@

.PHONY: clean
clean:
	del /f /q $(SRC_FILES_CPP:%.cpp=src\\%.o) $(SRC_FILES_C:%.c=src\\%.o)
COMPILATOR := g++
FINALE_OUTPUT := bin/launcher.exe
DIRECTORY_SRC := src
DIRECTORY_INCLUDE := C:/SDL2/i686-w64-mingw32/include
DIRECTORY_LIB := C:/SDL2/i686-w64-mingw32/lib
STATIC_LIBS := -lmingw32 -lSDL2_image -lSDL2main -lSDL2 -mwindows

ICON := icon

FINALE_FLAGS := -m32 -O2 -s -static-libstdc++ -static-libgcc  -L${DIRECTORY_INCLUDE} ${STATIC_LIBS} -I${DIRECTORY_INCLUDE} ${DIRECTORY_SRC}/${ICON}.res

SRC_FILES_CPP := $(wildcard *.cpp)
SRC_FILES_C := $(wildcard *.c)

BINARY_SRC_FILES := $(SRC_FILES_CPP:%.cpp=${DIRECTORY_SRC}/%.o) $(SRC_FILES_C:%.c=${DIRECTORY_SRC}/%.o)
BINARY_SRC_FLAGS := -m32 -O2 -s -L${DIRECTORY_INCLUDE} -l${STATIC_LIBS} -I${DIRECTORY_INCLUDE}

${FINALE_OUTPUT}: ${BINARY_SRC_FILES}
	${COMPILATOR} $^ ${FINALE_FLAGS} -o ${FINALE_OUTPUT}

${DIRECTORY_SRC}/%.o: %.c
	${COMPILATOR} $< -c ${BINARY_SRC_FLAGS} -o $@

${DIRECTORY_SRC}/%.o: %.cpp
	${COMPILATOR} $< -c ${BINARY_SRC_FLAGS} -o $@

.PHONY: clean
clean:
	del /f /q $(SRC_FILES_CPP:%.cpp=${DIRECTORY_SRC}\\%.o) $(SRC_FILES_C:%.c=${DIRECTORY_SRC}\\%.o) ${DIRECTORY_SRC}\${ICON}.res

.PHONy: icon
icon:
	windres.exe -J rc -O coff -i ${ICON}.rc -o ${DIRECTORY_SRC}/${ICON}.res -F pe-i386
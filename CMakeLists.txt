cmake_minimum_required(VERSION 3.16)
project(Famine C ASM_NASM)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-Wall -Wextra -nostdlib -fPIC -nodefaultlibs -Wno-stack-protector -fno-builtin -g3")
set(CMAKE_ASM_FLAGS "-felf64 -g -Fdwarf")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -fPIC")

set(SOURCES
        src/asm/famine.asm
        src/famine.c
        src/daemon.c
        src/utils.c
        src/asm/syscall.asm
        src/asm/strlen.asm
        src/asm/strcpy.asm
        src/asm/memcpy.asm
        src/asm/memmem.asm
        src/asm/end.asm)
set(HEADERS include/famine.h)

add_executable(Famine ${SOURCES} ${HEADERS})
target_include_directories(Famine PRIVATE include)
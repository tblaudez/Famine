cmake_minimum_required(VERSION 3.16)
project(Famine C ASM_NASM)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-Wall -Wextra -nostdlib -fPIC -nodefaultlibs -Wno-stack-protector -fno-builtin")
set(CMAKE_ASM_FLAGS "-felf64")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -fPIC")

set(SOURCES
        src/asm/payload.asm
        src/famine.c
        src/daemon.c
        src/utils.c
        src/asm/syscall.asm
        src/asm/libasm/strlen.asm
        src/asm/libasm/strcpy.asm
        src/asm/libasm/memcpy.asm
        src/asm/libasm/memmem.asm
        src/asm/end.asm)
set(HEADERS include/famine.h)

add_executable(Famine ${SOURCES} ${HEADERS})
target_include_directories(Famine PRIVATE include)
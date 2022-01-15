//
// Created by tblaudez on 1/14/22.
//

#include <stdbool.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <dirent.h>
#include "famine.h"

static bool isDaemon(const char *procDirectory, const char *dirName) {
	size_t dirNameLen = ft_strlen(dirName);
	char filePath[dirNameLen + 12];
	ft_strcpy(filePath, procDirectory);
	ft_strcpy(filePath + 6, dirName);
	ft_strcpy(filePath + 6 + dirNameLen, ((char[]) {'/', 's', 't', 'a', 't', '\0'}));

	int fd = (int) syscall_wrapper(__NR_open, filePath, O_RDONLY);
	if (fd == -1) {
		return false;
	}

	char readBuf[32];
	syscall_wrapper(__NR_read, fd, &readBuf, sizeof(readBuf));
	syscall_wrapper(__NR_close, fd);
	return ft_memmem(readBuf, sizeof(readBuf), ((char[]) {'(', 'd', 'a', 'e', 'm', 'o', 'n', ')', '\0'}), 8);

}

bool DaemonProcessRunning(const char *procDirectory) {
	int fd = (int) syscall_wrapper(__NR_open, procDirectory, O_RDONLY | O_DIRECTORY);
	if (fd == -1) {
		return false;
	}

	while (1) {
		char bufDirent[1024];
		int entsize = (int) syscall_wrapper(__NR_getdents64, fd, &bufDirent, sizeof(bufDirent));
		if (entsize <= 0) {
			break;
		}

		for (int offset = 0; offset < entsize;) {
			struct linux_dirent64 *entry = (struct linux_dirent64 *) (bufDirent + offset);
			if (entry->d_type == DT_DIR && entry->d_name[0] != '.') {
				if (isDaemon(procDirectory, entry->d_name)) {
					syscall_wrapper(__NR_close, fd);
					return true;
				}
			}
			offset += entry->d_reclen;
		}
	}

	syscall_wrapper(__NR_close, fd);
	return false;
}


//
// Created by tblaudez on 1/14/22.
//

#include <unistd.h>

int main(void) {
	daemon(1, 1);
	while (1) {
		sleep(1);
	}
}
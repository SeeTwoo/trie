#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include "slice.h";

#define BUFFER_SIZE 1024

struct gnl {
	int		fd;
	char		buffer[BUFFER_SIZE];
	struct slice	remaining;
};

#endif

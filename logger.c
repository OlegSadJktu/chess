#include "logger.h"

#define FILENAME "log.log"

static int fd = -1;

static int createFD() {
    if (fd != -1) {
        return fd;
    }
    fd = open(FILENAME, O_WRONLY | O_APPEND | O_CREAT, 0666);
    return fd;
}

void logInt(char *tag, int data) {
    createFD();
    if (strlen(tag) > 60) {
        logInfo("To long tag");
        return;
    }
    char str[80];
    sprintf(str, "%s: %i", tag, data);
    logInfo(str);
}

void logInfo(char* info) {
    createFD();
    write(fd, info, strlen(info));
    write(fd, "\n", strlen("\n"));
}


#include <stdio.h>
#include <string.h>

#include "io.h"
#include "chauder.h"
#include "log.h"

error_et read_file(char const* fname, char** buf, size_t* len) {
    FILE* fd = fopen(fname, "r");
    if (fd == NULL) {
        ERROR("Can't open file '%s'", fname);
        return SHADER_READ_ERROR;
    }

    fseek(fd, 0L, SEEK_END);
    *len = ftell(fd);
    rewind(fd);

    *buf = malloc(*len);

    size_t nread = fread(*buf, sizeof(char), *len, fd);
    if (nread < *len) {
        WARNING(
            "File '%s' is %zu bytes long but only %zu bytes where read, attempting to continue.",
            fname, *len, nread);
    }

    fclose(fd);
    return CHAUDER_SUCCESS;
}

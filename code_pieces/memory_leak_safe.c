#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buffer;
    size_t len;
} Line;

static Line make_line(const char *src) {
    Line line;
    line.len = strlen(src);

    line.buffer = malloc(line.len + 1);
    memcpy(line.buffer, src, line.len + 1);

    return line;
}

static Line process_line(const char *input) {
    Line temp = make_line(input);

    Line out = temp;

    return out;
}

int main() {
    for (int i = 0;; i++) {
        Line l = process_line("example text"); 

        if (i == 0) {
            printf("%s\n", l.buffer);
        }

        free(l.buffer)
    }

    return 0;
}
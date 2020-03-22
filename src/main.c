#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

static uint8_t * tape_ptr = 0;

const char *
interpret(const char *);

signed
main (void) {

    size_t TAPE_LENGTH = 30000;
    uint8_t * tape = calloc(TAPE_LENGTH, sizeof (uint8_t));
    if ( !tape ) {
        return EXIT_FAILURE;
    }

    tape_ptr = tape;

    const char * p = isatty(fileno(stdin)) ? "bf: " : "";
    char * input;
    while ( (input = readline(p)) ) {
        add_history(input);
        interpret(input);
        free(input);
    }

    free(tape);
    return EXIT_SUCCESS;
}

const char *
interpret (const char * inst) {

    if ( !inst ) { return 0; }

    const char * c = inst;
    while ( inst && *inst ) {
        switch ( *inst ) {
            case '.': putchar(*tape_ptr); ++inst; break;
            case ',': *tape_ptr = (uint8_t )getchar(); ++inst; break;
            case '+': ++(*tape_ptr); ++inst; break;
            case '-': --(*tape_ptr); ++inst; break;
            case '>': ++tape_ptr; ++inst; break;
            case '<': --tape_ptr; ++inst; break;
            case '[': inst = interpret(inst + 1); break;
            case ']': if ( *tape_ptr ) { inst = c; } else { return inst + 1; }; break;
            default : ++inst; break;
        }
    }

    return 0;
}


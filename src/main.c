#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

static char tape [30000] = "";
static char * tape_ptr = tape;

const char *
interpret(const char *);

signed
main (void) {

    char * input;
    while ( (input = readline("bf: ")) ) {
        add_history(input);
        interpret(input);
        free(input);
    }

    return EXIT_SUCCESS;
}

const char *
interpret (const char * inst) {

    if ( !inst ) { return 0; }

    const char * c = inst;
    while ( inst && *inst ) {
        switch ( *inst ) {
            case '.': putchar(*tape_ptr); ++inst; break;
            case ',': *tape_ptr = (char )getchar(); ++inst; break;
            case '+': ++(*tape_ptr); ++inst; break;
            case '-': --(*tape_ptr); ++inst; break;
            case '>': ++tape_ptr; ++inst; break;
            case '<': --tape_ptr; ++inst; break;
            case '[': inst = interpret(inst + 1); break;
            case ']': if ( *tape_ptr ) { inst = c; } else { return inst + 1; }; break;
        }
    }

    return 0;
}

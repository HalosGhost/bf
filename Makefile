PROGNM = bfi

CC ?= gcc
CFLAGS ?= -g -ggdb -O3 -fPIE -flto -fstack-protector-strong --param=ssp-buffer-size=1 -Wno-reserved-id-macro -Wall -Wextra -Wpedantic -Werror -std=gnu18 -fsanitize=undefined
LDFLAGS ?= `pkg-config --libs readline`
VER = `git describe --long --tags | sed 's/\([^-]*-g\)/r\1/;s/-/./g'`
FMFLAGS = -wp -then -wp -wp-rte

ifneq ($(CC), tcc)
CFLAGS += -pie -D_FORTIFY_SOURCE=2
LDFLAGS += -Wl,-z,relro,-z,now
endif

ifeq ($(CC), clang)
CFLAGS += -Weverything -fsanitize-trap=undefined
endif

CFLAGS += -Wno-disabled-macro-expansion

include mke/rules

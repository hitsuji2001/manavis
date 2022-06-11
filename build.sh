#!/bin/bash

CXX="${CXX:-gcc}"
SRC_APP="./*.c"
CFLAGS="-Werror -Wall -Wextra -pedantic -ggdb"
OFLAGS="-lsqlite3"
LIBS="sdl2"
OUT="manavis"

set -e

if [ -z "$LIBS" ]
then
    $($CXX $SRC_APP $CFLAGS $OFLAGS -o $OUT)
else
    $($CXX $SRC_APP $CFLAGS $OFLAGS -o $OUT $(pkg-config --cflags --libs $LIBS))
fi

if [[ $? -ne 0 ]]
then
    echo "ERROR: Compile failed!"
    exit 1
else
    echo "Compile succesfully!"
    exit 0
fi

#!/bin/bash

TARGET_DIR=$PWD
OUTPUT_DIR=$PWD

mkdir -p "$OUTPUT_DIR"

CDIR=""
for x in **/*.cpp; do
  if [ "$CDIR" != "$TARGET_DIR/${x%/*}" ]; then
    CDIR="$TARGET_DIR/${x%/*}"
    cd $CDIR
    gcov -p *.cpp

    SUBDIR="${x%/*}"
    PREFIX="#${SUBDIR/\//\#}"

    for f in *.gcov; do
        if [[ $f == \#* ]] ;
        then
           cp $f "$OUTPUT_DIR/$f"
        else
           cp $f "$OUTPUT_DIR/$PREFIX#$f"
        fi
    done
  fi
done
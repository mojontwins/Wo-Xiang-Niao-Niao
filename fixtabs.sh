#!/bin/bash
find . -iname "*.h" -exec sed -i "s#\t#    #g" '{}' \;
find . -iname "*.c" -exec sed -i "s#\t#    #g" '{}' \;
find . -iname "*.bas" -exec sed -i "s#\t#    #g" '{}' \;
find . -iname "*.bi" -exec sed -i "s#\t#    #g" '{}' \;

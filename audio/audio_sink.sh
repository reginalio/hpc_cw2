#!/bin/bash
../local/bin/sox -t raw -r 44100 -L -b 16 -e signed -c 2 - -d

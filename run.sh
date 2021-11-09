#!/bin/bash

./bake.sh

./test.sh

cd src
./main "$@"
cd ..
#!/bin/bash

docker build -t dijkstra_test .

docker run --rm -it -v $(pwd):/code dijkstra_test $@

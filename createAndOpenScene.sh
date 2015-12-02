#!/usr/bin/env bash
make

./raytracer "$@"
convert scene.ppm scene.png
open scene.png
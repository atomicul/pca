#!/bin/bash

for i in {1..5}; do
	mv ~/Downloads/level$1_$i.in .
done

for i in {1..5}; do
	python3 main.py <"level$1_$i.in" >"level$1_$i.out"
done

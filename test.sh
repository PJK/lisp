#!/bin/bash

failed=0
run=0

function test {
	run=$(($run + 1))
	if [ "$(cat $1 | build/bin/interpreter)" != "$2" ]; then
		echo
		echo "Failed at $1 - expected $2, but got"
		echo "$(cat $1 | build/bin/interpreter)"
		failed=$(($failed + 1))
	else
		echo -n .
	fi
}

test example/evil_plus.l 	"Integer: -2"

test example/factorial.l 	"Integer: 720"

test example/fast_fib.l  	"Integer: 75025"

test example/map.l 			"List: '(Integer: 1, List: '(Integer: 4, List: '(Integer: 9, List: '(Integer: 16, List: '(Integer: 25, List: nil)))))"

test example/parallel.l 	"List: '(Integer: 75025, List: '(Integer: 75025, List: nil))"

test example/scope.l 		"Integer: 1"

test example/silly_fib.l 	"List: '(Integer: 75025, List: '(Integer: 75025, List: nil))"

test example/stream.l 		"List: '(Integer: 5, List: '(Integer: 6, List: '(Integer: 7, List: nil)))"


echo
echo "[$(($run - $failed))/$run]"
#!/usr/bin/env bash
function die {
	echo "$1" >&2
	exit 1
}

for seq in {1..3}{1..3}{1..3}{1..3}{1..3}{1..3}; do
	echo -n "$seq" | ./is_galois.x >/dev/null
done

for seq in {1..3}{1..3}{1..3}{1..3}{1..3}{1..3}; do
	echo -n "$seq" | ./is_primitive.x
	[[ "$?" -eq 0 ]] && continue
	echo -n "$seq" | ./galois_rotation.x >/dev/null
done

# set -x
# set -e
for seq in {1..3}{1..3}{1..3}{1..3}{1..3}{1..3}; do
	echo -n "$seq" | ./galois_factorization.x >/dev/null
done


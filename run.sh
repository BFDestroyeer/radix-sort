#!/bin/bash

if [ $# -ne 1 ]
then
    executable_path='./build/radix-sort'
else
    executable_path=$1
fi

# Write system information

# Write header
echo '' > 'results.md'
echo '|Name|Threads count|10 000 000 items|100 000 000 items|1 000 000 000 items|' >> 'results.md'
echo '|-|-|-|-|-|' >> 'results.md'

# Run executable
$executable_path -rseq >> 'results.md'
echo '[  OK  ] Recursive seqential sort'

$executable_path -seq >> 'results.md'
echo '[  OK  ] Seqential sort'

$executable_path -thread >> 'results.md'
echo '[  OK  ] Thread sort'

mpiexec --use-hwthread-cpus $executable_path -mpi >> 'results.md'
echo '[  OK  ] MPI sort'

$executable_path -omp >> 'results.md'
echo '[  OK  ] OpenMP sort'

$executable_path -tbb >> 'results.md'
echo '[  OK  ] Intel TBB sort'

echo 'Done'

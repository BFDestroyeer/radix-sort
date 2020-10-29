if ($args.Length -eq 0)
{
    $executable_path = '.\build\Release\radix-sort.exe'
}
else
{
    $executable_path = $args[0]
}

# Write sysyem information
'' > 'results.md'

$processor = Get-WMIObject win32_Processor
$os = Get-WmiObject Win32_OperatingSystem
$os.Caption >> 'results.md'
'\' >> 'results.md'
$processor.Name >> 'results.md'

# Write header
'|Name|Threads count|10 000 000 items|100 000 000 items|1 000 000 000 items|' >> 'results.md'
'|-|-|-|-|-|' >> 'results.md'

# Run executable
& $executable_path -rseq >> 'results.md'
& $executable_path -seq >> 'results.md'
& $executable_path -thread >> 'results.md'
& mpiexec --use-hwthread-cpus $executable_path -mpi >> 'results.md'
& $executable_path -omp >> 'results.md'
& $executable_path -tbb >> 'results.md'

$executable_path
if ($args.Length -eq 0)
{
    $executable_path = '.\build\Release\radix-sort.exe'
}
else
{
    $executable_path = $args[0]
}

# Write sysyem information
Clear-Content 'results.md'
if ($Env:OS -eq 'Windows_NT')
{
    $computer_system = Get-WmiObject -class Win32_ComputerSystem
    $processor = Get-WMIObject win32_Processor
    $os = Get-WmiObject Win32_OperatingSystem
    $os.Caption >> 'results.md'
    '\' >> 'results.md'
    $processor.Name >> 'results.md'
}

# Write header
'|Name|Threads count|10 000 000 items|100 000 000 items|1 000 000 000 items|' >> 'results.md'
'|-|-|-|-|-|' >> 'results.md'

#Run executable
& $executable_path -rseq >> 'results.md'
& $executable_path -seq >> 'results.md'
& $executable_path -thread >> 'results.md'
& mpiexec -n $computer_system.numberoflogicalprocessors $executable_path -mpi >> 'results.md'
& $executable_path -omp >> 'results.md'
& $executable_path -tbb >> 'results.md'
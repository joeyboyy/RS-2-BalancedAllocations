Directory:
.           source code, CMakeLists.txt, plot.plt (helper gnuplot script)
|
|-- out     output dir of experiment executables (located in direct child directory), input dir for plot.plt
|-- plots   output dir of plot.plt

This is a CMake project. To compile the executables, create a build directory and invoke CMake as
usual. Note that the executables assume to be in a direct child directory of the root dir (this).

Execute the executables 
- BalancedAllocBatched
- BalancedAllocBatchedPartialInfo
- BalancedAllocOnline
- BalancedAllocOnlinePartialInfo
from within the build directory to populate/overwrite the experiment results in the out/ directory.

This is all needed to reproduce the results. For further processing, the gnuplot script plots.plt
can be used (adjust depending on use case) to populate/overwrite the plots/ directory.
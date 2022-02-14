# Advent of Code 2016
All days done for Advent of Code 2016 written in C++. Requires C++14 compatible compiler and cmake to build. Tested with clang, gcc and msvc.

## Compile
mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE="Release" ..

## Run
From repository root dir - run build/bin/aoc2016 to calculate results for all days.

To just run specific days it first argument is a regex to which days to calculate e.g.:

* build/bin/aoc2016 01 - will run only day 1.
* build/bin/aoc2016 "02|04" - will run day 2 and 4.

## Runtime with my input

Benchmarks are run on a Ryzen 9 5900X - single thread execution. Compiled with clang-15 on Windows 10 WSL 2.

 Day | Part | Time (s)
:---:|:----:|--------:
01|1|  .000012
01|2|  .000056
02|1|  .000024
02|2|  .000024
03|1|  .000600
03|2|  .000652
04|1|  .003084
04|2|  .001184
05|1| 7.217430
05|2|18.0351xx
06|1|  .000012
06|2|  .000009
07|1|  .000219
07|2|  .000680
08|1|  .000163
08|2|  .000149
09|1|  .000013
09|2|  .000253
10|1|  .001434
10|2|  .001605
11|1|  .000003
11|2|  .000001
12|1|  .001837
12|2|  .059379
13|1|  .000127
13|2|  .000109
14|1|  .029014
14|2|30.8656xx
15|1|  .000273
15|2|  .005487
16|1|  .000006
16|2|  .102578
17|1|  .000044
17|2|  .043089
18|1|  .000026
18|2|  .248776
19|1|  .000002
19|2|  .002082
20|1|  .000089
20|2|  .000105
21|1|  .000060
21|2|  .000049
22|1|  .004058
22|2|  .000616
23|1|  .000146
23|2| 7.87605x
24|1|  .006743
24|2|  .006658
25|1|  .018168
25|2|N/A
Total|-|64.5339

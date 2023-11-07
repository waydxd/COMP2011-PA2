#!/bin/bash
# loop from 1 to 10
g++ -std=c++11 pa2.cpp -o pa2
for x in {1..10}
do
    # run pa1 with inputx.txt and redirect output to myOutput.txt
    ./pa2 < input$x.txt > myOutput$x.txt
    # compare myOutput.txt with output.txt using diff command
    echo "Testcase $x"
    wdiff myOutput$x.txt output$x.txt
done

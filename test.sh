make
if (( $# == 0 )); then
    ./flow -q -d puzzles/regular_5x5_01.txt
    ./flow -q -d puzzles/regular_6x6_01.txt
    ./flow -q -d puzzles/regular_7x7_01.txt
    ./flow -q -d puzzles/regular_8x8_01.txt
    ./flow -q -d puzzles/regular_9x9_01.txt

    ./flow -q -d puzzles/extreme_8x8_01.txt
    ./flow -q -d puzzles/extreme_9x9_01.txt
    ./flow -q -d puzzles/extreme_9x9_30.txt
    ./flow -q -d puzzles/extreme_10x10_01.txt
    ./flow -q -d puzzles/extreme_10x10_30.txt
    ./flow -q -d puzzles/extreme_11x11_07.txt
    ./flow -q -d puzzles/extreme_11x11_15.txt
    ./flow -q -d puzzles/extreme_11x11_20.txt
    ./flow -q -d puzzles/extreme_11x11_30.txt
    ./flow -q -d puzzles/extreme_12x12_01.txt
    ./flow -q -d puzzles/extreme_12x12_02.txt
    ./flow -q -d puzzles/extreme_12x12_28.txt
    ./flow -q -d puzzles/extreme_12x12_29.txt
    ./flow -q -d puzzles/extreme_12x12_30.txt
    exit 1
fi
while getopts reai OPTION;
do
    case "$OPTION" in
        r) 
        ./flow -q -d puzzles/regular_5x5_01.txt
        ./flow -q -d puzzles/regular_6x6_01.txt
        ./flow -q -d puzzles/regular_7x7_01.txt
        ./flow -q -d puzzles/regular_8x8_01.txt
        ./flow -q -d puzzles/regular_9x9_01.txt
        exit;;
        e) 
        ./flow -q -d puzzles/extreme_8x8_01.txt
        ./flow -q -d puzzles/extreme_9x9_01.txt
        ./flow -q -d puzzles/extreme_9x9_30.txt
        ./flow -q -d puzzles/extreme_10x10_01.txt
        ./flow -q -d puzzles/extreme_10x10_30.txt
        ./flow -q -d puzzles/extreme_11x11_07.txt
        ./flow -q -d puzzles/extreme_11x11_15.txt
        ./flow -q -d puzzles/extreme_11x11_20.txt
        ./flow -q -d puzzles/extreme_11x11_30.txt
        ./flow -q -d puzzles/extreme_12x12_01.txt
        ./flow -q -d puzzles/extreme_12x12_02.txt
        ./flow -q -d puzzles/extreme_12x12_28.txt
        ./flow -q -d puzzles/extreme_12x12_29.txt
        ./flow -q -d puzzles/extreme_12x12_30.txt
        exit;;
        a)
        ./flow -q -d puzzles/regular_5x5_01.txt
        ./flow -q -d puzzles/regular_6x6_01.txt
        ./flow -q -d puzzles/regular_7x7_01.txt
        ./flow -q -d puzzles/regular_8x8_01.txt
        ./flow -q -d puzzles/regular_9x9_01.txt
        ./flow -q -d puzzles/extreme_8x8_01.txt
        ./flow -q -d puzzles/extreme_9x9_01.txt
        ./flow -q -d puzzles/extreme_9x9_30.txt
        ./flow -q -d puzzles/extreme_10x10_01.txt
        ./flow -q -d puzzles/extreme_10x10_30.txt
        ./flow -q -d puzzles/extreme_11x11_07.txt
        ./flow -q -d puzzles/extreme_11x11_15.txt
        ./flow -q -d puzzles/extreme_11x11_20.txt
        ./flow -q -d puzzles/extreme_11x11_30.txt
        ./flow -q -d puzzles/extreme_12x12_01.txt
        ./flow -q -d puzzles/extreme_12x12_02.txt
        ./flow -q -d puzzles/extreme_12x12_28.txt
        ./flow -q -d puzzles/extreme_12x12_29.txt
        ./flow -q -d puzzles/extreme_12x12_30.txt
        exit;;
        i)
        ./flow -q -d puzzles/regular_5x5_01.txt
        esac
done


#./flow -q -d puzzles/regular_5x5_01.txt
#./flow -q -d puzzles/regular_6x6_01.txt
#./flow -q -d puzzles/regular_7x7_01.txt
#./flow -q -d puzzles/regular_8x8_01.txt
#./flow -q -d puzzles/regular_9x9_01.txt


#./flow -q -d puzzles/extreme_8x8_01.txt
#./flow -q -d puzzles/extreme_9x9_01.txt
#./flow -q -d puzzles/extreme_9x9_30.txt
#./flow -q -d puzzles/extreme_10x10_01.txt
#./flow -q -d puzzles/extreme_10x10_30.txt
#./flow -q -d puzzles/extreme_11x11_07.txt
#./flow -q -d puzzles/extreme_11x11_15.txt
#./flow -q -d puzzles/extreme_11x11_20.txt
#./flow -q -d puzzles/extreme_11x11_30.txt
#./flow -q -d puzzles/extreme_12x12_01.txt
#./flow -q -d puzzles/extreme_12x12_02.txt
#./flow -q -d puzzles/extreme_12x12_28.txt
#./flow -q -d puzzles/extreme_12x12_29.txt
#./flow -q -d puzzles/extreme_12x12_30.txt

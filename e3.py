import os
tests = ["deadlock_6x6_01.txt",
"extreme_10x10_01.txt",
"extreme_10x10_30.txt",
"extreme_11x11_07.txt",
"extreme_11x11_15.txt",
"extreme_11x11_20.txt",
"extreme_11x11_30.txt",
"extreme_12x12_01.txt",
"extreme_12x12_02.txt",
"extreme_12x12_28.txt",
"extreme_12x12_29.txt",
"extreme_12x12_30.txt",
"extreme_8x8_01.txt",
"extreme_9x9_01.txt",
"extreme_9x9_30.txt",
"jumbo_10x10_01.txt",
"jumbo_11x11_01.txt",
"jumbo_12x12_30.txt",
"jumbo_13x13_26.txt",
"jumbo_14x14_01.txt",
"jumbo_14x14_02.txt",
"jumbo_14x14_19.txt",
"jumbo_14x14_21.txt",
"jumbo_14x14_30.txt",
"regular_5x5_01.txt",
"regular_6x6_01.txt",
"regular_7x7_01.txt",
"regular_8x8_01.txt",
"regular_9x9_01.txt"]


os.system("make")
for test in tests:
    os.system("./flow -q -d -r puzzles/" + test)
    
print("\n#########################################################\n")

for test in tests:
    os.system("./flow -q puzzles/" + test)
 
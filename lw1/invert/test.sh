assert_equal() {
    if diff -ew "$1" "$2" > /dev/null; then
        echo -e "\033[32mTest passed $i: $1 matches $2\033[0m"
    else
        echo -e "\033[31mTest failed $i: $1 does not match $2\033[0m"
        exit 1
    fi
}

### Ввод через файл

#1 Обычная матрица
i=1
echo "1   2   3
0   1   4
5   6   0" > ./test/input.txt
echo "-24.000   18.000    5.000
20.000    -15.000   -4.000
-5.000    4.000     1.000" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#2 Нет обратной матрицы
((i++))
echo "1  2  3
4  5  6
7  8  9" > ./test/input.txt
echo "Non-invertible" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#3 Единичная матрица
((i++))
echo "1  0  0
0  1  0
0  0  1" > ./test/input.txt
echo "1.000  0.000  0.000
0.000  1.000  0.000
0.000  0.000  1.000" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#4 Матрица с нулями
((i++))
echo "1  0  0
0  1  0
0  0  1" > ./test/input.txt
echo "1.000  0.000  0.000
0.000  1.000  0.000
0.000  0.000  1.000" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#5 Только нули
((i++))
echo "0  0  0
0  0  0
0  0  0" > ./test/input.txt
echo "Non-invertible" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#6 Матрица с отрицательными значениями
((i++))
echo "-1  -2  3
4   -5  6
-7   8  9" > ./test/input.txt
echo "-0.388	0.175	0.013
-0.325	0.050	0.075
-0.013	0.092	0.054" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#7 Некорректный ввод матрицы 3 на 3 в ширину
((i++))
echo "1 2 3
4 5 6
7 8" > ./test/input.txt
echo "Invalid matrix format" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#8 Некорректный ввод матрицы 3 на 3 в длину
((i++))
echo "1 2 3
4 5 6" > ./test/input.txt
echo "Invalid matrix format" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#9 Некорректный ввод матрицы 3 на 3, буква вместо цифры
((i++))
echo "1 2 й
4 5 6
7 8 3" > ./test/input.txt
echo "Invalid matrix format" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#10 float и int
((i++))
echo "4   7   2.3
2   1   1
3   -2  -2.31" > ./test/input.txt
echo "-0.009   0.321    0.131
0.212    -0.448   0.017
-0.194    0.806   -0.278" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#11 Пустой входной файл
((i++))
echo "" > ./test/input.txt
echo "Invalid matrix format" > ./test/expected.txt
./cmake-build-debug/invert "./test/input.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

### Ввод через stdin

#12 Обычная матрица
((i++))
echo "1   2   3
0   1   4
5   6   0" | ./cmake-build-debug/invert > ./test/output.txt
echo "-24.000   18.000    5.000
20.000    -15.000   -4.000
-5.000    4.000     1.000" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#13 Нет обратной матрицы
((i++))
echo "1  2  3
4  5  6
7  8  9" | ./cmake-build-debug/invert > ./test/output.txt
echo "Non-invertible" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#14 Единичная матрица
((i++))
echo "1  0  0
0  1  0
0  0  1" | ./cmake-build-debug/invert > ./test/output.txt
echo "1.000  0.000  0.000
0.000  1.000  0.000
0.000  0.000  1.000" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#15 Матрица с нулями
((i++))
echo "1  0  0
0  1  0
0  0  1" | ./cmake-build-debug/invert > ./test/output.txt
echo "1.000  0.000  0.000
0.000  1.000  0.000
0.000  0.000  1.000" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#16 Только нули
((i++))
echo "0  0  0
0  0  0
0  0  0" | ./cmake-build-debug/invert > ./test/output.txt
echo "Non-invertible" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#17 Матрица с отрицательными значениями
((i++))
echo "-1  -2  3
4   -5  6
-7   8  9" | ./cmake-build-debug/invert > ./test/output.txt
echo "-0.388	0.175	0.013
-0.325	0.050	0.075
-0.013	0.092	0.054" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#18 Некорректный ввод матрицы 3 на 3 в ширину
((i++))
echo "1 2 3
4 5 6
7 8" | ./cmake-build-debug/invert > ./test/output.txt
echo "Invalid matrix format" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#19 Некорректный ввод матрицы 3 на 3 в длину
((i++))
echo "1 2 3
4 5 6" | ./cmake-build-debug/invert > ./test/output.txt
echo "Invalid matrix format" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#20 Некорректный ввод матрицы 3 на 3, буква вместо цифры
((i++))
echo "1 2 й
4 5 6
7 8 3" | ./cmake-build-debug/invert > ./test/output.txt
echo "Invalid matrix format" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#21 float и int
((i++))
echo "4   7   2.3
2   1   1
3   -2  -2.31" | ./cmake-build-debug/invert > ./test/output.txt
echo "-0.009   0.321    0.131
0.212    -0.448   0.017
-0.194    0.806   -0.278" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#22 Ввод пустого значения
((i++))
echo "" | ./cmake-build-debug/invert > ./test/output.txt
echo "Invalid matrix format" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

echo -e "\033[32mAll tests passed!\033[0m"
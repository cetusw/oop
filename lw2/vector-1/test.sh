assert_equal() {
    if diff -ew "$1" "$2" > /dev/null; then
        echo -e "\033[32mTest passed $i: $1 matches $2\033[0m"
    else
        echo -e "\033[31mTest failed $i: $1 does not match $2\033[0m"
        exit 1
    fi
}

assert_differance() {
    if diff "$1" "$2" > /dev/null; then
        echo -e "\033[31mTest failed $i: $1 does not match $2\033[0m"
        exit 1
    else
        echo -e "\033[32mTest passed $i: $1 matches $2\033[0m"
    fi
}

#1 Ввод одного элемента
i=1
echo "1.0" | ./cmake-build-debug/vector-1 > ./test/output.txt
echo "2.000" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#2 Ввод элементов через пробел
((i++))
echo "1.0 2 3.659512" | ./cmake-build-debug/vector-1 > ./test/output.txt
echo "3.220 4.220 5.879" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#3 Отрицательные числа
((i++))
echo "4 16 -30 10" | ./cmake-build-debug/vector-1 > ./test/output.txt
echo "-20.000 14.000 20.000 26.000" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#4 Ввод элементов через пробелы, табуляции и переносы строк
((i++))
echo "1.0
2           3.659512

23
        34.09 0" | ./cmake-build-debug/vector-1 > ./test/output.txt
echo "12.750 13.750 14.750 16.409 35.750 46.840" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#5 Все числа отрицательные
((i++))
echo "-1.0004000 -703 -3.659512 -11" | ./cmake-build-debug/vector-1 > ./test/output.txt
echo "-703.000 -11.000 -3.660 -1.000" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#6 Нечисловой символ
((i++))
echo "- 2 3" | ./cmake-build-debug/vector-1 > ./test/output.txt
echo "ERROR" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#7 Пустой файл
((i++))
echo "" | ./cmake-build-debug/vector-1 > ./test/output.txt
echo "" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#8 Переполнение
((i++))
echo "100000000000000000000000000000000000000 100000000000000000000000000000000000000 100000000000000000000000000000000000000
100000000000000000000000000000000000000 100000000000000000000000000000000000000 100000000000000000000000000000000000000" | ./cmake-build-debug/vector-1 > ./test/output.txt
echo "ERROR" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#9 Ввод неотсортированных элементов
((i++))
echo "7.67 3.56 2344" | ./cmake-build-debug/vector-1 > ./test/output.txt
echo "788.637 792.747 3129.077" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

echo -e "\033[32mAll tests passed!\033[0m"
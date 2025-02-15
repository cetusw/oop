assert_equal() {
    if diff -q "$1" "$2" > /dev/null; then
        echo -e "\033[32mTest passed $i: $1 matches $2\033[0m"
    else
        echo -e "\033[31mTest failed $i: $1 does not match $2\033[0m"
        exit 1
    fi
}

#1 Обычный перевод
i=1
echo "31" > ./test/expected.txt
./cmake-build-debug/radix 16 10 1F > ./test/output.txt
assert_equal ./test/output.txt ./test /expected.txt

#2 Обратно
((i++))
echo "1F" > ./test/expected.txt
./cmake-build-debug/radix 10 16 31 > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#3 В двоичную
((i++))
echo "1010" > ./test/expected.txt
./cmake-build-debug/radix 10 2 10 > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#4 Из двоичной
((i++))
echo "F" > ./test/expected.txt
./cmake-build-debug/radix 2 16 1111 > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#5 Отрицательное число
((i++))
echo "-2A" > ./test/expected.txt
./cmake-build-debug/radix 10 16 -42 > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#6 Ноль
((i++))
echo "0" > ./test/expected.txt
./cmake-build-debug/radix 10 2 0 > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#7 Основание больше 36-ти из
((i++))
cout=$(./cmake-build-debug/radix 37 10 123 2>&1)
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#8 Основание больше 36-ти в
((i++))
cout=$(./cmake-build-debug/radix 10 37 12 2>&1)
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#9 Основание меньше 2-х из
((i++))
cout=$(./cmake-build-debug/radix 1 10 1 2>&1)
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#10 Основание меньше 2-х в
((i++))
cout=$(./cmake-build-debug/radix 10 1 1 2>&1)
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#11 Число не соответствует основанию
((i++))
cout=$(./cmake-build-debug/radix 10 2 ABC 2>&1)
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#12 Не указан один аргумент
((i++))
cout=$(./cmake-build-debug/radix 10 2 2>&1)
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#13 Не указан ни один аргумент
((i++))
cout=$(./cmake-build-debug/radix 2>&1)
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

echo -e "\033[32mAll tests passed!\033[0m"

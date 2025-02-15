assert_equal() {
    if diff -q "$1" "$2" > /dev/null; then
        echo -e "\033[32mTest passed $i: $1 matches $2\033[0m"
    else
        echo -e "\033[31mTest failed $i: $1 does not match $2\033[0m"
        exit 1
    fi
}

# Замена, содержащая искомую строку
i=1
echo "mama delala pelmeni" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "ma" "mama"
echo "mamamama delala pelmeni" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

# Одно вхождение в середине строки
((i++))
echo "12312312345" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "1231234" "XYZ"
echo "123XYZ5" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

# Пустая искомая строка
((i++))
echo "tut text" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "" "tam"
echo "tut text" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

# Пустая строка-заменитель
((i++))
echo "" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "hello" ""
echo "" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

# Три вхождения в середине строки
((i++))
echo "asdmamamaasd" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "ma" "mama"
echo "asdmamamamamamaasd" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

# Ошибка открытия входного файла
((i++))
if [ -r ./test/input123.txt ]; then
    cout=$(./cmake-build-debug/replace ./test/input123.txt ./test/output.txt "1231234" "rep" 2>&1)
else
    cout="ERROR"
fi
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

# Ошибка открытия выходного файла
((i++))
if [ -w ./test/output123.txt ]; then
    cout=$(./cmake-build-debug/replace ./test/input.txt ./test/output123.txt "1231234" "rep" 2>&1)
else
    cout="ERROR"
fi
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

# Ошибка открытия входного и выходного файла
((i++))
if [ -r ./test/input123.txt ] || [ -w ./test/output123.txt ]; then
    cout=$(./cmake-build-debug/replace ./test/input123.txt ./test/output123.txt "1231234" "rep" 2>&1)
else
    cout="ERROR"
fi
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

# Пустая входная строка
((i++))
echo "" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "replace" "random string"
echo "" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

# Одно вхождение в конце строки
((i++))
echo "delala pelmeni ma" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "ma" "mama"
echo "delala pelmeni mama" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

# Два вхождение в конце строки
((i++))
echo "delala pelmeni mama" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "ma" "mama"
echo "delala pelmeni mamamama" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

# Завершение программы при вводе строки-заменителя
((i++))
cout=$(echo -e "searchLine\n\cD" | ./cmake-build-debug/replace 2>&1)
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

# Завершение программы при вводе искомой строки
((i++))
cout=$(echo -e "\cD\n" | ./cmake-build-debug/replace 2>&1)
echo "ERROR" > ./test/expected.txt
echo "$cout" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

# Несколько строк во входном файле
((i++))
echo "mama delala pelmeni\nya pokushal plotno" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "ma" "mama"
echo "mamamama delala pelmeni\nya pokushal plotno" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

# Замена всей строки
((i++))
echo "hello" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "hello" "world"
echo "world" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

# Искомая строка длиннее входной строки
((i++))
echo "short" > ./test/input.txt
./cmake-build-debug/replace ./test/input.txt ./test/output.txt "longsearch" "replace"
echo "short" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

echo -e "\033[32mAll tests passed!\033[0m"

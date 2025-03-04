assert_equal() {
    if diff "$1" "$2" > /dev/null; then
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

#1 Шифрование с максимальным размером ключа
i=1
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "255"
assert_equal ./test/output.txt ./test/expected_hello_world.txt

#2 Шифрование с минимальным размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "0"
assert_equal ./test/output.txt ./test/expected_key_0.txt

#3 Шифрование с максимальным -1 размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "254"
assert_equal ./test/output.txt ./test/expected_key_254.txt

#4 Шифрование с максимальным +1 размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
echo "ERROR" > ./test/expected.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "256" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#5 Шифрование с минимальным -1 размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
echo "ERROR" > ./test/expected.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "-1" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#6 Шифрование с минимальным +1 размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "1" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected_key_1.txt

#7 Шифрование и дешифрование с максимальным размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "255"
./cmake-build-debug/crypt "decrypt" "./test/output.txt" "./test/decrypt.txt" "255"
assert_equal ./test/input.txt ./test/decrypt.txt

#8 Шифрование и дешифрование с минимальным размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "0"
./cmake-build-debug/crypt "decrypt" "./test/output.txt" "./test/decrypt.txt" "0"
assert_equal ./test/input.txt ./test/decrypt.txt

#9 Шифрование и дешифрование с максимальным -1 размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "254"
./cmake-build-debug/crypt "decrypt" "./test/output.txt" "./test/decrypt.txt" "254"
assert_equal ./test/input.txt ./test/decrypt.txt

#10 Дешифрование с максимальным +1 размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
echo "ERROR" > ./test/expected.txt
./cmake-build-debug/crypt "decrypt" "./test/input.txt" "./test/output.txt" "256" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#11 Дешифрование с минимальным -1 размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
echo "ERROR" > ./test/expected.txt
./cmake-build-debug/crypt "decrypt" "./test/input.txt" "./test/output.txt" "-1" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#12 Шифрование и дешифрование с минимальным +1 размером ключа
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "1"
./cmake-build-debug/crypt "decrypt" "./test/output.txt" "./test/decrypt.txt" "1"
assert_equal ./test/input.txt ./test/decrypt.txt

#13 Шифрование и дешифрование
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "255"
./cmake-build-debug/crypt "decrypt" "./test/output.txt" "./test/decrypt.txt" "255"
assert_equal ./test/input.txt ./test/decrypt.txt

#14 Шифрование с одним ключом и дешифрование с другим
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "255"
./cmake-build-debug/crypt "decrypt" "./test/output.txt" "./test/decrypt.txt" "1"
assert_differance ./test/input.txt ./test/decrypt.txt

#15 Сначала дешифруем, а потом шифруем
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "decrypt" "./test/input.txt" "./test/output.txt" "255"
./cmake-build-debug/crypt "encrypt" "./test/output.txt" "./test/decrypt.txt" "255"
assert_equal ./test/input.txt ./test/decrypt.txt

#16 Шифрование программы
((i++))
./cmake-build-debug/crypt "encrypt" "./cmake-build-debug/crypt" "./cmake-build-debug/crypt1" "255"
./cmake-build-debug/crypt "decrypt" "./cmake-build-debug/crypt1" "./cmake-build-debug/crypt2" "255"
sudo chmod +x ./cmake-build-debug/crypt2
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt2 "encrypt" "./test/input.txt" "./test/output.txt" "255"
assert_equal ./test/output.txt ./test/expected_hello_world.txt

#17 Неверное количество параметров
((i++))
echo "Hello, World!" > ./test/input.txt
echo "ERROR" > ./test/expected.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#18 Неправильное значение cryptMode
((i++))
echo "Hello, World!" > ./test/input.txt
echo "ERROR" > ./test/expected.txt
./cmake-build-debug/crypt "blabla" "./test/input.txt" "./test/decrypt.txt" "23" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#19 Несуществующий файл
((i++))
echo "Hello, World!" > ./test/input.txt
echo "ERROR" > ./test/expected.txt
./cmake-build-debug/crypt "encrypt" "./test/inputblabla.txt" "./test/output.txt" "23" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#20 Нечисловое значение key
((i++))
echo "Hello, World!" > ./test/input.txt
echo "ERROR" > ./test/expected.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "blabla" > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#21 Программа запускается без параметров
((i++))
echo "Hello, World!" > ./test/input.txt
echo "ERROR" > ./test/expected.txt
./cmake-build-debug/crypt > ./test/output.txt
assert_equal ./test/output.txt ./test/expected.txt

#22 Шифруем пустой файл
((i++))
touch ./test/empty.txt
./cmake-build-debug/crypt "encrypt" "./test/empty.txt" "./test/output.txt" "255"
assert_equal ./test/output.txt ./test/empty.txt

#23 Файл с одним символом
((i++))
echo "A" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output.txt" "255"
assert_equal ./test/output.txt ./test/expected_one_char.txt

#24 Повторное шифрование
((i++))
echo "Hello, World!" > ./test/input.txt
./cmake-build-debug/crypt "encrypt" "./test/input.txt" "./test/output1.txt" "123"
./cmake-build-debug/crypt "encrypt" "./test/output1.txt" "./test/output2.txt" "123"
./cmake-build-debug/crypt "decrypt" "./test/output2.txt" "./test/decrypt1.txt" "123"
./cmake-build-debug/crypt "decrypt" "./test/decrypt1.txt" "./test/decrypt2.txt" "123"
assert_equal ./test/input.txt ./test/decrypt2.txt

echo -e "\033[32mAll tests passed!\033[0m"
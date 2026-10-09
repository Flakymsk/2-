#!/bin/bash
gcc ../utils.c func.c main.c -o program -lm
echo -e "Hello 123 World!\nC programming 2026.\n#$\nNoNewlineEnd 99" > input.txt

echo "=== ЗАПУСК ТЕСТОВ ==="

./program -d input.txt
echo "Результат -d:"
cat out_input.txt
echo "----------------"

./program -i input.txt
echo "Результат -i:"
cat out_input.txt
echo "----------------"

./program -s input.txt
echo "Результат -s:"
cat out_input.txt
echo "----------------"

./program -a input.txt
echo "Результат -a:"
cat out_input.txt
echo "----------------"

./program -nd input.txt custom.txt
echo "Результат -nd:"
cat custom.txt

rm -f input.txt out_input.txt custom.txt

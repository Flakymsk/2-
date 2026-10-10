gcc ../utils.c func.c main.c -o program -lm

echo -e "0001A\n101\n00000\nFF" > input.txt

echo "=== ЗАПУСК ТЕСТОВ ==="

./program input.txt output.txt
echo "Результат обработки:"
cat output.txt
echo "----------------"

rm -f input.txt output.txt program

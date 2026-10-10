gcc -fsanitize=address -g ../utils.c func.c main.c -o program -lm

echo "=== ЗАПУСК ТЕСТОВ ==="

echo "Результат -h для 25:"
./program 25 -h
echo "----------------"

echo "Результат -p для 17:"
./program 17 -p
echo "----------------"

echo "Результат -s для 255:"
./program 255 -s
echo "----------------"

echo "Результат -e для 3:"
./program 3 -e
echo "----------------"

echo "Результат -a для 5:"
./program 5 -a
echo "----------------"

echo "Результат -f для 5:"
./program 5 -f
echo "----------------"

echo "Результат -e для ошибки (11):"
./program 11 -e
echo "----------------"
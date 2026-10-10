gcc ../utils.c func.c main.c -o program -lm

echo "=== ЗАПУСК ТЕСТОВ ==="

./program 1 50

rm -f program
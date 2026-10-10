gcc ../utils.c func.c main.c -o program -lm

echo "=== ЗАПУСК ТЕСТОВ ==="

echo -e "FF\n10\nStop" | ./program 16

rm -f program

gcc ../utils.c func.c main.c -o program -lm

echo "=== ЗАПУСК АВТОТЕСТОВ ==="
./program -1 0 0 0 2 2 2 2 0
./program -2 2.0 5.0 2.0 3.0 4.0
./program -4 2.0 4.0 8.0
./program -5 2.0 -3
./program -6 -1.0 1.0 0.0001
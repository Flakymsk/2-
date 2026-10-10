gcc ../utils.c func.c main.c -o program -lm

echo -e "Привет 123 Мир!\nC programming 2026.\n#$\nNoNewlineEnd 99" > input.txt

echo "=== ЗАПУСК ТЕСТОВ ДЛЯ ЗАДАЧИ 4 ==="

./program -d input.txt
echo "Результат -d (с кириллицей):"
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

./program -nd input.txt ./input.txt > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Тест защиты путей: ОК (перезапись заблокирована)"
else
    echo "Тест защиты путей: ФЕЙЛ (уязвимость к перезаписи файла!)"
fi
echo "----------------"

rm -f input.txt out_input.txt program

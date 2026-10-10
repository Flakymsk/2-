
gcc ../utils.c func.c main.c -o program -lm

echo -e "word1\tword3\nword5" > file1.txt
echo -e "word2 word4\tword6 word7" > file2.txt
echo "A B C D E F G H I J" > file_a.txt

echo "=== ЗАПУСК ТЕСТОВ ДЛЯ ЗАДАЧИ 7 ==="

./program -r file1.txt file2.txt out_r.txt
echo "Результат -r:"
cat out_r.txt
echo -e "\n----------------"

./program -a file_a.txt out_a.txt
echo "Результат -a:"
cat out_a.txt
echo -e "\n----------------"

./program -a file_a.txt ./file_a.txt > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Тест одинаковых файлов: ОК (перезапись заблокирована)"
else
    echo "Тест одинаковых файлов: ФЕЙЛ (уязвимость к затиранию!)"
fi
echo "----------------"

rm -f file1.txt file2.txt file_a.txt out_r.txt out_a.txt program

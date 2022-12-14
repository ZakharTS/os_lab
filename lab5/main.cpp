#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/* Вариант 9. Написать программу, которая получает со стандартного потока ввода
содержимое любого текстового файла и выводит в стандартный поток вывода строки,
начинающиеся на гласную букву, а в поток ошибки – порядковый номер выведенной строки.

 Протестировать на различных файлах с использованием конвейеров в различных комбинациях
вашей программы и команд cat, sort, head, tail.

 В текущем каталоге создайте два файла, в один из которых выводите
нечетные, а во второй - четные строки, начинающиеся на согласную букву.*/

int main() {
    // part 1
    char curChar = ' ';
    int strNumber = 0;
    size_t sizeRead = 1;
//    while (sizeRead) {
//        strNumber++;
//        sizeRead = read(0, &curChar, 1);
//        if (!sizeRead) return -1;
//
//        if (curChar != 'a' && curChar != 'A' && curChar != 'e' && curChar != 'E' && curChar != 'i' && curChar != 'I'
//            && curChar != 'o' && curChar != 'O' && curChar != 'u' && curChar != 'U' && curChar != 'y' &&
//            curChar != 'Y') {
//            for (; curChar != '\n';) {
//                sizeRead = read(0, &curChar, 1);
//            }
//            continue;
//        }
//        char str[256];
//        str[0] = curChar;
//        int i = 1;
//        for (; curChar != '\n'; i++) {
//            sizeRead = read(0, &curChar, 1);
//            str[i] = curChar;
//        }
//        write(1, str, i);
//        char strNumChar[256];
//        int strNumCharSize = sprintf(strNumChar, "%d\n", strNumber);
//        write(2, strNumChar, strNumCharSize);
//    }

    // part 2
    int f1 = open("file1", O_WRONLY | O_CREAT, 0666), f2 = open("file2", O_WRONLY | O_CREAT, 0666);

    while (sizeRead) {
        strNumber++;
        sizeRead = read(0, &curChar, 1);
        if (!sizeRead) return -1;

        if (((curChar >= 64 && curChar <= 90) || (curChar >= 97 && curChar <= 122)) &&
            (curChar != 'a' && curChar != 'A' && curChar != 'e' && curChar != 'E' && curChar != 'i' && curChar != 'I'
             && curChar != 'o' && curChar != 'O' && curChar != 'u' && curChar != 'U' && curChar != 'y' &&
             curChar != 'Y')) {
            char str[256];
            str[0] = curChar;
            int i = 1;
            for (; curChar != '\n'; i++) {
                sizeRead = read(0, &curChar, 1);
                str[i] = curChar;
            }
            if (strNumber % 2 == 1) {
                write(f1, str, i);
            }
            if (strNumber % 2 == 0) {
                write(f2, str, i);
            }
        } else {
            for (; curChar != '\n';) {
                sizeRead = read(0, &curChar, 1);
            }
        }
    }

    return 0;
}

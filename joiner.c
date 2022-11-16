#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char * argv[]) {
	FILE *f1, *f2;	//дескрипторы файлов
	char buf;	//буфер для символов
	char stars[5]= {'*','*','*','*','*'}; 	//разделитель файлов
	f1 = fopen(argv[2], "wb");	//открываем архив для записи
	f2 = fopen(argv[1], "rb");	//открываем распаковщик для чтения
	printf("writing unpacker...\n");
	while(!feof(f2))	//цикл до конца файл
	{
		if(fread(&buf, 1, sizeof(buf), f2)>0)	//чтение из файла
			fwrite(&buf, sizeof(buf), 1, f1);	//пишем в файл
	}
	fclose(f2); //закрываем распоковщик
	fwrite(&stars, sizeof(stars), 1, f1); //пишем разделитель
	f2 = fopen(argv[3], "rb");	//открываем первый файл для чтения
	printf("writing first file...\n");
	while(!feof(f2))	//цикл до конца файл
	{
		if(fread(&buf, 1, sizeof(buf), f2)>0)	//чтение из файла
			fwrite(&buf, sizeof(buf), 1, f1);	//пишем в файл
	}
	fclose(f2);	//закрываем первый файл
	fwrite(&stars, sizeof(stars), 1, f1);	//пишем разделитель
	f2 = fopen(argv[4], "rb");	//открываем второй файл для чтения
	printf("writing second file...\n");
	while(!feof(f2))	//цикл до конца файл
	{
		if(fread(&buf, 1, sizeof(buf), f2)>0)	//чтение из файла
			fwrite(&buf, sizeof(buf), 1, f1);	//пишем в файл
	}
	fclose(f2);	//закрываем второй файл
	fclose(f1);	//закрываем архив
	printf("complite!");
	getchar();	//ожидание нажатия Enter
	return EXIT_SUCCESS;	//завершение программы
}

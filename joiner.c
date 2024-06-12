#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char crypt(char key, char data)
{
	return data^key;
}

int main(int argc, char * argv[]) {
	FILE *f1, *f2;	//дескрипторы файлов
	char buf;	//буфер для символов
	char buf1 = 'f';
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
	fclose(f1); //закрываем архив
	for(int i = 0; i<argc-2;i++)
	{
		f1 = fopen(argv[2], "ab");
		fwrite(&stars, sizeof(stars), 1, f1); //пишем разделитель
		buf1 = (int)(atoi(argv[5+i*3])); //пишем атрибуты(запуск после распаковки, режим отображения, ..?)
		fwrite(&buf1, 1, 1, f1);
		fwrite(argv[4+i*3], 10, 1, f1); //пишем имя первого файла
		fwrite(&stars, sizeof(stars), 1, f1); //пишем разделитель
		f2 = fopen(argv[3+i*3], "rb");	//открываем первый файл для чтения
		printf("writing file number %d...\n", i+1);
		buf1='f';
		while(!feof(f2))	//цикл до конца файл
		{
			if(fread(&buf, 1, sizeof(buf), f2)>0)	//чтение из файла
			{
				buf1=buf;
				fwrite(&buf1, sizeof(buf), 1, f1);	//пишем в файл
			}
		}
		printf("file number %d wrote\n", i+1);
		fclose(f2);	//закрываем первый файл
		fclose(f1);	//закрываем архив
	}
	printf("complite!");
	getchar();	//ожидание нажатия Enter
	return EXIT_SUCCESS;	//завершение программы
}
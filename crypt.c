#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>
void rad_pas(char* password, int len_pas) //генерация случайного пароля из определенного набора символов
{
    if(password==NULL) return;
    char set[]="qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789";
    size_t n=sizeof(set)-1;
    for(size_t i=0;i<len_pas;i++)
    {
        int rand_index=rand()%n;
        password[i]=set[rand_index];
    }
    password[len_pas]='\0';
}
void crypty(char* data,char* cr, size_t len_data, const char* key) //функция для шифрования и дешифрования XOR
{
    if(data==NULL) return;
    if(cr==NULL) return;
    if(key==NULL) return;
    size_t len_pas=strlen(key);
    if(len_pas!=0)
    {
        for(size_t i=0;i<len_data;i++)
        {
            cr[i]=data[i]^key[i%len_pas];
        }
    }
}
int main()
{
    setlocale(LC_ALL,"");
    char FilePath[MAX_PATH],message[4096],password_1[100],password_2[100];
    char shifr[4096];
    char data_ex[4096],decrypt[4096];
    char saved_password[100]="";
    int Result=0,choice=0;
    size_t ResSize_t=0,n=0;
    char way[100]="";
    srand(time(NULL));
    FILE* f;
    printf("Введите название файла\n");
    if(scanf(" %[^\n]",FilePath)!=1){
        printf("Ошибка ввода названия файла");
        return 1;
    }
    printf("1 - зашифровать данные\n2 - расшифровать данные\n3 - забыл пароль\n4 - выход\n");
    if(scanf("%d",&choice)!=1){
        printf("Ошибка ввода действия");
        return 2;
    }
    switch(choice)
    {
    case 1:
        printf("Введите сообщение: ");
        if(scanf(" %[^\n]",message)!=1){
            printf("Ошибка ввода сообщения");
            return 3;
        }
        size_t len_mes=strlen(message);
        if(len_mes>=sizeof(message))
        {
            printf("Превышение возможного размера сообщения");
            return 4;
        }
        f=fopen(FilePath,"w");
        if(f==NULL)
        {
            printf("Ошибка открытия файла: %s",FilePath);
            return 5;
        }
        Result=fprintf(f,"%s",message);
        if(Result<0)
        {
            printf("Ошибка записи сообщения в файл");
            return 6;
        }
        rad_pas(password_1,16);
        printf("Ваш пароль для будущей расшифровки данных: %s\n",password_1);
        Result=fclose(f);
        if(Result!=0)
        {
            printf("Ошибка закрытия файла");
            return 7;
        }
        f=fopen("password.txt","w");
        if(f==NULL)
        {
            printf("Ошибка открытия файла"); 
            return 8;
        }
        Result=fprintf(f,"%s",password_1);
        if(Result<0)
        {
            printf("Ошибка записи пароля");
            return 9;
        }
        Result=fclose(f);
        if(Result!=0)
        {
            printf("Ошибка закрытия файла");
            return 10;
        }
        crypty(message,shifr,len_mes,password_1); 
        f=fopen("new.txt","wb");
        if(f==NULL)
        {
            printf("Ошибка открытия файла");
            return 11;
        }
        Result=fwrite(shifr,sizeof(shifr[0]),len_mes,f); //записали зашифрованные данные в новый файл
        if(Result!=len_mes)
        {
            printf("Ошибка записи зашифрованных данных");
            return 12;
        }
        for(size_t i=0;i<len_mes;i++)
        {
            printf("%02X ",(unsigned char)shifr[i]); //вывели зашифрованные данные
        }
        Result=fclose(f);
            if(Result!=0)
            {
                printf("Ошибка закрытия файла");
                return 13;
            }
        break;
    case 2:
        printf("\nВведите пароль для расшифровки данных:\n");
        if(scanf("%s",password_2)!=1){
            printf("Ошибка ввода пароля для дешифровки");
            return 14;
        }
        f=fopen("password.txt","rb");
        if(f==NULL)
        {
            printf("Ошибка открытия файла");
            return 15;
        }
        if(fgets(saved_password,sizeof(saved_password),f) == NULL)
        {
            printf("Ошибка чтения пароля\n");
            fclose(f);
            return 16;
        }
        Result=fclose(f);  
        size_t len = strlen(saved_password);
        if(len > 0 && saved_password[len-1] == '\n')
            saved_password[len-1] = '\0';
        if(strcmp(saved_password, password_2) == 0)
        {
            f=fopen("new.txt","rb");
            if(f==NULL)
            {
                printf("Ошибка открытия файла");
                return 17;
            }
            n=sizeof(data_ex)/sizeof(data_ex[0]);
            ResSize_t=fread(data_ex,sizeof(data_ex[0]),n,f); //считали зашифрованные данные из файла
            if(ResSize_t==0)
            {
                printf("Ошибка чтения зашифрованных данных из файла");
                return 18;
            }
            Result=fclose(f);
            if(Result!=0)
            {
                printf("Ошибка закрытия файла");
                return 19;
            }
            f=fopen("decrypt.txt","wb");
            if(f==NULL)
            {
                printf("Ошибка открытия файла");
                return 20;
            }
            crypty(data_ex,decrypt,ResSize_t,password_2); //расшифровали данные
            Result=fwrite(decrypt,sizeof(decrypt[0]),ResSize_t,f);
            if(Result!=ResSize_t)
            {
                printf("Ошибка записи расшифрованных данных");
                return 21;
            }
            printf("Расшифрованные данные (HEX):\n");
            for(size_t i=0;i<ResSize_t;i++)
            {
                printf("%02X ",(unsigned char) decrypt[i]);
            }
            printf("\n\nРасшифрованные данные (текст):\n");
            for(size_t i=0;i<ResSize_t;i++){
                printf("%c", (unsigned char) decrypt[i]);
            }
            printf("\n");
            Result=fclose(f);
            if(Result!=0)
            {
                printf("Ошибка закрытия файла");
                return 22;
            }
        }
        else
        {
            printf("Ошибка ввода неверного пароля");
            return 23;
        }
        break;
    case 3:
        printf("Введите метод, который использовался для шифрования");
        if(scanf("%s",way)!=1){
            printf("Ошибка ввода метода шифрования");
            return 24;
        }
        if(strcmp(way, "XOR") == 0 || strcmp(way, "xor") == 0)
        {
            f=fopen("password.txt","r");
            if(f != NULL)
            {
                if(fgets(saved_password, sizeof(saved_password),f)==NULL)
                {
                    fclose(f);
                    break;
                }
                Result=fclose(f);
                if(Result!=0)
                {
                    printf("Ошибка закрытия файла");
                    return 25;
                }
                size_t len = strlen(saved_password);
                if(len > 0 && saved_password[len-1] == '\n')
                    saved_password[len-1] = '\0';
                printf("Ваш пароль: %s\n", saved_password);
            }
            else
            {
                printf("Файл с паролем не найден. Сначала зашифруйте данные.\n");
                return 26;
            }
        }
        else
        {
            printf("Ошибка: неизвестный метод шифрования\n");
            return 27;
        }
        break;

    case 4:
        printf("Для завершения работы программы нажмите Enter");
        while(getchar()!='\n');  
        getchar();  
        break;
    default:
        printf("Неверный выбор режима");
        return 28;
    }
        return 0;
} 
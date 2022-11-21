#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

#define folderDirectory "C:/KittyCat/"
#define folderCatData "C:/KittyCat/CatData"
#define fileCatID "C:/KittyCat/CatID"

void create_folder()
{
    mkdir(folderDirectory);
}

// struct of cat
struct cat
{
    int id;
    char name[20];
    float weight;
    char type[20];
    int sex;         // 0-female or 1-male
    int vaccination; // 1 yes- 0 not
};

typedef struct cat CAT;

void SubId()
{
    int fileID;
    FILE *fptr;
    fptr = fopen(fileCatID, "rb");
    fscanf(fptr, "%d", &fileID);
    fileID -= 1;
    fclose(fptr);
    fptr = fopen(fileCatID, "wb");
    fprintf(fptr, "%d", fileID);
    fclose(fptr);
}

int GenerateIdCat()
{
    int fileID;
    FILE *fptr;
    if ((fptr = fopen(fileCatID, "rb")) == NULL)
    {
        int id = 1;
        fptr = fopen(fileCatID, "wb");
        fprintf(fptr, "%d", id);
        fclose(fptr);

        return 1;
    }
    else
    {
        fscanf(fptr, "%d", &fileID);
        fileID += 1;
        fclose(fptr);
        fptr = fopen(fileCatID, "wb");
        fprintf(fptr, "%d", fileID);
        fclose(fptr);

        return fileID;
    }
}

void CreateCat()
{

    CAT x;
    char check;
    int CatId = GenerateIdCat();
    char dir[20] = folderCatData;
    FILE *fptr;
    if ((fptr = fopen(dir, "ab")) == NULL)
    {
        printf("Error opening/creating file!!\n");
        exit(0);
    }

    puts("\t\t\t==============================");
    puts("\t\t\t     Create a new Kitty  ");
    puts("\t\t\t==============================");
    puts("\t\t\t* * * * * * * * * * * * * * * *");
    // input data of cat
    printf("\nInput your kitty: ");
    fflush(stdin);
    gets(x.name);
    printf("\nInput the weight of your kitty: ");
    fflush(stdin);
    scanf("%f", &x.weight);
    fflush(stdin);
    printf("\nInput the type of your kitty: ");
    gets(x.type);
    fflush(stdin);
    printf("\nInput the sex of your kitty (0-female or 1-male): ");
    scanf("%d", &x.sex);
    while (x.sex != 0 && x.sex != 1)
    {
        printf("\nInvalid option, re-input the sex of your kitty");
        scanf("%d", &x.sex);
    }
    printf("\nInput the vaccination of your kitty (1-yes or 0-not): ");
    scanf("%d", &x.vaccination);
    while (x.vaccination != 0 && x.vaccination != 1)
    {
        printf("\nInvalid option, re-input the vaccination of your kitty");
        scanf("%d", &x.vaccination);
    }
    x.id = CatId;
    // output data of cat you entered
    system("cls");
    printf("\nYour information of kitty that you have entered:");
    printf("\n*********************************************");
    printf("\nKitty name: %s", x.name);
    printf("\nKitty ID %d", x.id);
    printf("\nKitty weight: %.1f", x.weight);
    printf("\nKitty type: %s", x.type);
    if (x.sex)
    {
        printf("\nThe sex of your kitty: male");
    }
    else
    {
        printf("\nThe sex of your kitty: female");
    }
    if (x.vaccination)
    {
        printf("\nYour kitty is vaccinated");
    }
    else
    {
        printf("\nYour kitty is not vaccinated");
    }
    printf("\n*********************************************");
    printf("\nDo you want to save this kitty(Y/N): ");
SAVE:
    do
    {
        scanf("%s", &check);
        switch (check)
        {
        case 'y':
        case 'Y':
            fwrite(&x, sizeof(x), 1, fptr);
            printf("\nKitty is saved");
            fclose(fptr);
            break;
        case 'n':
        case 'N':
            printf("Kitty is not saved");
            SubId();
            break;
        default:
            printf("Invalid option, re-input your option");
            goto SAVE;
            break;
        }
        break;
    } while (1);
    printf("\nDo you want to re-input a new cat(Y/N): ");
REINPUT:
    do
    {
        scanf("%s", &check);
        if (check == 'y' || check == 'Y')
        {
            system("cls");
            CreateCat();
        }
        else if (check == 'n' || check == 'N')
        {
            break;
        }
        else
        {
            goto REINPUT;
        }

    } while (1);
}

void UI_Menu()
{
    // demo UI
    while (1)
    {
        puts("\t\t\t==============================");
        puts("\t\t\t     WELCOME TO THE SHOP  ");
        puts("\t\t\t==============================");
        puts("\t\t\t* * * * * * * * * * * * * * * *");
        puts("\t\t\t1. Manage Cat\n\n\t\t\t2. Manage Products\n\n\t\t\t3. Your Cart\n\n\t\t\t4. Manage Finance\n\n\t\t\t5. Manage Client\n\n\t\t\t6. Exit");
        printf("\t\t\tSelect your choice  ");
        int u;
        scanf("%d", &u);
        if (u == 1)
        {
            printf("Your choice is 1");
            exit(0);
        }
        else if (u == 2)
        {
            printf("Your choice is 2");
            exit(0);
        }
        else if (u == 3)
        {
            printf("Your choice is 3");
            exit(0);
        }
        else if (u == 4)

        {
            printf("Your choice is 4");
            exit(0);
        }
        else if (u == 5)
        {
            printf("Your choice is 5");
            exit(0);
        }
        else if (u == 6)
        {
            printf("exit");
            exit(0);
        }
        else
        {
            puts("Invalid option. Please select one of the available options");
        }
    }
}

int main()
{
    create_folder();
    // UI_Menu();
    CreateCat();
    return 0;
}

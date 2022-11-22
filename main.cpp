#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

#define folderDirectory "C:/KittyCat/"
#define fileCatData "C:/KittyCat/CatData"
#define fileProductData "C:/KittyCat/ProductData"
#define fileCatID "C:/KittyCat/CatID"
#define fileProductID "C:/KittyCat/ProductID"

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

struct product
{
    int id;
    char name[20];
    int quantity;
    char expiry[20];
    unsigned int price;
};

typedef struct product Pdt;

void SubId(int opt)
{
    //! opt 1- cat, opt 2- product
    int fileID;
    FILE *fptr;
    fptr = fopen(opt == 1 ? fileCatID : fileProductID, "rb");
    fscanf(fptr, "%d", &fileID);
    fileID -= 1;
    fclose(fptr);
    fptr = fopen(opt == 1 ? fileCatID : fileProductID, "wb");
    fprintf(fptr, "%d", fileID);
    fclose(fptr);
}

int GenerateId(int opt)
{
    //! opt 1- cat, opt 2- product
    int fileID;
    FILE *fptr;
    if ((fptr = fopen(opt == 1 ? fileCatID : fileProductID, "rb")) == NULL)
    {
        int id = 1;
        fptr = fopen(opt == 1 ? fileCatID : fileProductID, "wb");
        fprintf(fptr, "%d", id);
        fclose(fptr);

        return 1;
    }
    else
    {
        fscanf(fptr, "%d", &fileID);
        fileID += 1;
        fclose(fptr);
        fptr = fopen(opt == 1 ? fileCatID : fileProductID, "wb");
        fprintf(fptr, "%d", fileID);
        fclose(fptr);

        return fileID;
    }
}

void CreateProduct()
{
    Pdt x;
    char check;
    int productId = GenerateId(2);
    char dir[30] = fileProductData;
    FILE *fptr;
    if ((fptr = fopen(dir, "ab")) == NULL)
    {
        printf("Error opening/creating file!!\n");
        exit(0);
    }

    puts("\t\t\t==============================");
    puts("\t\t\t     Create a new Product  ");
    puts("\t\t\t==============================");
    puts("\t\t\t* * * * * * * * * * * * * * * *");
    // input data of cat
    printf("\nInput your product: ");
    fflush(stdin);
    gets(x.name);
    printf("\nInput the price of your product: ");
    fflush(stdin);
    scanf("%u", &x.price);
    while (x.price <= 0)
    {
        printf("\nInvalid value of price, please re-input it");
        scanf("%u", &x.price);
    }
    printf("\nInput the quantity of your product: ");
    scanf("%d", x.quantity);
    while (x.quantity < 0)
    {
        printf("\nInvalid value of quantity, please re-input it");
        scanf("%d", &x.quantity);
    }
    fflush(stdin);
    printf("\nInput the expiry of your product: ");
    gets(x.expiry);
    x.id = productId;
    fflush(stdin);
    // output data of product you entered
    system("cls");
    printf("\nYour information of product that you have entered:");
    printf("\n*********************************************");
    printf("\nProduct name: %s", x.name);
    printf("\nProduct ID %d", x.id);
    printf("\nProduct price: %d VND", x.price);
    printf("\nProduct quantity: %d", x.quantity);
    printf("\nProduct expiry: %s", x.expiry);
    printf("\n*********************************************");
    printf("\nDo you want to save this product(Y/N): ");
SAVE:
    while (1)
    {
        scanf("%c", &check);
        switch (check)
        {
        case 'y':
        case 'Y':
            fwrite(&x, sizeof(x), 1, fptr);
            printf("\nProduct is saved");
            fclose(fptr);
            break;
        case 'n':
        case 'N':
            printf("\nProduct is not saved");
            SubId(2);
            break;
        default:
            printf("\nInvalid option, re-input your choice: ");
            scanf("%c", &check);
            goto SAVE;
            break;
        }
        break;
    }
    fflush(stdin);
    printf("\nDo you want to re-input a new product(Y/N): ");
    char reInput;
REINPUT:
    while (1)
    {
        scanf("%c", &reInput);
        switch (reInput)
        {
        case 'y':
        case 'Y':
            system("cls");
            CreateProduct();
            break;
        case 'n':
        case 'N':
            break;
        default:
            printf("\nInvalid option, re-input your choice: ");
            scanf("%c", &reInput);
            break;
        }
        break;
    }
}

void CreateCat()
{

    CAT x;
    char check;
    int CatId = GenerateId(1);
    char dir[20] = fileCatData;
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
    fflush(stdin);
    printf("\n*********************************************");
    printf("\nDo you want to save this kitty(Y/N): ");
SAVE:
    while (1)
    {
        scanf("%c", &check);
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
            printf("\nKitty is not saved");
            SubId(1);
            break;
        default:
            printf("\nInvalid option, re-input your option: ");
            scanf("%c", &check);
            goto SAVE;
            break;
        }
        break;
    }
    fflush(stdin);
    printf("\nDo you want to re-input a new cat(Y/N): ");
    char reInput;
REINPUT:
    while (1)
    {
        scanf("%c", &reInput);
        switch (reInput)
        {
        case 'y':
        case 'Y':
            system("cls");
            CreateCat();
            break;
        case 'n':
        case 'N':
            break;
        default:
            printf("\nInvalid option, re-input your choice: ");
            scanf("%c", &reInput);
            goto REINPUT;
            break;
        }
        break;
    }
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
    // CreateProduct();
    CreateCat();
    return 0;
}

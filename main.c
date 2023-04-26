#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Enum representing gender type
 */
typedef enum {
    male,
    female,
    undefined
} tGender;

/**
 * @brief Struct representing one record in binary file.
 */
typedef struct{
    char name[100];
    char surname[100];
    int age;
    tGender gender;
}tRecord;

/**
 * @brief This function creates new record on dynamic memory. Moreover, the record is filled with data proceed as parameters.
 * @param name
 * @param surname
 * @param age
 * @param gender  @sa tGender
 * @return pointer to a new tRecord
 */
tRecord * generateRecord(const char * const name, const char * const surname, const int age, const tGender gender){
    tRecord *zaznam = malloc(sizeof(tRecord));
    strcpy(zaznam->name, name);
    strcpy(zaznam->surname, surname);
    zaznam->age = age;
    (*zaznam).gender = gender;
    return zaznam;
}

/**
 * This function converst the gender (tGender) to a EN string
 * @param g The gender to be converted
 * @return String representation of the gender.
 */
const char * genderToString(const tGender g){
    switch (g) {
        case male: return "male";
        case female: return "female";
        case undefined: return "undefined";
        default: return "N/A";
    }
}

/**
 * @brief This function print out the one record to the standard output.
 * @param record The record to be printed.
 */
void printRecord(const tRecord * const record){
    printf("Name: %s\n"
           "Surname: %s\n"
           "Gender: %s\n"
           "Age: %i\n", record->name, record->surname, genderToString(record->gender), record->age
           );
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Funce main.
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int main() {

    /************************************************************
     * Ukázka práce s textovým souborem v režimu přidávání      *
     ************************************************************/
    int testValue = 10;
    FILE * fp = fopen("text.txt", "a");
    if (fp != NULL){
        fprintf(fp, "Hello world!!\n");
        fprintf(fp, "Value: %i\n", testValue);
        fprintf(fp, "%i\n", testValue);
        fclose(fp);
        fp = NULL;
    }
    /************************************************************
     * Ukázka práce s textovým souborem v režimu čtení          *
     ************************************************************/
    fp = fopen("text.txt", "r");
    if (fp != NULL){
        char c;
        while(1) {
            c = fgetc(fp);
            if( feof(fp) ) {
                break ;
            }
            printf("%c", c);
        }
        fclose(fp);
        fp = NULL;
    }

    /************************************************************
     * Ukázka práce s binárním souborem v režimu zápisu         *
     ************************************************************/
    const tRecord * const p1 = generateRecord("Karel", "Novak", 35, male);
    const tRecord * const p2 = generateRecord("Valerie", "Novakova",34, female );
    const tRecord * const p3 = generateRecord("Ales", "Vlcek", 21, undefined);

    fp = fopen("data.bin", "wb");
    if (fp != NULL ){
        fwrite(p1, sizeof(tRecord), 1, fp);
        fwrite(p2, sizeof(tRecord), 1, fp);
        fwrite(p3, sizeof(tRecord), 1, fp);
        fclose(fp);
        fp = NULL;
    }
    free(p1);
    free(p2);
    free(p3);

    /************************************************************
     * Ukázka práce s binárním souborem v režimu čtení          *
     ************************************************************/
    fp = fopen("data.bin", "rb");
    if (fp != NULL){
        tRecord record;
        while (!feof(fp)){
            fread(&record, sizeof (tRecord), 1 ,fp);
            printRecord(&record);
        }
        fclose(fp);
        fp = NULL;
    }

    return 0;
}

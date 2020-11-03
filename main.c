#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void create_bin_file_integer(char* file_name, int num){
  int r;
  FILE* file_out = fopen(file_name, "wb");
  for(int i = 0;i<num;i++){
    r = rand()%100;
    fwrite(&r, sizeof(int), 1, file_out);
  }
  fclose(file_out);

}

void reader_bin_file_integer(char* file_name){
  FILE* file_in = fopen(file_name, "rb");
  if(!file_in){
    printf("Error: Read operation");
    exit(1);
  }
  int numbers;
  printf("\nReading file . . . %s \n", file_name);
  while(fread(&numbers, sizeof(int), 1, file_in)){
    printf("%d\n", numbers);
  }
  fclose(file_in);
}

void remove_ext(char *s){
    int size_str = strlen(s);
    s[size_str-4]='\0';
}

void convert_txt_file_to_bin_file(char* file_name_txt){
  FILE* file_txt = fopen(file_name_txt, "r");
  char bin_extension_name[9] = "BIN_CVRT";
  char bin_file_name[30];

  strcpy(bin_file_name, file_name_txt);
  remove_ext(bin_file_name);
  strcat(bin_file_name, bin_extension_name);

  FILE* bin_file = fopen(bin_file_name, "wb");

  int numbers;

  while(fscanf(file_txt, "%d", &numbers) != EOF){
    fwrite(&numbers, sizeof(int), 1, bin_file);
  }
  fclose(bin_file);
  fclose(file_txt);

  printf("\nReading converted file: \n");
  reader_bin_file_integer(bin_file_name);
  printf("CONVERSION COMPLETED . . .");

}
int main()
{   srand(time(NULL));
    char s[30];
    int op;
    int num;
    printf("Do you want to create a new bin file, read an existing bin file or convert a txt file to a bin file?\n");
    printf("1- Create\n");
    printf("2- Read\n");
    printf("3 - Convert\n");
    scanf("%d", &op);
    if(op == 1){
      printf("Enter the file name: ");
      scanf("%s", s);
      printf("Enter the number of elements in the file to be created: ");
      scanf("%d",&num);
      create_bin_file_integer(s, num);
    }else if(op == 2){
      printf("Enter the file name: ");
      scanf("%s", s);
      reader_bin_file_integer(s);
    }else if(op == 3){
      printf("Enter the file name: ");
      scanf("%s", s);
      convert_txt_file_to_bin_file(s);
    }
    else{
      printf("\nError! Invalid operation!\n");
    }

    return 0;
}

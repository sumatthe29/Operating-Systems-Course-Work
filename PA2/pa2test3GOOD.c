#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

FILE * readdoc(FILE * p, char* file) // int noc
{
    p = fopen(file,"r");
    // will reiterate 
    while(1)
    {
        printf("Enter the number of bytes you want to read: ");
        // char* input = (char*) malloc(1024);
        char input[10];
        
        if((fgets(input, 10, stdin) != NULL))
        {
            // needed an int check for fgets 
            // for (int i = 0; i < strlen(input); i++)
            // {
            //     if (isdigit(input[i]) == 0)
            //     {
            //         // printf("Correct");
            //         continue;
            //     }
            // }
            
            int noc = atoi(input);
            // printf("%d", noc);
            // printf("%s, %d",file, noc);
            char* bf = (char*) malloc(noc);
            int i = noc;
            //read(fp, &bf, noc);
            //fgets(bf,noc,fp);

            int f = fread(bf,noc,1,p);
            // printf("%d",f);

            // bf[strcspn(bf, "\n")] = 0;
            // if (feof(p)){
            //     printf("%s", bf);
                   
            // }
            // else{printf("%s\n",bf);}
            //fflush(stdout);
            fprintf(stdout,"%s\n",bf);

            
            free (bf);
            // fclose(p); 
            
            // free (input);
            break;
        }

        // ctrl d detected, close file and exit from function with code 0
        else
        {
            fclose(p);
            printf("\n");
            exit(0);

        }
    }
    return p;

}



FILE * writedoc(FILE * p, char* file)
{
    p = fopen(file, "w");
    // int p = open(file,O_WRONLY);
    // will reiterate 
    while(1)
    {
        printf("Enter the string you want to write: ");
        // char* input = (char*) malloc(1024);
        char input[1024];
        
        if((fgets(input, 1024, stdin) != NULL))
        {
            //fputs(input,p);
            //write(p,input,strlen(input));
            fwrite(input,1,strlen(input),p);
            fflush(p);
            // fclose(p);
            break;
        }

        // ctrl d detected, close file and exit from function with code 0
        else
        {
            fclose(p);
            printf("\n");
            exit(0);

        }
    }
 return p;

}

// void seekdoc()
// {
    
//     // will reiterate 
                    // while(1)
                    // {
                    //     printf("Enter an offest value: ");
                    //     // char* input = (char*) malloc(1024);
                    //     char offset[10];
                        
                    //     if((fgets(offset, 10, stdin) != NULL))
                    //     {
                            
                    //         int off = atoi(offset);
                    //         char seek[1];
                    //         printf("Enter a value for whence (0 for SEEK_SET, 1 for SEEK_CUR, 2 for SEEK_END): ");
                    //         if(fgets(seek, 1, stdin) != NULL)
                    //         {
                    //             int sk = atoi(seek);
                    //             fseek(fp,off,sk);

                    //         }
                    //         else
                    //         {
                    //             fclose(fp);
                    //             printf("\n");
                    //             exit(0);

                    //         }
                            
                    //         break;
                    //     }

                    //     // ctrl d detected, close file and exit from function with code 0
                    //     else
                    //     {
                    //         fclose(fp);
                    //         printf("\n");
                    //         exit(0);

                    //     }
                    // }

// }

int main(int argc, char* argv[]) {

    //char fn[100], *file;
    //file = fgets(fn,100,stdin);
    //scanf("%s", &fn);

    char* file = argv[1];
    // printf("%s\n", file);

    FILE* fp;
    fp = fopen(file, "a+");

    // if file is read/writable and valid start menu sequence

    if(!fp) 
    {
        printf("file DNE or restricted access, exit program\n");
        // return nonzero status
        return 255;
    }

    //if (fp){

    // fclose(fp);

        // open close handled by each function, allows for control of specific ops and consistant reference
        // which had issues when passed as a value. 
        // behaviour more closely resembles lab example, read/write pointer behaviour improves
        char* buffer = (char*) malloc(1024);
        printf("Option (r for read, w for write, s for seek): ");

        while(1){
            
            
            // if input is not recieved as eops

            if (fgets(buffer, 1024, stdin) == NULL)
            {
                // fclose(fp);
                printf("\n");
                break;
            }
            
                int noc; 
                switch(*buffer) {
                    case 'r' :
                    // fp = fopen(file, "r");

                    // will reiterate 
                    while(1)
                    {
                        printf("Enter the number of bytes you want to read: ");
                        // char* input = (char*) malloc(1024);
                        char input[10];
                        
                        if((fgets(input, 10, stdin) != NULL))
                        {
    
                            
                            int noc = atoi(input);
                            // printf("%d", noc);
                            // printf("%s, %d",file, noc);
                            char* bf = (char*) malloc(noc);
                            int i = noc;
                            //read(fp, &bf, noc);
                            //fgets(bf,noc,fp);

                            int f = fread(bf,noc,1,fp);
                            
                            fflush(stdout);
                            fprintf(stdout,"%s\n",bf);

                            
                            free (bf);
                            
                            break;
                        }

                        // ctrl d detected, close file and exit from function with code 0
                        else
                        {
                            fclose(fp);
                            printf("\n");
                            exit(0);

                        }
                    }
                    printf("Option (r for read, w for write, s for seek): ");
                    break;    
                    case 'w' :
                    // fp = fopen(file, "a");
                    //int p = open(file,O_APPEND);
                    // will reiterate 
                    while(1)
                    {
                        printf("Enter the string you want to write: ");
                        // char* input = (char*) malloc(1024);
                        char input[1024];
                        
                        if((fgets(input, 1024, stdin) != NULL))
                        {
                            //strncpy(input,input,strlen(input)-1);
                            //fputs(input,p);
                            
                            input[strlen(input)-1] = '\0';
                            //write(p,strcat(input,"\0"),strlen(input)+1);
                            fwrite(strcat(input,"\0"),1,strlen(input)+1,fp);
                            fflush(fp);
                            // fclose(p);
                            break;
                        }

                        // ctrl d detected, close file and exit from function with code 0
                        else
                        {
                            fclose(fp);
                            printf("\n");
                            exit(0);

                        }
                    }
                
                    printf("Option (r for read, w for write, s for seek): ");
                    // printf("selected w\n");
                    break;
                    case 's' :
                    // will reiterate 
                    
                        printf("Enter an offest value: ");
                        // char* input = (char*) malloc(1024);
                        char offset[10];
                        
                        if((fgets(offset, 10, stdin) != NULL))
                        {
                            
                            int off = atoi(offset);
                            char seek[2];
                            printf("Enter a value for whence: ");
                            // (0 for SEEK_SET, 1 for SEEK_CUR, 2 for SEEK_END):
                            if(fgets(seek, 2, stdin) != NULL)
                            {
                                int sk;
                                //fseek(fp,off,sk);
                                //printf("sucess");
                                //break;

                                switch(*seek) {
                                case '0' :
                                sk = atoi(seek);
                                fseek(fp,off,SEEK_SET);
                                //printf("sucess");
                                break;    
                                case '1' :
                                sk = atoi(seek);
                                fseek(fp,off,SEEK_CUR);
                                //printf("sucess");
                                break;
                                case '2' :
                                sk = atoi(seek);
                                fseek(fp,off,SEEK_END);
                                //printf("sucess");
                                break;
                                default :
                                printf("./pa2test error: seek failed\n");
                                exit(255);
                                continue; 


                            }

                            }
                            else
                            {
                                fclose(fp);
                                printf("\n");
                                exit(0);

                            }
                            
                            break;
                        }

                        // ctrl d detected, close file and exit from function with code 0
                        else
                        {
                            fclose(fp);
                            printf("\n");
                            exit(0);

                        }
                    
                    default :
                    printf("Option (r for read, w for write, s for seek): ");
                    continue; 


                }
            
            // printf("Choice: %s", buffer);
            //memset(buffer,0,1024);
        }

        // fclose(fp);


         
        free(buffer);
        return 0;
}


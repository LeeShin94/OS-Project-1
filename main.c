#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define CHUNK 9128


 int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char buffer[CHUNK];
        //char    string[] = "Hello, world!\n";
        char    readbuffer[CHUNK];
        //char ch;

        //count words
        int count = 0, c = 0, i, j = 0, k, space = 0;
        char p[1000][512], str1[512], ptr1[1000][512];
        char *ptr;

        pipe(fd);

        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* child process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                while(read(fd[0], readbuffer,sizeof(readbuffer)) != 0){

                    //printf("%s",readbuffer);
                    for (i = 0;i<strlen(readbuffer);i++){
                        if ((readbuffer[i] == ' ')||(readbuffer[i] ==',')||(readbuffer[i] == '.')){
                            space++;
                        }
                    }
                    for (i=0,j=0,k=0;j<strlen(readbuffer);j++){
                        if ((readbuffer[j]==' ')||(readbuffer[j] == 44)||(readbuffer[j] == 46)){
                            p[i][k] = '\0';
                            i++;
                            k = 0;
                        }else{
                            p[i][k++] = readbuffer[j];
                        }
                    }
                    k = 0;
                    for(i=0;i<= space;i++){
                        for(j=0;j<=space;j++){
                            if(i==j){
                                strcpy(ptr1[k],p[i]);
                                k++;
                                count++;
                                break;
                            }else{
                                if(strcmp(ptr1[j],p[i])!=0)
                                    continue;
                                else
                                    break;
                            }
                        }
                    }
                    for (i=0;j<=space;j++){
                        for(j=0;j<space;j++){
                            if(strcmp(ptr1[i],p[j]) ==0)
                                c++;
                        }
                        printf("%s %d times\n",ptr1[i],c);
                        c=0;
                    }
                }
                /*
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);*/


        }
        else
        {
                /* parent process closes up input side of pipe */
                close(fd[0]);

                FILE *fp;

                fp = fopen("ANNA.txt", "r");

                if(fp ==NULL){
                    perror("open error\n");
                    exit(EXIT_FAILURE);
                }
                while (fgets(buffer, sizeof(buffer), fp) != NULL){
                    //printf("%s", buffer);
                    write(fd[1], buffer, CHUNK);
                }
                fclose(fp);


                /*while((ch = fgetc(fp)) != EOF){
                    //printf("%c", ch);


                }*/

                /* Send "string" through the output side of pipe */
                //write(fd[1], string, (strlen(string)+1));
                exit(0);
        }

        return(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <assert.h>
#define MAXWORDLEN 128

const char* findWhitespace(const char* text)
    {
        while (*text && !isspace(*text))
            text++;
        return text;
    }

    const char* findNonWhitespace(const char* text)
    {
        while (*text && isspace(*text))
            text++;
        return text;
    }

    typedef struct tagWord
    {
        char word[MAXWORDLEN + 1];
        int count;
    } Word;

    typedef struct tagWordList
    {
        Word* words;
        int count;
    } WordList;

    WordList* createWordList(unsigned int count);

    void extendWordList(WordList* wordList, const int count)
    {
        Word* newWords = (Word*)malloc(sizeof(Word) * (wordList->count + count));
        if (wordList->words != NULL) {
            memcpy(newWords, wordList->words, sizeof(Word)* wordList->count);
            free(wordList->words);
        }
        for (int i = wordList->count; i < wordList->count + count; i++) {
            newWords[i].word[0] = '\0';
            newWords[i].count = 0;
        }
        wordList->words = newWords;
        wordList->count += count;
    }

    void addWord(WordList* wordList, const char* word)
    {
        assert(strlen(word) <= MAXWORDLEN);
        extendWordList(wordList, 1);
        Word* wordNode = &wordList->words[wordList->count - 1];
        strcpy(wordNode->word, word);
        wordNode->count++;
    }

    Word* findWord(WordList* wordList, const char* word)
    {
        for(int i = 0; i < wordList->count; i++) {
            if (strcmp(word, wordList->words[i].word) == 0) {
                return &wordList->words[i];
            }
        }
        return NULL;
    }

    void updateWordList(WordList* wordList, const char* word)
    {
        Word* foundWord = findWord(wordList, word);
        if (foundWord == NULL) {
            addWord(wordList, word);
        } else {
            foundWord->count++;
        }
    }

    WordList* createWordList(unsigned int count)
    {
        WordList* wordList = (WordList*)malloc(sizeof(WordList));
        if (count > 0) {
            wordList->words = (Word*)malloc(sizeof(Word) * count);
            for(unsigned int i = 0; i < count; i++) {
                wordList->words[i].count = 0;
                wordList->words[i].word[0] = '\0';
            }
        }
        else {
            wordList->words = NULL;
        }
        wordList->count = count;
        return wordList;
    }

    /*void printWords(WordList* wordList)
    {
        for (int i = 0; i < wordList->count; i++) {
            printf("%s: %d\n", wordList->words[i].word, wordList->words[i].count);
        }
    }*/

    int compareWord(const void* vword1, const void* vword2)
    {
        Word* word1 = (Word*)vword1;
        Word* word2 = (Word*)vword2;
        return strcmp(word1->word, word2->word);
    }

    void sortWordList(WordList* wordList)
    {
        qsort(wordList->words, wordList->count, sizeof(Word), compareWord);
    }

int main()
{
    int fd[2],bfd[2];
    pid_t childpid;
    char string[1024];
    char readbuffer[4096];
    char recreadbuffer[4096];

    pipe(fd);
    pipe(bfd);

    if((childpid = fork()) == -1){
        perror("fork");
        exit(1);
    }

    if(childpid == 0){
        close(fd[1]);
        close(bfd[0]);

        while(read(fd[0], readbuffer, sizeof(readbuffer))>0){
            //printf("%s",readbuffer);
            WordList   *wordList = createWordList(0);
            Word       *foundWord = NULL;
            const char *beg = findNonWhitespace(readbuffer);
            const char *end;
            char       word[MAXWORDLEN];

            while (beg && *beg) {
                end = findWhitespace(beg);
                if (*end) {
                    assert(end - beg <= MAXWORDLEN);
                    strncpy(word, beg, end - beg);
                    word[end - beg] = '\0';
                    updateWordList(wordList, word);
                    beg = findNonWhitespace(end);
                }
                else {
                    beg = NULL;
                }
            }

            sortWordList(wordList);
            //printWords(wordList);
            for (int i = 0; i < wordList->count; i++) {
                //printf("%s: %d\n", wordList->words[i].word, wordList->words[i].count);
                write(bfd[1],wordList->words[i].word,strlen(wordList->words[i].word));
                char buffer[50];
                int n = sprintf(buffer," : %d ",wordList->words[i].count);
                write(bfd[1],buffer,n);
                //char num = (char)wordList->words[i].count;
                //write(bfd[1],&wordList->words[i].count,sizeof(wordList->words[i].count));

            }

        }
        //close(fd[0]);
        //close(bfd[1]);
    }else{
    //parent

    close(fd[0]); //close input side of pipe
    close(bfd[1]);
    FILE * file;
    file = fopen("ANNA.txt", "r");
    if (file) {
        while (fgets(string, sizeof(string), file)!= NULL){
            write(fd[1], string, (strlen(string)));
            if(read(bfd[0], recreadbuffer, sizeof(recreadbuffer))>0){
                printf("%s",recreadbuffer);
            }


        }
        fclose(file);

        //close(fd[1]);
        //close(bfd[0]);
        //wait(0);
    }


    }
    return 0;
}

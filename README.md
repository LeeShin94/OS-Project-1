# OS-Project-1-1 pipe
1. We produced this ptoject in the Code::Blocks IDE environment. The txt file should be put in the same folder where main.c located in.
2. Two pipes(fd and bfd) were created for two-way conversation between child and parent.The parent reads the file line by line and send them to the child process. The child process then calls function described in the main.c file and send the content to perform word count.The words are seperated by the white space.
3. Count each unique word in ANNA.txt file, the time consumed was 87 seconds.
4. We used structure to store list of each word's frequency and its content. The child sent the counted results to parent and printed out on screen.

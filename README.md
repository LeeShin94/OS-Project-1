# OS-Project-1-1 pipe
1.	We produced this project in the Code::Blocks IDE environment. It uses gcc compiler. The txt file should be put in the same folder where main.c located in.
2.	Two pipes (fd and bfd) were created for two-way conversation between child and parent. The parent reads the file line by line and send them to the child process. The child process then calls function described in the main.c file and send the content to perform word count. The output of word count will then be sent back to the parent and printed on terminal screen.
3.	Count each unique word in ANNA.txt file, the time consumed was 78 seconds. The method we used to count words is two structs: one to save the entire word list and the other one to save the current word for comparison.

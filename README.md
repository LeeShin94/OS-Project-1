# OS-Project-1-1 pipe
1.	We produced this project in the Code::Blocks IDE environment. It uses gcc compiler. The txt file should be put in the same folder where main.c located in.
2.	Two pipes (fd and bfd) were created for two-way conversation between child and parent. The parent reads the file line by line and send them to the child process. The child process then calls function described in the main.c file and send the content to perform word count. The output of word count will then be sent back to the parent and printed on terminal screen.
3.	Count each unique word in ANNA.txt file, the time consumed was 78 seconds. The method we used to count words is two structs: one to save the entire word list and the other one to save the current word for comparison.
4.	If compared to message queue, creating pipes are easier but not too flexible. We have to use two pipes for two-way communication, while message queues only require two methods to send and receive messages. However, message queues spent way more time for data to go back and forth if the amount of data is too big. Another thing troubled us is to determine the message to be taken from the message queue. We noticed that messages removed from the queue are no longer available, making it harder to perform receive and send messages in a single process.
5.	Hadoop is a map reduce programming developed by Apache Software Foundation. The importance of Hadoop may come from the development of web search engines. It acts as a great help for search result return automation. Its feature of low cost and fast response is what we think that draws many people’s attention.
6.	Shared memory may be the most efficient way based on its structure. Although we did not successfully create a shared memory word count, we did try our best to look for information about this area. 

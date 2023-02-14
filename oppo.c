// #include "types.h"
// #include "stat.h"
// #include "user.h"

// #define MSGSIZE 8

// int main(void)
// {
// 	toggle(); 
// 	printf(1,"%s\n","IPC Test case");
	
// 	int cid = fork();
// 	if(cid==0){
// 		// This is child
// 		char *msg = (char *)malloc(MSGSIZE);
// 		int stat=-1;
// 		while(stat==-1){
// 			stat = recv(msg);
// 			// stat = recv(&myid ,&from, msg);
// 		}
// 		printf(1,"2 CHILD: msg recv is: %s \n", msg );
// 		exit();
// 	}else{
// 		// This is parent
// 		char *msg_child = (char *)malloc(MSGSIZE);
// 		msg_child = "PQER";
// 		printf(1,"1 PARENT: msg sent is: %s \n", msg_child );
// 		send(getpid(),cid,msg_child);	
// 		free(msg_child);
// 	}
// 	wait();
// 	exit();
// }


#include "types.h"
#include "stat.h"
#include "user.h"

#define MSGSIZE 8

int main(int argc, char const *argv[]) {
  int pid;
  int processes = 5;  // 1 parent, 4 child
  int thread_ids[8] = {-1};  // -1 means illegal pid
  int parent = getpid();
  int tid = 0;

  for (int i = 1; i < processes; i++) {
    tid = i;
    pid = fork();
    if (pid == 0) {
      // child process
      break;
    } else {
      thread_ids[i - 1] = pid;
      tid = 0;
    }
  }
  if (pid == 0) {
    // child process (receive)
    char *msg = (char *)malloc(MSGSIZE);
    int stat = -1;
    while(stat == -1){
      stat = recv(msg);
    }
    printf(1,"%s %d \n", msg, tid);
    // printf(1,"CHILD: message received is %s %d \n", msg, tid);
    exit();
  } else {
    // parent process (send)
    char *msg_child = (char *)malloc(MSGSIZE);
    msg_child = "@";
    printf(1,"%s %d \n", msg_child, tid);
    // printf(1,"PARENT: message sent is %s %d \n", msg_child, tid);
    send_multi(parent, thread_ids, msg_child);
    free(msg_child);
  }

  for (int i = 1; i < processes; i++) {
	wait();
  }
  exit();
  return 0;
}

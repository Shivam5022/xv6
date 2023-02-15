#include "types.h"
#include "stat.h"
#include "user.h"

volatile float mean = -1;

int min (int x, int y) {
	if (x < y) return x;
	return y;
}

void printfloat(float xx)
{
  int beg=(int)(xx);
  int fin=(int)(xx*100)-beg*100;
  printf(1, "%d.%d", beg, fin);
}

int
main(int argc, char *argv[])
{
	if(argc != 3){
		printf(1,"Need type and input filename\n");
		exit();
	}
	char *filename;
	filename = argv[2];
	int type = atoi(argv[1]);
	printf(1,"Type is %d and filename is %s\n",type, filename);

	int tot_sum = 0;	

	int size = 1000;
	short arr[size];
	char c;
	int fd = open(filename, 0);
	for(int i=0; i<size; i++){
		read(fd, &c, 1);
		arr[i]=c-'0';
		read(fd, &c, 1);
	}	
  	close(fd);
  	// this is to supress warning
  	printf(1,"first elem %d\n", arr[0]);

	float variance = 0.0;
  
  	//----FILL THE CODE HERE for unicast sum

	int child_processes = 7; // between 1 and 8
	if (child_processes < 1 || child_processes > 8) {
		printf(1,"Child Processes should be between 1 to 8.\n");
		exit();
	}
	int rec_pids[8] = {-1}; // -1 means illegal
	int coordinator = getpid();
	int pid, tid = -1;
	for (int i = 0; i < child_processes; i++) {
		tid = i;
		pid = fork();

		if (pid == 0) {
			// child process
			break;
		} else {
			// parent process
			tid = -1;
			rec_pids[i] = pid;
		}
	}

	// parent (co-ordinator) has tid = -1, rest have tid = 0, 1, 2, 3.....
	int divide = size / child_processes;

	if (divide * child_processes != size) {
		++divide;
	}

	if (pid == 0) {
		// it is child process, it will send its partial sum to parent
		int partial_sum = 0;

		for (int i = tid * divide; i < min(size, (1 + tid) * divide); i++) {
			partial_sum += arr[i];
		}

		send(getpid(), coordinator, &partial_sum);
		if (type == 0) {
			exit();
			// in type 0 nothing to do more so exit
		}
	} else {
		// it is parent process, it will collect partial sums from children
		int aux = 0;
		int S = 0;
		while (aux < child_processes) {
			int *msg = (int *)malloc(8);
			int stat = -1;
			while (stat == -1) {
				stat = recv(msg);
			}

			S += *msg;
			++aux;
		}

		tot_sum = S;

		if (type == 1) {
			mean = tot_sum / (1.0 * size);
			float temp = mean;
			send_multi(coordinator, rec_pids, &temp);
		}
	}

	if (type == 1) {
		if (pid == 0) {  // child msg receiving multicasts
			while (mean == -1) {
				float *msg = (float *)malloc(8);
				int stat = -1;
				while (stat == -1) {
					stat = recv(msg);
				}
				mean = *msg;

				if (mean >= 0) break;
			}

			float partial_var = 0.0;

			for (int i = tid * divide; i < min(size, (1 + tid) * divide); i++) {
				partial_var += (mean - arr[i]) * (mean - arr[i]);
			}

			send(getpid(), coordinator, &partial_var);
			exit();
			// work done, now exit it
		}
		float V = 0.0;
		int aux = 0;
		while (aux < child_processes) {
			float *msg = (float *)malloc(8);
			int stat = -1;
			while (stat == -1) {
				stat = recv(msg);
			}

			V += *msg;
			++aux;
		}

		variance = V / (1.0 * size);

	}

  	//------------------

  	if(type==0){ //unicast sum
		printf(1,"Sum of array for file %s is %d\n", filename,tot_sum);
	}

	if (type == 1) {
		printf(1,"Var of array for file %s is ", filename);
		printfloat(variance);
		printf(1, "\n");
	}

	for (int i = 0; i < child_processes; i++) {
		wait();
	}
	exit();
}

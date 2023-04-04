

// normal 3645
// edf 4365

#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstate.h"

int main(int argc, char *argv[])
{   
    int f = 10;
    
    int num_procs = 3;
    int deadline_value[3] = {30, 24, 21};
    int exectime[3] = {5, 6, 4};

    int parent_pid = getpid();

    // Set the scheduling policy to EDF
    deadline(parent_pid, f * 19);
    exec_time(parent_pid, f * 4);
    sched_policy(parent_pid, 0);


    for(int i = 0; i < num_procs; i++)
    {
        int cid = fork();
        if (cid != 0)
        {
            // rate(cid, f * rate_value[i]);
            deadline(cid, f * deadline_value[i]);
            exec_time(cid, f * exectime[i]);
            sched_policy(cid, 0);
        }
        else
        {
            /*The XV6 kills the process if th exec time is completed*/
            while(1) {
                
            }
        }
    }

    while(1) {

    }
}



// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "pstate.h"

// int main(int argc, char *argv[])
// {   
//     int num_procs = 2;
//     int Rate[2] = {21, 11};
//     int exectime[2] = {1, 2};

//     int parent_pid = getpid();

//     // Set the scheduling policy to RM
//     rate(parent_pid, 1);
//     exec_time(parent_pid, 10);
//     sched_policy(parent_pid, 1);


//     // 453

//     for(int i = 0; i < num_procs; i++)
//     {
//         int cid = fork();
//         if (cid != 0)
//         {
//             // Set the scheduling policy to RM
//             rate(cid, Rate[i]);
//             exec_time(cid, exectime[i]);
//             sched_policy(cid, 1);
//         }
//         else
//         {
//             /*The XV6 kills the process if the exec time is completed*/
//             while(1) {
                
//             }
//         }
//     }

//     while(1) {

//     }
// }
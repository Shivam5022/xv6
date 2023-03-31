
// https://github.com/asafch/xv6-scheduling/tree/22ce8e98fb1fdacc5a341d75008f8a914f5c8ec7


// normal 3645
// edf 4365

#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstate.h"

int main(int argc, char *argv[])
{   
    int num_procs = 3;
    int Deadline[3] = {7, 24, 15};
    int exectime[3] = {5, 6, 4};

    int parent_pid = getpid();

    printf(1, "og_pid: %d \n", parent_pid);

    // Set the scheduling policy to EDF
    deadline(parent_pid, 11);
    exec_time(parent_pid, 4);
    sched_policy(parent_pid, 0);

    for(int i = 0; i < num_procs; i++)
    {
        int cid = fork();
        if (cid != 0)
        {
            // Set the scheduling policy to EDF
            deadline(cid, Deadline[i]);
            exec_time(cid, exectime[i]);
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
//     int Rate[2] = {5, 25};
//     int exectime[2] = {50, 100};

//     int parent_pid = getpid();

//     // Set the scheduling policy to RM
//     rate(parent_pid, 15);
//     exec_time(parent_pid, 200);
//     sched_policy(parent_pid, 1);

//     // printf(1, "%d %d %d \n", data->pid[0], data->state[0], data->sched_policy[0]);
//     // printf(1, "%d %d %d \n", data->pid[1], data->state[1], data->sched_policy[1]);
//     // printf(1, "%d %d %d \n", data->pid[2], data->state[2], data->sched_policy[2]);

//     //   pid   prio
//     //    3     2
//     //    4     3
//     //    5     1

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
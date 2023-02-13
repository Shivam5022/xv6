#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "communication.h"

void
setup(struct msgQueue* Q) {
  Q->front = 0;
  Q->last  = 0;
}

void
insert(struct msgQueue* Q,struct message* n) {
  n->next = 0;
  
  if(Q->last == 0) {
    Q->front = Q->last = n;
    return;
  }

  Q->last->next = n;
  Q->last = n;

}

struct message*
remove(struct msgQueue* Q) {

  if(Q->front==0) {
    return 0;
  }

  struct message* m = Q->front;
  Q->front = Q->front->next;

  if(Q->front == 0) {
    Q->last = 0;
  }

  return m;  
}
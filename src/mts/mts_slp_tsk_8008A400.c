#include "linker.h"
#include "mts_new.h"

extern int gTaskIdx_800C0DB0;
extern mts_task gTasks_800C0C30[];
extern int gMts_active_task_idx_800C13C0;
extern int gMts_bits_800C0DB4;

extern void SwEnterCriticalSection_8009954C(void);
extern void SwExitCriticalSection_8009956C(void);
extern int ChangeTh_800994EC(int thread);

void mts_slp_tsk_8008A400()
{
    mts_task *pTask;          // $a1
    int bitMask;              // $a0
    int task_idx;             // $v1
    int bChangeThreadContext; // $v0
    int rCount;
    SwEnterCriticalSection_8009954C();

    pTask = &gTasks_800C0C30[gTaskIdx_800C0DB0];
    rCount = pTask->field_C_ref_count;
    if (rCount > 0)
    {
        pTask->field_0_state = 3;
        gMts_bits_800C0DB4 |= 1 << gTaskIdx_800C0DB0;
    }
    else
    {
        pTask->field_0_state = 4;
        gMts_bits_800C0DB4 &= ~(1 << gTaskIdx_800C0DB0);
    }
    bitMask = 1;
    task_idx = 0;
    pTask->field_C_ref_count = 0;
    gMts_active_task_idx_800C13C0 = -1;
    for (task_idx = 0; task_idx < 12; task_idx++)
    {
        if ((gMts_bits_800C0DB4 & bitMask) != 0)
        {
            break;
        }
        bitMask *= 2;
    }

    gMts_active_task_idx_800C13C0 = task_idx;
    if (task_idx == gTaskIdx_800C0DB0)
    {
        bChangeThreadContext = 0;
    }
    else
    {
        bChangeThreadContext = 1;
        gTaskIdx_800C0DB0 = task_idx;
    }

    if (bChangeThreadContext)
    {
        ChangeTh_800994EC(gTasks_800C0C30[gTaskIdx_800C0DB0].field_18_tcb);
    }
    SwExitCriticalSection_8009956C();
}
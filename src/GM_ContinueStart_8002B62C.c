#include "linker.h"
#include "Script_tbl_map_8002BB44.h"

// force GP
extern int                  GM_LoadRequest_800AB3D0;
int SECTION(".sdata")       GM_LoadRequest_800AB3D0;

extern GameState_800B4D98   gGameState_800B4D98;

void                        GM_CallSystemCallbackProc_8002B570(int id, int arg);
void                        GCL_RestoreVar_80021488(void);
void                        sub_8002B600(int);

void GM_ContinueStart_8002B62C()
{
    int total_continues; // $s2
    int current_stage;   // $s1

    GM_CallSystemCallbackProc_8002B570(1, 0);
    total_continues = gGameState_800B4D98.field_AE_total_continues;
    current_stage = gGameState_800B4D98.field_0C_current_stage;
    GCL_RestoreVar_80021488();
    if (gGameState_800B4D98.field_0C_current_stage != current_stage)
    {
        GM_LoadRequest_800AB3D0 = 1;
    }
    else
    {
        sub_8002B600(-1);
    }

    gGameState_800B4D98.field_AE_total_continues = total_continues + 1;

    // Set the bomb to no less than 10 seconds to prevent instant death
    // note: casting needed to produce sltiu and lhu vs lh
    if ((unsigned int)(unsigned short)gGameState_800B4D98.field_4A_item_states[eTIMER_B] - 1 < 9)
    {
        gGameState_800B4D98.field_4A_item_states[eTIMER_B] = 10;
    }
}
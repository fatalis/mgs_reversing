#include "rifle.h"
#include "Script_tbl_map_8002BB44.h"

// PSG1

extern char aRifle_0[];     // = "rifle"
extern GameState_800B4D98   gGameState_800B4D98;
extern short                dword_800B7800[];

extern void                 GM_FreeObject_80034BF8(OBJECT *object);
extern int                  sd_set_cli_800887EC(int sdCode, int unused);
extern void                 GV_DestroyOtherActor_800151D8(struct Actor *pActorToKill);
extern int                  GV_StrCode_80016CCC(const char *string);
extern void                 GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void                 GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);

#pragma INCLUDE_ASM("asm/Weapon/rifle_act_helper_80067BFC.s")
#pragma INCLUDE_ASM("asm/Weapon/rifle_act_80067D60.s")

void rifle_kill_80068118(Actor_Rifle *rifle)
{
	GM_FreeObject_80034BF8(&rifle->f20_obj);
	if (gGameState_800B4D98.field_1C_equipped_weapon != 9)
	{
		dword_800B7800[4] = 0x140;
	}
	sd_set_cli_800887EC(0x1ffff21, 0);
	if ((Actor*)rifle->f5c)
	{
		GV_DestroyOtherActor_800151D8((Actor*)rifle->f5c);
	}
}

int rifle_loader_80068184(Actor_Rifle *actor_rifle, OBJECT *parent_obj, int num_parent)
{
    OBJECT *obj = &actor_rifle->f20_obj;
    
    int id = GV_StrCode_80016CCC(aRifle_0);
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, id, 0x6d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    actor_rifle->f5c = 0;
    
    return 0;
}

#pragma INCLUDE_ASM("asm/Weapon/NewRifle_80068214.s")

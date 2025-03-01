#include "aam.h"

// stinger

extern char aStinger_0[]; // = "stinger"
extern char aAamC[];      // = "aam.c"
extern short dword_800AB9EC;
extern short dword_800ABA2C;

extern int GV_StrCode_80016CCC(const char *string);
extern void GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void GM_FreeObject_80034BF8(OBJECT *obj);
extern void GV_DestroyOtherActor_800151D8(struct Actor *pActorToKill);
extern void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);

extern void aam_act_800670CC(int param_1);

#pragma INCLUDE_ASM("asm/Weapon/aam_act_800670CC.s")

void aam_kill_800673B0(Actor_Aam *actor)
{
    GM_FreeObject_80034BF8(&actor->f20_obj);
    if (actor->f5c)
    {
        GV_DestroyOtherActor_800151D8(actor->f5c);
    }
}

int aam_loader_800673F0(Actor_Aam *actor_aam, OBJECT *parent_obj, int num_parent)
{
    OBJECT *obj = &actor_aam->f20_obj;
    
    int id;
    actor_aam->f5c = 0;
    
    id = GV_StrCode_80016CCC(aStinger_0);
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, id, 0x6d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}

Actor_Aam *NewAAM_80067480(int a1, OBJECT *parent_object, int num_parent, int a4, int a5)
{
    Actor_Aam *actor_aam = (Actor_Aam*)GV_NewActor_800150E4(6, sizeof(Actor_Aam));
    if (actor_aam)
    {
        GV_SetNamedActor_8001514C(&actor_aam->field_0_actor, (TActorFunction)aam_act_800670CC, (TActorFunction)aam_kill_800673B0, aAamC);
        if (aam_loader_800673F0(actor_aam, parent_object, num_parent) < 0)
        {
            GV_DestroyActor_800151C8(&actor_aam->field_0_actor);
            return 0;
        }

        actor_aam->f44 = a1;
        actor_aam->parent_object = parent_object;
        actor_aam->num_parent = num_parent;
        actor_aam->f50 = a4;
        actor_aam->f54 = a5;
        actor_aam->f58 = 0;
    }
    
    dword_800ABA2C = 0;
    dword_800AB9EC = 0;
    
    return actor_aam;
}

#include <util/idaTypes.h>
#include "game.h"

extern void		face_item_helper_80060CB8(WORD *in, WORD *out);
extern int		GV_StrCode_80016CCC(const char* string );
extern WORD		*DG_FindTexture_8001D830(int);

void EQ_ChangeTexture_80060CE4(const char* itemName1, const char* itemName2)
{
	WORD*	pTexture1;
	WORD*	pTexture2;
	WORD	buff[5];
  
	pTexture1 = DG_FindTexture_8001D830(GV_StrCode_80016CCC(itemName1));
	pTexture2 = DG_FindTexture_8001D830(GV_StrCode_80016CCC(itemName2));

	face_item_helper_80060CB8(pTexture1 + 1, buff);
	face_item_helper_80060CB8(pTexture2 + 1, pTexture1 + 1);
	face_item_helper_80060CB8(buff, pTexture2 + 1);
}

// Remove head model
void EQ_InvisibleHead_80060D5C(OBJECT *pObj, short *pnPacks, short *pRaise)
{
    if ( pObj->objs->n_models >= 7 )
    {
        *pnPacks = pObj->objs->objs[6].n_packs;
        *pRaise = pObj->objs->objs[6].raise;
        DG_FreeObjPacket_8001AAD0(&pObj->objs->objs[6], 0);
        DG_FreeObjPacket_8001AAD0(&pObj->objs->objs[6], 1);
        pObj->objs->objs[6].n_packs = 1;
        pObj->objs->objs[6].raise = -30000;
    }
}

// Put head model back
void EQ_VisibleHead_80060DF0(OBJECT *pObj, short *pnPacks, short *pRaise)
{
    if ( pObj->objs->n_models >= 7 )
    {
        pObj->objs->objs[6].n_packs = *pnPacks;
        pObj->objs->objs[6].raise = *pRaise;
        DG_FreeObjPacket_8001AAD0(&pObj->objs->objs[6], 0);
        DG_FreeObjPacket_8001AAD0(&pObj->objs->objs[6], 1);
    }
}

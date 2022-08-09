#include "SD/sd.h"

extern SOUND_W* sptr_800C057C;
extern int freq_tbl_8009FC08[108];
extern SPU_TRACK_REG spu_tr_wk_800C0658[23];
extern int mtrack_800BF1EC;

#pragma INCLUDE_ASM("asm/SD/SD_spuwr_80087A88.s")
#pragma INCLUDE_ASM("asm/sound_off_80087DAC.s")
#pragma INCLUDE_ASM("asm/SD/sng_off_80087E2C.s")
#pragma INCLUDE_ASM("asm/SD/se_off_80087E94.s")
#pragma INCLUDE_ASM("asm/SD/sng_pause_80087EF4.s")
#pragma INCLUDE_ASM("asm/SD/sng_pause_off_80087F24.s")
#pragma INCLUDE_ASM("asm/SD/keyon_80087F58.s")
#pragma INCLUDE_ASM("asm/SD/keyoff_80087F80.s")
#pragma INCLUDE_ASM("asm/SD/tone_set_80087FA8.s")
#pragma INCLUDE_ASM("asm/SD/pan_set2_800882E4.s")
#pragma INCLUDE_ASM("asm/SD/vol_set_80088320.s")

void freq_set_800885D4(unsigned int a1)
{
    unsigned char temp, temp2, temp3, temp4;
    int temp5;
    int* temp6;

    a1 += (signed char)sptr_800C057C->field_D1_micro;
    temp4 = a1;
    temp3 = (a1 >> 8) + sptr_800C057C->field_D0_macro;
    temp3 &= 0x7F;
    temp6 = freq_tbl_8009FC08;
    temp5 = temp6[temp3+1] - temp6[temp3];

    if ( temp5 & 0x8000 )
    {
        temp5 = 0xC9;
    }

    temp = temp5;
    temp2 = temp5 >> 8;
    temp5 = ((temp * temp4) >> 8) + (temp2 * temp4);
	temp5 += temp6[temp3];

    spu_tr_wk_800C0658[mtrack_800BF1EC].field_8_pitch = temp5;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_C_pitch_fg = 1;
}

#pragma INCLUDE_ASM("asm/SD/drum_set_80088694.s")

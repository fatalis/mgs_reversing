#ifndef GCL_H
#define GCL_H



// A hashed name of an actor and a pointer to a function that creates an instance of said actor
struct                      Actor;
typedef struct Actor        *(*TGCL_ActorCreateFn)(int name, int where, int argc, char **argv);

typedef struct				GCL_ActorTableEntry
{
	unsigned short			hashCode;
	TGCL_ActorCreateFn		function;
} GCL_ActorTableEntry;

// A hashed name of a GCL command and pointer to function that implements the command
typedef int                 (*TGCL_CommandFn)(unsigned char* pScript);

typedef struct				GCL_COMMANDLIST
{
	unsigned short			hashCode;
	TGCL_CommandFn			function;
} GCL_COMMANDLIST;

// leak
typedef struct              _gcl_commanddef
{
    struct _gcl_commanddef  *next;
    int                     n_commlist;
    GCL_COMMANDLIST         *commlist;
} GCL_COMMANDDEF;

// leak
typedef struct
{
    unsigned short          argc;
    long                    *argv;
} GCL_ARGS;

enum GCLOperators
{
    eNegate = 1,
    eIsZero = 2,
    eComplement = 3,
    eAdd = 4,
    eSubtract = 5,
    eMultiply = 6,
    eDivide = 7,
    eModulus = 8,
    eEquals = 9,
    eNotEquals = 10,
    eLessThan = 11,
    eLessThanOrEqual = 12,
    eGreaterThan = 13,
    eGreaterThanOrEqual = 14,
    eBitWiseOR = 15,
    eBitWiseAND = 16,
    eBitWiseXOR = 17,
    eOr = 18,
    eAnd = 19,
    eEqual = 20,
};

#define GAME_FLAG_BIT_01	0x1
#define GAME_FLAG_BIT_02	0x2
#define GAME_FLAG_BIT_03	0x4
#define GAME_FLAG_BIT_04	0x8
#define GAME_FLAG_BIT_05	0x10
#define GAME_FLAG_BIT_06	0x20
#define GAME_FLAG_BIT_07	0x40
#define GAME_FLAG_BIT_08	0x80
#define GAME_FLAG_BIT_09	0x100
#define GAME_FLAG_BIT_10	0x200
#define GAME_FLAG_BIT_11	0x400
#define GAME_FLAG_BIT_12    0x800
#define GAME_FLAG_BIT_13	0x1000
#define GAME_FLAG_BIT_14	0x2000
#define GAME_FLAG_BIT_15	0x4000
#define GAME_FLAG_BIT_16	0x8000
#define GAME_FLAG_BIT_17	0x10000
#define GAME_FLAG_BIT_18	0x20000
#define GAME_FLAG_BIT_19	0x40000
#define GAME_FLAG_BIT_20	0x80000
#define GAME_FLAG_BIT_21	0x100000
#define GAME_FLAG_BIT_22	0x200000
#define GAME_FLAG_BIT_23	0x400000
#define GAME_FLAG_BIT_24	0x800000
#define GAME_FLAG_BIT_25	0x1000000
#define GAME_FLAG_BIT_26	0x2000000
#define GAME_FLAG_BIT_27	0x4000000
#define GAME_FLAG_BIT_28	0x8000000
#define GAME_FLAG_BIT_29	0x10000000
#define GAME_FLAG_BIT_30	0x20000000
#define GAME_FLAG_BIT_31	0x40000000
#define GAME_FLAG_BIT_32	0x80000000

// Radio codes (radio.dat files)
#define RDCODE_NULL             0
#define RDCODE_TALK             1
#define RDCODE_VOICE            2
#define RDCODE_ANIM             3
#define RDCODE_ADD_CONTACT      4
#define RDCODE_MEMSAVE          5
#define RDCODE_SOUND            6
#define RDCODE_PROMPT           7
#define RDCODE_VARSAVE          8
#define RDCODE_IF               0x10
#define RDCODE_ELSE             0x11
#define RDCODE_ELSEIF           0x12
#define RDCODE_SWITCH           0x20
#define RDCODE_SWITCH_CASE      0x21
#define RDCODE_SWITCH_DEFAULT   0x22
#define RDCODE_RANDSWITCH       0x30
#define RDCODE_RANDSWITCH_CASE  0x31
#define RDCODE_EVAL             0x40
#define RDCODE_SCRIPT           0x80
#define RDCODE_ENDLINE          0xFF

// Gcl codes (.gcx files)
#define GCLCODE_NULL            0
#define GCLCODE_SHORT           1
#define GCLCODE_BYTE            2
#define GCLCODE_CHAR            3
#define GCLCODE_BOOL            4
#define GCLCODE_HASHED_STRING   6 // can also be a hashed proc name
#define GCLCODE_STRING          7
#define GCLCODE_PROC_CALL       8 // hashed proc name to call
#define GCLCODE_SDCODE          9
#define GCLCODE_TABLE_CODE      10 // .vox, .dmo and radio.dat
#define GCLCODE_VARIABLE        0x10 // variables codes are: 0x11, 0x12, 0x13, 0x14, 0x16, 0x18
#define GCLCODE_STACK_VAR       0x20
#define GCLCODE_EXPRESSION      0x30
#define GCLCODE_EXPR_OPERATOR   0x31
#define GCLCODE_SCRIPT_DATA     0x40
#define GCLCODE_PARAMETER       0x50
#define GCLCODE_COMMAND         0x60
#define GCLCODE_PROC            0x70

#define GCL_IsVariable(gcl_code)    ((gcl_code & 0xF0) == GCLCODE_VARIABLE)
#define GCL_IsParam(gcl_code)       ((gcl_code & 0xFF) == GCLCODE_PARAMETER)

#define GCL_GetVarTypeCode(gcl_var)     (((gcl_var << 1 ) >> 25) & 0xF)
#define GCL_GetVarOffset(gcl_var)       (gcl_var & 0xFFFF)
#define GCL_IsGameStateVar(gcl_var)     ((gcl_var & 0xF00000) == 0x800000)
#define GCL_GetBoolVarBitFlag(gcl_var)  (char)(1 << (((gcl_var << 1) >> 17) & 0xF))

static inline long GCL_GetLong( char *ptr ) // leak
{
    unsigned char *p;
    p = ( unsigned char * )ptr;
    return ( p[ 0 ] << 24 ) | ( p[ 1 ] << 16 ) | ( p[ 2 ] << 8 ) | ( p[ 3 ] );
}

static inline long GCL_GetShort( char *ptr ) // leak
{
    unsigned char *p;
    p = ( unsigned char * )ptr;
    return ( signed short )( ( p[ 0 ] << 8 ) | ( p[ 1 ] ) );
}

static inline char GCL_GetByte( char *ptr ) // leak
{
    return *ptr;
}

#define GCL_AdvanceShort(p) p += sizeof(short)
#define GCL_AdvanceByte(p)  p += sizeof(unsigned char)


void                        GCL_StartDaemon_8001FCDC(void);

int                         GCL_ExecBlock_80020118(unsigned char *pScript, GCL_ARGS *pArgs);
int                         GCL_ExecProc_8001FF2C(int procId, GCL_ARGS *pArgs);
int                         GCL_GetParam_80020968(char paramName);
int                         GCL_GetNextParamValue_80020AD4(void);
unsigned char               *GCL_Get_Param_Result_80020AA4(void);
unsigned char               *GCL_GetNextValue_8002069C(unsigned char *pScript, int *retCode, int *retValue);
int                         GCL_GetSV_80020A14(unsigned char *pInScript, short *pOut3Words);
void                        GCL_ChangeSenerioCode_8001FCB0(int bMain);

int                         GCL_GetNextInt_800209E8(unsigned char *pScript);

int                         GCL_AddCommMulti_8001FD2C( GCL_COMMANDDEF *pChain );

#endif // GCL_H

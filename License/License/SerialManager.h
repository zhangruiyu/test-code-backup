#pragma once
//#include "afx.h"
#include "stdafx.h"


#define ROTL32(X,C)      (((X)<<(C))|((X)>>(32-(C))))
#define ROTR32(X,C)      (((X)>>(C))|((X)<<(32-(C))))
#define ROT2(x)          (((x)>>2)|((x)<<30))
#define ROT9(x)          (((x)>>9)|((x)<<23))
#define ROT8(x)          (((x)>>8)|((x)<<24))
#define ROT16(x)         (((x)>>16)|((x)<<16))
#define ROT24(x)         (((x)>>24)|((x)<<8))
#define ROT27(x)         (((x)>>27)|((x)<<5))

#define ALG_OK					   0
#define ALG_NOTOK				   1
#define WORDS_PER_SEAL_CALL        1024
#define WORD(cp)         ((cp[0]<<24)|(cp[1]<<16)|(cp[2]<<8)|(cp[3]))
#define F1(x,y,z)        (((x)&(y))|((~(x))&(z)))
#define F2(x,y,z)        ((x)^(y)^(z))
#define F3(x,y,z)        (((x)&(y))|((x)&(z))|((y)&(z)))
#define F4(x,y,z)        ((x)^(y)^(z))
#define ENO   0      /* MODE ~ encrypt */
#define DE1   1      /* MODE ~ decrypt */
typedef struct {
	DWORD ek[32];
	DWORD dk[32];
} des_ctx;

typedef struct {
	DWORD t[520];
	DWORD s[265];
	DWORD r[20];
	DWORD counter;
	DWORD ks_buf[WORDS_PER_SEAL_CALL];
	int           ks_pos;
}  seal_ctx;

typedef struct {
	DWORD		*xk;
	int					 nr;
}  rc5_ctx;

static DWORD KnL[32] = { 0L };
static DWORD KnR[32] = { 0L };
static DWORD Kn3[32] = { 0L };
static BYTE Df_Key[24] = {
	0x0l, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
	0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
	0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67 
};
static WORD bytebit[8]    = {
	0200, 0100, 040, 020, 010, 04, 02, 01 
};
static DWORD bigbyte[24] = {
	0x800000L,    0x400000L,     0x200000L,    0x100000L,
	0x80000L,     0x40000L,      0x20000L,     0x10000L,
	0x8000L,      0x4000L,       0x2000L,      0x1000L,
	0x800L,       0x400L,        0x200L,       0x100L,
	0x80L,        0x40L,         0x20L,        0x10L,
	0x8L,         0x4L,          0x2L,         0x1L   
};
/* Use the key schedule specified in the Standard (ANSI X3.92-1981). */

static BYTE pc1[56] = {
	56, 48, 40, 32, 24, 16,  8,  0, 57, 49, 41, 33, 25, 17,
	9,  1, 58, 50, 42, 34, 26, 18, 10,  2, 59, 51, 43, 35,
	62, 54, 46, 38, 30, 22, 14,  6, 61, 53, 45, 37, 29, 21,
	13,  5, 60, 52, 44, 36, 28, 20, 12,  4, 27, 19, 11,  3 
};
static BYTE totrot[16] = {
	1,  2,  4,  6,  8, 10, 12, 14, 15, 17, 19, 21, 23, 25,
	27, 28 
};
static BYTE pc2[48] = {
	13, 16, 10, 23,  0,  4,  2, 27, 14,  5, 20,  9, 22, 18,
	11,  3, 25,  7, 15,  6, 26, 19, 12,  1, 40, 51, 30, 36,
	46, 54, 29, 39, 50, 44, 32, 47, 43, 48, 38, 55, 33, 52,
	45, 41, 49, 35, 28, 31 
};
static DWORD SP1[64] = {
	0x01010400L, 0x00000000L, 0x00010000L, 0x01010404L,
	0x01010004L, 0x00010404L, 0x00000004L, 0x00010000L,
	0x00000400L, 0x01010400L, 0x01010404L, 0x00000400L,
	0x01000404L, 0x01010004L, 0x01000000L, 0x00000004L,
	0x00000404L, 0x01000400L, 0x01000400L, 0x00010400L,
	0x00010400L, 0x01010000L, 0x01010000L, 0x01000404L,
	0x00010004L, 0x01000004L, 0x01000004L, 0x00010004L,
	0x00000000L, 0x00000404L, 0x00010404L, 0x01000000L,
	0x00010000L, 0x01010404L, 0x00000004L, 0x01010000L,
	0x01010400L, 0x01000000L, 0x01000000L, 0x00000400L,
	0x01010004L, 0x00010000L, 0x00010400L, 0x01000004L,
	0x00000400L, 0x00000004L, 0x01000404L, 0x00010404L,
	0x01010404L, 0x00010004L, 0x01010000L, 0x01000404L,
	0x01000004L, 0x00000404L, 0x00010404L, 0x01010400L,
	0x00000404L, 0x01000400L, 0x01000400L, 0x00000000L,
	0x00010004L, 0x00010400L, 0x00000000L, 0x01010004L
};
static DWORD SP2[64] = {
	0x80108020L, 0x80008000L, 0x00008000L, 0x00108020L,
	0x00100000L, 0x00000020L, 0x80100020L, 0x80008020L,
	0x80000020L, 0x80108020L, 0x80108000L, 0x80000000L,
	0x80008000L, 0x00100000L, 0x00000020L, 0x80100020L,
	0x00108000L, 0x00100020L, 0x80008020L, 0x00000000L,
	0x80000000L, 0x00008000L, 0x00108020L, 0x80100000L,
	0x00100020L, 0x80000020L, 0x00000000L, 0x00108000L,
	0x00008020L, 0x80108000L, 0x80100000L, 0x00008020L,
	0x00000000L, 0x00108020L, 0x80100020L, 0x00100000L,
	0x80008020L, 0x80100000L, 0x80108000L, 0x00008000L,
	0x80100000L, 0x80008000L, 0x00000020L, 0x80108020L,
	0x00108020L, 0x00000020L, 0x00008000L, 0x80000000L,
	0x00008020L, 0x80108000L, 0x00100000L, 0x80000020L,
	0x00100020L, 0x80008020L, 0x80000020L, 0x00100020L,
	0x00108000L, 0x00000000L, 0x80008000L, 0x00008020L,
	0x80000000L, 0x80100020L, 0x80108020L, 0x00108000L
};
static DWORD SP3[64] = {
	0x00000208L, 0x08020200L, 0x00000000L, 0x08020008L,
	0x08000200L, 0x00000000L, 0x00020208L, 0x08000200L,
	0x00020008L, 0x08000008L, 0x08000008L, 0x00020000L,
	0x08020208L, 0x00020008L, 0x08020000L, 0x00000208L,
	0x08000000L, 0x00000008L, 0x08020200L, 0x00000200L,
	0x00020200L, 0x08020000L, 0x08020008L, 0x00020208L,
	0x08000208L, 0x00020200L, 0x00020000L, 0x08000208L,
	0x00000008L, 0x08020208L, 0x00000200L, 0x08000000L,
	0x08020200L, 0x08000000L, 0x00020008L, 0x00000208L,
	0x00020000L, 0x08020200L, 0x08000200L, 0x00000000L,
	0x00000200L, 0x00020008L, 0x08020208L, 0x08000200L,
	0x08000008L, 0x00000200L, 0x00000000L, 0x08020008L,
	0x08000208L, 0x00020000L, 0x08000000L, 0x08020208L,
	0x00000008L, 0x00020208L, 0x00020200L, 0x08000008L,
	0x08020000L, 0x08000208L, 0x00000208L, 0x08020000L,
	0x00020208L, 0x00000008L, 0x08020008L, 0x00020200L
};
static DWORD SP4[64] = {
	0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
	0x00802080L, 0x00800081L, 0x00800001L, 0x00002001L,
	0x00000000L, 0x00802000L, 0x00802000L, 0x00802081L,
	0x00000081L, 0x00000000L, 0x00800080L, 0x00800001L,
	0x00000001L, 0x00002000L, 0x00800000L, 0x00802001L,
	0x00000080L, 0x00800000L, 0x00002001L, 0x00002080L,
	0x00800081L, 0x00000001L, 0x00002080L, 0x00800080L,
	0x00002000L, 0x00802080L, 0x00802081L, 0x00000081L,
	0x00800080L, 0x00800001L, 0x00802000L, 0x00802081L,
	0x00000081L, 0x00000000L, 0x00000000L, 0x00802000L,
	0x00002080L, 0x00800080L, 0x00800081L, 0x00000001L,
	0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
	0x00802081L, 0x00000081L, 0x00000001L, 0x00002000L,
	0x00800001L, 0x00002001L, 0x00802080L, 0x00800081L,
	0x00002001L, 0x00002080L, 0x00800000L, 0x00802001L,
	0x00000080L, 0x00800000L, 0x00002000L, 0x00802080L
};
static DWORD SP5[64] = {  
	0x00000100L, 0x02080100L, 0x02080000L, 0x42000100L,
	0x00080000L, 0x00000100L, 0x40000000L, 0x02080000L,
	0x40080100L, 0x00080000L, 0x02000100L, 0x40080100L,
	0x42000100L, 0x42080000L, 0x00080100L, 0x40000000L,
	0x02000000L, 0x40080000L, 0x40080000L, 0x00000000L,
	0x40000100L, 0x42080100L, 0x42080100L, 0x02000100L,
	0x42080000L, 0x40000100L, 0x00000000L, 0x42000000L,
	0x02080100L, 0x02000000L, 0x42000000L, 0x00080100L,
	0x00080000L, 0x42000100L, 0x00000100L, 0x02000000L,
	0x40000000L, 0x02080000L, 0x42000100L, 0x40080100L,
	0x02000100L, 0x40000000L, 0x42080000L, 0x02080100L,
	0x40080100L, 0x00000100L, 0x02000000L, 0x42080000L,
	0x42080100L, 0x00080100L, 0x42000000L, 0x42080100L,
	0x02080000L, 0x00000000L, 0x40080000L, 0x42000000L,
	0x00080100L, 0x02000100L, 0x40000100L, 0x00080000L,
	0x00000000L, 0x40080000L, 0x02080100L, 0x40000100L
};
static DWORD SP6[64] = {
	0x20000010L, 0x20400000L, 0x00004000L, 0x20404010L,
	0x20400000L, 0x00000010L, 0x20404010L, 0x00400000L,
	0x20004000L, 0x00404010L, 0x00400000L, 0x20000010L,
	0x00400010L, 0x20004000L, 0x20000000L, 0x00004010L,
	0x00000000L, 0x00400010L, 0x20004010L, 0x00004000L,
	0x00404000L, 0x20004010L, 0x00000010L, 0x20400010L,
	0x20400010L, 0x00000000L, 0x00404010L, 0x20404000L,
	0x00004010L, 0x00404000L, 0x20404000L, 0x20000000L,
	0x20004000L, 0x00000010L, 0x20400010L, 0x00404000L,
	0x20404010L, 0x00400000L, 0x00004010L, 0x20000010L,
	0x00400000L, 0x20004000L, 0x20000000L, 0x00004010L,
	0x02000010L, 0x20404010L, 0x00404000L, 0x20400000L,
	0x00404010L, 0x20404000L, 0x00000000L, 0x20400010L,
	0x00000010L, 0x00004000L, 0x20400000L, 0x00404010L,
	0x00004000L, 0x00400010L, 0x20004010L, 0x00000000L,
	0x20404000L, 0x20000000L, 0x00400010L, 0x20004010L 
};
static DWORD SP7[64] = {
	0x00200000L, 0x04200002L, 0x04000802L, 0x00000000L,
	0x00000800L, 0x04000802L, 0x00200802L, 0x04200800L,
	0x04200802L, 0x00200000L, 0x00000000L, 0x04000002L,
	0x00000002L, 0x04000000L, 0x04200002L, 0x00000802L,
	0x04000800L, 0x00200802L, 0x00200002L, 0x04000800L,
	0x04000002L, 0x04200000L, 0x04200800L, 0x00200002L,
	0x04200000L, 0x00000800L, 0x00000802L, 0x04200802L,
	0x00200800L, 0x00000002L, 0x04000000L, 0x00200800L,
	0x04000000L, 0x00200800L, 0x00200000L, 0x04000802L,
	0x04000802L, 0x04200002L, 0x04200002L, 0x00000002L,
	0x00200002L, 0x04000000L, 0x04000800L, 0x00200000L,
	0x04200800L, 0x00000802L, 0x00200802L, 0x04200800L,
	0x00000802L, 0x04000002L, 0x04200802L, 0x04200000L,
	0x00200800L, 0x00000000L, 0x00000002L, 0x04200802L,
	0x00000000L, 0x00200802L, 0x04200000L, 0x00000800L,
	0x04000002L, 0x04000800L, 0x00000800L, 0x00200002L 
};
static DWORD SP8[64] = {
	0x10001040L, 0x00001000L, 0x00040000L, 0x10041040L,
	0x10000000L, 0x10001040L, 0x00000040L, 0x10000000L,
	0x00040040L, 0x10040000L, 0x10041040L, 0x00041000L,
	0x10041000L, 0x00041040L, 0x00001000L, 0x00000040L,
	0x10040000L, 0x10000040L, 0x10001000L, 0x00001040L,
	0x00041000L, 0x00040040L, 0x10040040L, 0x10041000L,
	0x00001040L, 0x00000000L, 0x00000000L, 0x10040040L,
	0x10000040L, 0x10001000L, 0x00041040L, 0x00040000L,
	0x00041040L, 0x00040000L, 0x10041000L, 0x00001000L,
	0x00000040L, 0x10040040L, 0x00001000L, 0x00041040L,
	0x10001000L, 0x00000040L, 0x10000040L, 0x10040000L,
	0x10040040L, 0x10000000L, 0x00040000L, 0x10001040L,
	0x00000000L, 0x10041040L, 0x00040040L, 0x10000040L,
	0x10040000L, 0x10001000L, 0x10001040L, 0x00000000L,
	0x10041040L, 0x00041000L, 0x00041000L, 0x00001040L,
	0x00001040L, 0x00040040L, 0x10000000L, 0x10041000L
};

class CSerialManager
{
private:
	CString m_strSerial;
	CString m_strMachineCode;
public:
	CSerialManager(void);
	~CSerialManager(void);
public:
public:
	int GetFinalData(BYTE cardnum[], BYTE finaldata[],int narcardSize,int narfinalSize=20);
	//cardnum中存放序列号（不大于24位，不足24位的在高端补零）的ASCII码
	//finaldata中存放加密结果的ASCII码 20位
	//note:   000000 123456 654321 987654 是一个不需补零的序列号，长度为24
	//   而       00 123456 654321 987654 是一个需要补零的序列号，长度为20
	//               123456 654321 987654 是一个需要补零的序列号，长度为18
	//narcardSize为cardnum的实际长度(不补零时)，narfinalSize为finaldata的长度（固定为20个单元）
	int GetFinalData(CString cardnum,CString& finaldata);
	
	BOOL ValidateSerial(CString& strSerial);
	CString& GetMachineCode(){return m_strMachineCode;} //获取机器码
	CString& GetSerial(){return m_strSerial;}           //获取序列号
protected:
	CString& MakeMachineCode();


private:
	void LongToChar(DWORD olddata[],int oldSize,BYTE newdata[],int& newSize);
	void CharToLong(BYTE olddata[],int oldSize,DWORD newdata[],int& newSize);
	void CardNumToData(CString cardnum, BYTE data[], int nSize=24);
	void SealEnc(seal_ctx *sc,BYTE *key,DWORD *data,int blocks);
	void Rc5Enc(rc5_ctx *c,int rounds,BYTE *key,int keylen,DWORD *data,int blocks);
	void DesEnc(des_ctx *dc,BYTE *key,BYTE *data,int blocks);
	void des_dec(des_ctx *dc,BYTE *data,int blocks);
	void des_enc(des_ctx *dc,BYTE *data,int blocks);
	void des_key(des_ctx *dc,BYTE *key);
	static void des_desfunc(register DWORD *block,register DWORD *keys);
	static void des_unscrun(register DWORD *outof,register BYTE *into);
	static void des_scrunch(register BYTE *outof,register DWORD *into);
	void des_des(BYTE *inblock,BYTE *outblock);
	void des_usekey(register DWORD *from);
	void des_cpkey(DWORD into[]);
	void des_cookey(register DWORD *raw1);
	void des_deskey(BYTE *key,WORD edf);
	void DataToString(BYTE data[],CString& finaldata,int nSize);
	void seal_resynch(seal_ctx *c,DWORD synch_word);
	void seal_decrypt(seal_ctx *c,DWORD *data_ptr,int w);
	void seal_encrypt(seal_ctx *c,DWORD *data_ptr,int w);
	void seal_key(seal_ctx *c,BYTE *key);
	void seal_refill_buffer(seal_ctx *c);
	int seal(seal_ctx* key,DWORD in,DWORD *out);
	int seal_init(seal_ctx* result,BYTE *key);
	DWORD seal_gamma(BYTE *a,int i);
	int seal_g(BYTE *in,int i,DWORD* h);
	void rc5_encrypt(rc5_ctx* c,DWORD *data,int blocks);
	BOOL rc5_key(rc5_ctx* c,BYTE *key,int keylen);
	void rc5_init(rc5_ctx* c,int rounds);
	void rc5_destroy(rc5_ctx *c);
	void DataToString(BYTE data[],BYTE finaldata[],int dataSize,int finalSize);
	void CardNumToData(BYTE cardnum[],BYTE data[],int narcardSize,int ndataSize=24);
};

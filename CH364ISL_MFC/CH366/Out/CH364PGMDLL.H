
#ifndef		_CH36X_PGM_H
#define		_CH36X_PGM_H

#ifdef __cplusplus
extern "C" {
#endif

#define CH364CHIP 1
#define CH366CHIP 2
#define MAX_LID 0x1800
#define MAX_CART_COUNT 32
	
typedef	struct	_PCI_CONFIG {					// ����PCI���ÿռ����ݽṹ
	USHORT			mPcVendorId;				// 00H ��Ӧ�̱�ʶ
	USHORT			mPcDeviceId;				// 02H �豸��ʶ
	USHORT			mPcCommandReg;				// 04H ����Ĵ���
	USHORT			mPcStatusReg;				// 06H ״̬�Ĵ���
	UCHAR			mPcRevisionId;				// 08H �޸ı�ʶ
	UCHAR			mPcProgramIf;				// 09H �Ĵ�������̽ӿ�
	UCHAR			mPcSubClass;				// 0AH �������
	UCHAR			mPcBaseClass;				// 0BH �����������
	UCHAR			mPcCacheLine;				// 0CH �����г���
	UCHAR			mPcLatenTimer;				// 0DH �ӳټ�����
	UCHAR			mPcHeaderType;				// 0EH ͷ������
	UCHAR			mPcBistReg;					// 0FH �ں��Բ��ԼĴ���
	ULONG			mPcBaseAddr0;				// 10H ��ַ�Ĵ���0
	ULONG			mPcBaseAddr1;				// 14H ��ַ�Ĵ���1
	ULONG			mPcBaseAddr2;				// 18H ��ַ�Ĵ���2
	ULONG			mPcBaseAddr3;				// 1CH ��ַ�Ĵ���3
	ULONG			mPcBaseAddr4;				// 20H ��ַ�Ĵ���4
	ULONG			mPcBaseAddr5;				// 24H ��ַ�Ĵ���5
	ULONG			mPcCardCis;					// 28H
	USHORT			mPcSubSysVen;				// 2CH ��ϵͳ��Ӧ�̱�ʶ
	USHORT			mPcSubSysDev;				// 2EH ��ϵͳ�豸��ʶ
	ULONG			mPcExpansRom;				// 30H ��չROM��ַ�Ĵ���
	UCHAR			mPcCapPtr;					// 34H
	UCHAR			mPcReserved1[3];			// 35H
	ULONG			mPcReserved2;				// 38H
	UCHAR			mPcInterLine;				// 3CH �ж��߼Ĵ���
	UCHAR			mPcInterPin;				// 3DH �ж����żĴ���
	UCHAR			mPcMinGrant;				// 3EH
	UCHAR			mPcMaxLatency;				// 3FH
} mPCI_CONFIG, *mPPCI_CONFIG;

typedef	struct	_CH364_CFG_REG {	   // CH364оƬ�����üĴ���
	mPCI_CONFIG		mCH364CfgPci;	   // 00H-3FH,��64�ֽ�Ϊ��׼PCI���ÿռ�
	UCHAR CH364CfgDout;                // 40H ����Ĵ���
	UCHAR CH364CfgCtrl;                // 41H ���ƼĴ���
	UCHAR CH364CfgDin;                 // 42H ����Ĵ���
	UCHAR CH364CfgSet;                 // 43H ���üĴ���
	//�����Ĵ���
	UCHAR AliaCH364CfgDout;            // 44H ����Ĵ�������
	UCHAR AliaCH364CfgCtrl;            // 45H ���ƼĴ�������
	UCHAR AliaCH364CfgDin;             // 46H ����Ĵ�������
	UCHAR AliaCH364CfgSet;             // 47H ���üĴ�������
	//4FH-44H ��43H-40H �ı�����ַ��7FH-50H ������ֻ��00H
} mCH364_CFG_REG, *mPCH364_CFG_REG;

typedef	struct	_CH366_CFG_REG {	   // CH364оƬ�����üĴ���
	mPCI_CONFIG		mCH366CfgPci;	   // 00H-3FH,��64�ֽ�Ϊ��׼PCI���ÿռ�
	UCHAR           ReservedBuf[192];  // 40-FFFH��4032�ֽ�Ϊ������,ֻ������0XFF
} mCH366_CFG_REG, *mPCH366_CFG_REG;





//��Ӧ�ò㽻���Ŀ�����Ϣ�ṹ
typedef struct _CardContext
{
	ULONG CardID;         //��λ��
	UCHAR CardType;       //������
	ULONG CfgRegBaseAddr; //����ַ
}mCardContext,*mPCardContext;

HANDLE	WINAPI	InitCH364IODrv(    //��ʹ��CH364����֮ǰ���ô˺���������ʼ������,��ʼ���ɹ��󷵻�һ����Ч�ľ��.
	HWND            WindowsHandle);//��������������

HANDLE WINAPI InitCH364IODrv_Ex(
					HWND WindowsHandle,
					PCHAR SYSFilePath   //sys�ļ���·��
					);                  //�ڳ���ʹ��ǰ���ش���������,���ص�ǰ���򿪵��������.

BOOL	WINAPI	CloseCH364IODrv(
	HANDLE          DrvHandle);     //�ڽ�������ǰ�������ʹ�øú��������رղ���

BOOL	WINAPI	CH364mReadIoByte(   // ��I/O�˿ڶ�ȡһ���ֽ�
	HANDLE          DrvHandle,
	PVOID			iAddr,          // ָ��I/O�˿ڵĵ�ַ
	PUCHAR			oByte );        // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����

BOOL	WINAPI	CH364mReadIoWord(   // ��I/O�˿ڶ�ȡһ����
	HANDLE          DrvHandle,
	PVOID			iAddr,          // ָ��I/O�˿ڵĵ�ַ
	PUSHORT			oWord );        // ָ��һ���ֵ�Ԫ,���ڱ����ȡ��������

BOOL	WINAPI	CH364mReadIoDword(  // ��I/O�˿ڶ�ȡһ��˫��
	HANDLE          DrvHandle,
	PVOID			iAddr,          // ָ��I/O�˿ڵĵ�ַ
	PULONG			oDword );       // ָ��һ��˫�ֵ�Ԫ,���ڱ����ȡ��˫������

BOOL	WINAPI	CH364mWriteIoByte(  // ��I/O�˿�д��һ���ֽ�
	HANDLE          DrvHandle,
	PVOID			iAddr,          // ָ��I/O�˿ڵĵ�ַ
	UCHAR			iByte );        // ��д����ֽ�����

BOOL	WINAPI	CH364mWriteIoWord(  // ��I/O�˿�д��һ����
	HANDLE          DrvHandle,
	PVOID			iAddr,          // ָ��I/O�˿ڵĵ�ַ
	USHORT			iWord );        // ��д���������

BOOL	WINAPI	CH364mWriteIoDword(  // ��I/O�˿�д��һ��˫��
	HANDLE          DrvHandle,
	PVOID			iAddr,           // ָ��I/O�˿ڵĵ�ַ
	ULONG			iDword );        // ��д���˫������

BOOL	WINAPI	CH364_FLASH_LOCK(  //��Flash-ROM�洢������д�����趨
	HANDLE	        DrvHandle,     //��ʼ������ʱ���ص���Ч���
	UCHAR           WRLock)  ;     //Ϊ00H����д����,Ϊ8CH������д����/ֻ������,Ϊ0FFH���д����/��ȫ����,ֻ�ڸ�λ����ܽ���

BOOL	WINAPI	FindCH364(         //����CH364оƬ,��ȡ�����Ϣ
	HANDLE          DrvHandle,     //��ʼ������ʱ���ص���Ч���
	PULONG          CH364_ID,      //CH364оƬ��λ�ú�,��������ָ����ʼоƬλ�ú�
	PULONG          IS_CH364,      //�Ƿ���CH364��     
	PVOID           CfgRegBaseAddr);//CH364���üĴ�����ַ

BOOL	WINAPI	CH364_FLASH_READ(  // ��Flash-ROM�洢����ȡ���ݿ�,����ʱ,��ȡ�ĵ�ַ�����mbuffer[0]..mbuffer[3]
	HANDLE          DrvHandle,	   //��ʼ������ʱ���ص���Ч���
	ULONG			iStartAddr,    // ָ����������ݵĵ�ַ
	PVOID			oBuffer,       // ָ��һ���㹻��Ļ�����,���ڱ����ȡ������
	PULONG			oLength );     // ָ�򳤶ȵ�Ԫ,����ʱΪ׼����ȡ�ĳ���,���غ�Ϊʵ�ʶ�ȡ�ĳ���

BOOL	WINAPI	CH364_FLASH_ERASE( // ��Flash-ROM�洢����ָ��������в���
	HANDLE          DrvHandle,     //��ʼ������ʱ���ص���Ч���
	ULONG			iStartAddr,    // Ҫ��������ʼ��ַ
	ULONG           iLength );     // Ҫ�������ֽ���

BOOL	WINAPI	CH364_FLASH_WRITE( // ��洢��д��һ���ֽ�
	HANDLE          DrvHandle,     //��ʼ������ʱ���ص���Ч���
	ULONG           iStartAddr,    //д��flash�ڵ���ʼ��ַ
	PVOID           iBuffer,       //д��flash�ڵ����ݻ�����
	PULONG          iLength);      //д��flash�ڵ����ݳ���

//CH366�ӿں���
BOOL	WINAPI	CH366_FLASH_LOCK(  //��Flash-ROM�洢������д�����趨
	HANDLE	        DrvHandle,     //��ʼ������ʱ���ص���Ч���
	UCHAR           WRLock)  ;     //Ϊ00H����д����,Ϊ8CH������д����/ֻ������,Ϊ0FFH���д����/��ȫ����,ֻ�ڸ�λ����ܽ���

BOOL	WINAPI	FindCH366(         //����CH364оƬ,��ȡ�����Ϣ
	HANDLE          DrvHandle,     //��ʼ������ʱ���ص���Ч���
	PULONG          CH364_ID,      //CH364оƬ��λ�ú�,��������ָ����ʼоƬλ�ú�
	PULONG          IS_CH366,           
	PVOID           CfgRegBaseAddr);//CH364���üĴ�����ַ

BOOL	WINAPI	CH366_FLASH_READ(  // ��Flash-ROM�洢����ȡ���ݿ�,����ʱ,��ȡ�ĵ�ַ�����mbuffer[0]..mbuffer[3]
	HANDLE          DrvHandle,	   //��ʼ������ʱ���ص���Ч���
	ULONG			iStartAddr,    // ָ����������ݵĵ�ַ
	PVOID			oBuffer,       // ָ��һ���㹻��Ļ�����,���ڱ����ȡ������
	PULONG			oLength );     // ָ�򳤶ȵ�Ԫ,����ʱΪ׼����ȡ�ĳ���,���غ�Ϊʵ�ʶ�ȡ�ĳ���

BOOL	WINAPI	CH366_FLASH_ERASE( // ��Flash-ROM�洢����ָ��������в���
	HANDLE          DrvHandle,     //��ʼ������ʱ���ص���Ч���
	ULONG			iStartAddr,    // Ҫ��������ʼ��ַ
	ULONG           iLength );     // Ҫ�������ֽ���

BOOL	WINAPI	CH366_FLASH_WRITE( // ��洢��д��һ���ֽ�
	HANDLE          DrvHandle,     //��ʼ������ʱ���ص���Ч���
	ULONG           iStartAddr,    //д��flash�ڵ���ʼ��ַ
	PVOID           iBuffer,       //д��flash�ڵ����ݻ�����
	PULONG          iLength);      //д��flash�ڵ����ݳ���

BOOL	WINAPI	CH364_FLASH_LOCK(  //��Flash-ROM�洢������д�����趨
	HANDLE	        DrvHandle,     //��ʼ������ʱ���ص���Ч���
	UCHAR           WRLock)  ;     //Ϊ00H����д����,Ϊ8CH������д����/ֻ������,Ϊ0FFH���д����/��ȫ����,ֻ�ڸ�λ����ܽ���

BOOL	WINAPI	FindCH364Ex(  // ����CH364оƬ,һ��ֻ����һ��
							HANDLE DrvHandle,
							PULONG CH364_ID, //����ʱ����������ʼλ�ú�,�����Ǵ��ڵ�CH364оƬ��λ��
							PULONG IS_CH364,
							PVOID CfgRegBaseAddr,
							USHORT VendorID,     //��������ʱ��ƥ�䳧��ID
							USHORT DeviceID,     //��������ʱ��ƥ���豸ID
							ULONG ClassID);      //��������ʱ��ƥ�����ID

BOOL	WINAPI	FindCH366Ex(  // ����CH366оƬ,һ��ֻ����һ��
							HANDLE          DrvHandle,  //�������
							PULONG          CH366_ID,   //CH364оƬ��λ�ú�,��������ָ����ʼоƬλ�ú�
							PULONG          IS_CH366,
							PVOID           CfgRegBaseAddr,   //���Ļ�ַ 
							USHORT VendorID,     //��������ʱ��ƥ�䳧��ID
							USHORT DeviceID,     //��������ʱ��ƥ���豸ID
							ULONG ClassID);      //��������ʱ��ƥ�����ID

	
//֧��CH36X��鿨�ӿں���
BOOL	WINAPI	CH36X_FLASH_LOCK(  //��Flash-ROM�洢������д�����趨
	ULONG			mIndex,        //CH364�����
	UCHAR           WRLock);       //Ϊ00H����д����,Ϊ8CH������д����/ֻ������,Ϊ0FFH���д����/��ȫ����,ֻ�ڸ�λ����ܽ���

BOOL	WINAPI	FindAllCH36X(      //����CH364оƬ,��ȡ�����Ϣ
	HANDLE          DrvHandle,     //�������
	mPCardContext   CardContext,   //���������Ŀ���Ϣ
	PULONG CardCount);             //PC���������Ŀ�������

BOOL	WINAPI	CH36X_FLASH_READ(  // ��Flash-ROM�洢����ȡ���ݿ�,����ʱ,��ȡ�ĵ�ַ�����mbuffer[0]..mbuffer[3]
	ULONG			mIndex,        // CH366�����
	ULONG			iStartAddr,    // ָ����������ݵĵ�ַ
	PVOID			oBuffer,       // ָ��һ���㹻��Ļ�����,���ڱ����ȡ������
	PULONG			oLength );     // ָ�򳤶ȵ�Ԫ,����ʱΪ׼����ȡ�ĳ���,���غ�Ϊʵ�ʶ�ȡ�ĳ���

BOOL	WINAPI	CH36X_FLASH_ERASE( // ��Flash-ROM�洢����ָ��������в���
	ULONG			mIndex,        //CH366�����
	ULONG			iStartAddr,    // Ҫ��������ʼ��ַ
	ULONG           iLength );     // Ҫ�������ֽ���

BOOL	WINAPI	CH36X_FLASH_WRITE( // ��洢��д��һ���ֽ�
	ULONG			mIndex,        //CH366�����
	ULONG           iStartAddr,    //д��flash�ڵ���ʼ��ַ
	PVOID           iBuffer,       //д��flash�ڵ����ݻ�����
	PULONG          iLength);      //д��flash�ڵ����ݳ���

#ifdef __cplusplus
}
#endif

#endif		// _CH36X_PGM_H
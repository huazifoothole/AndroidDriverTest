//
// Created by chandler on 2017/8/23.
//
#include <jni.h>
#ifndef ANDROIDDRIVERTEST_NATIVE_HSCANNER_H
#define ANDROIDDRIVERTEST_NATIVE_HSCANNER_H


/**********************************************************************************************************************
* ͨ�ú궨�嶨��
**********************************************************************************************************************/
#if WIN32
#define 	__WINAPI WINAPI
#else
#define 	__WINAPI
#define	BOOL				int
#define	bool				int
#define BYTE				unsigned char
#define LONG				long
#define WORD				unsigned short
#define DWORD				unsigned long
#define TRUE				1
#define FALSE				0
#define true				1
#define false				0
#endif

/**********************************************************************************************************************
* Hscanner�ⲿ�ӿں�������
**********************************************************************************************************************/
#ifdef	__cplusplus
extern "C" {
#endif

typedef void(*SCANNERCALLBACK)(int eventId, void* data);

/**
 * 1 ��ʼ��ɨ��ǹ
 */
int __WINAPI BCRInit(SCANNERCALLBACK scannerCallBack(int,void*), const char*
input_dir, const char* output_dir);

/**
 * 2 �ر�ɨ��ǹ
 */
void __WINAPI BCRClose();

/**
 * 3 ��ȡ���һ�εĴ�����
 */
int __WINAPI BCRGetLastErrorCode();

/**
 * 4 ɨ��ǹ������ѯ
 */
int __WINAPI BCRQueryCapability();

/**
 * 5 ��ȡ���һ�εĴ�����������Ϣ������ 100 �ֽ����ڣ���������������
 */
void __WINAPI BCRGetLastErrorStr(char *const errStr, int const errStrBufLen);

/**
 *6  ����׼��
 */
bool __WINAPI BCRAimOn();

/**
 *7 �ر���׼��
 */
bool __WINAPI BCRAimOff();

/**
 * 8 ����ɨ��ǹ�豸
 */
bool __WINAPI BCREnable();

/**
 * 9 ����ɨ��ǹ�豸
 */
bool __WINAPI BCRDisable();

/**
 * 10 ����ĳ���������͵�֧�֣�����Ĭ��ֻ�� PDF417�� Data Matrix �� Interleaved 2 of 5 ���͵����룬
����Ҫʶ��������������ʱ����ͨ���˽ӿڴ����������ʶ��֧�֡�
 */
bool __WINAPI BCREnableCode(unsigned int const codeType);

/**
 * 11 �ر�ĳ���������͵�֧�֡�
 */
bool __WINAPI BCRDisableCode(unsigned int const codeType);

/**
 * 12 ��������ģʽ���������ߺ������������ɨ��������û�����ɨ�迪�أ������뿪����ģʽ������
ͨ�� Wakeup �ӿ��뿪����ģʽ��
 */
bool __WINAPI BCRSleep(unsigned int const time);

/**
 * 13 ����ɨ��ǹ
 */
bool __WINAPI BCRWakeup();

/**
 * 14 ����ͨѶ
 */
bool __WINAPI BCRResetComm();

/**
 * 15 ��ʼɨ��ʶ��
 */
bool __WINAPI BCRStartScan();

/**
 * 16 ֹͣɨ��ʶ��
 */
bool __WINAPI BCRStopScan();

/**
 * 17 �Ƿ�ɨ�����
 */
bool __WINAPI BCRScanIsComplete();

/**
 * 18 ɨ��ǹ״̬���
 */
bool __WINAPI BCRIsReady();

/**
 * 19 ����ɨ��ǹģʽ
 */
bool __WINAPI BCRSetScanMode(unsigned int const mode);

/**
 * 20 ��ȡɨ��ǹģʽ
 */
bool __WINAPI BCRGetScanMode(unsigned int *const mode);

/**
 * 21 ��ȡɨ��ǹ���״̬��ʹ���ֶ�ģʽ��ʱ����Ч��
 */
void __WINAPI BCRGetTriggerStatus(int *const status);

/**
 * 22 ��ȡɨ��ͼ��ķֱ���
 */
void __WINAPI BCRGetScanDpi(int *const widthDpi, int *const heightDpi);

/**
 * 23 ���ԭʼͼ���С�����û��ͼ���������Ϊ0
 * ������
 * width : ͼ��ʵ�ʿ��,���ش�С
 * height: ͼ��ʵ�ʸ߶ȣ����ش�С
 * bufsize: BCRGetImage �ӿ��������ռ�Ĵ�С
 */
bool __WINAPI BCRGetImageSize(int* const width,int* const height, int* const bufsize);

/**
 * 24 ���ԭʼͼ��,��ͼ��Ӧ���Ǿ������۵㴦��ͷ�λУ����ĵ�ɫͼ��
 * ������
 * image :ͼ������
 * bufferLen: Image��������С
 */
int __WINAPI BCRGetImage(char* const image,int const bufferLen);

/**
 * 25 ��ȡɨ�����ݵĳ��ȣ���Ӧ�÷�����������С��
 * ������
 * length: ΪGetTicketInfo �ӿڵ���ʱticketInfo��������Ŀռ��С
 */
bool __WINAPI BCRGetDataLength(unsigned int *const length);

/**
 * 26 ��ȡɨ�������
 * ������
 * ticketInfo: ���ؽ�������������Ϣ�������ʽ�ο��� 1 ���й������ݷ��ؽṹ����
 * ���룺
 * bufferLen: Ӧ�ó��������������Ĵ�С
 * ���أ�
 * 0 :��ȡʧ��
 * ����������ȡ��ͼ���ʱ���С
 */
int __WINAPI BCRGetTicketInfo(unsigned char *const ticketInfo, unsigned int const bufferLen);

/**
 * 27 ����ɨ��ǹ��ʾ��
 */
bool __WINAPI BCRBeep(int const tone);

/**
 * 28 ����ɨ��ǹ������ʾ��
 */
void __WINAPI BCREnableBeep();

/**
 * 29 ��ֹɨ��ǹ������ʾ��
 */
void __WINAPI BCRDisableBeep();

/**
 * 30 ���ɨ��ǹ�����е�����
 */
void __WINAPI BCRClearBuffer();

/**
 * 31 ȡ��ɨ��ǹ��Ӳ����Ϣ
 *  ������hwinfo
 *  ���룺��ʶ hwInfo �ĳ��ȣ���4096�ֽ����ڣ�
 */
bool __WINAPI BCRGetHWInformation(char* const hwInfo , int const length);

/**
 * 32 ��ȡ����汾
 * ������
 * swversion:�汾��
 */
void __WINAPI BCRGetSWVersion(char* const swversion , unsigned int const length);

/**
 * 33 �򿪲������û������Ƶ���ɫ
 * ���룺
 *  1 Green LED
    2 Red LED
 */
bool __WINAPI BCRUserLEDOn(unsigned int *const mode);

/**
 * 34 �ر��û�������
 */
void __WINAPI BCRUserLEDOff();

#ifdef	__cplusplus
}
#endif

#endif //ANDROIDDRIVERTEST_NATIVE_HSCANNER_H
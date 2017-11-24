#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <android/log.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "native-hscanner.h"
#include "com_example_andrivertest_BCRInterface.h"

#define  LOG_TAG    "native-hscanner"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO  , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)


/**********************************************************************************************************************
* Hscanner�ӿڴ�����
**********************************************************************************************************************/
#define	PRINTER_START_CODE			0x00
#define	HSCANNER_NO_ERROR			0x00
#define NO_HSCANNER  2001  //Can not find  �Ҳ���ɨ��ǹ
#define DATA_LINE_ERROR   2002 //�����߹��� Data line error
#define POWER_ERROR 2003    //��Դ�߹���
#define HSCANNER_IS_BUSY 2004 //ɨ��ǹæ
#define TIME_OUT 2005 //��ʱ
#define HSCANNER_DISABLED 2006//ɨ��ǹ������
#define GET_HWVERSION_ERROR 2007//��ȡɨ��ǹӲ����Ϣʧ��
#define START_ERROR 2008//����ɨ��ǹʧ��
#define TABPAR_NONE 2009//�����ļ�������
#define GET_ORIGIN_IMAGE_ERROR 2010//��ȡԭʼͼ������ʧ��
#define HSCANNER_READ_ERROR 2011//ɨ��ǹ���ݶ�ȡ����
#define OTHER_ERROR 2500//��������




int	returnValueInt = HSCANNER_NO_ERROR;
bool isInit = false;
char  mbarCode[256] = {0x00};


JNIEXPORT jint JNICALL Java_com_example_andrivertest_BCRInterface_BCRInit
        (JNIEnv *env, jclass){

    int bcrRet = BCRInit(NULL, "/sdcard/", "/sdcard/");
    LOGI("bcrRet = %d",bcrRet);

    return bcrRet;
}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetLastErrorCode
        (JNIEnv *, jclass) {

    int ret = BCRGetLastErrorCode();
    return ret;
}

JNIEXPORT jstring JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetLastErrorStr
        (JNIEnv *env, jclass) {

    char errStr[256] = {0x00};
    BCRGetLastErrorStr(errStr, 256);
    return env->NewStringUTF(errStr);

}

JNIEXPORT void JNICALL Java_com_example_andrivertest_BCRInterface_BCRClose
        (JNIEnv *, jclass) {

    BCRClose();
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRStartScan
        (JNIEnv *, jclass) {

    bool flag = false;
    flag = BCRStartScan();
    return  flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRStopScan
        (JNIEnv *, jclass) {

    bool flag = false;
    flag = BCRStopScan();
    return  flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRScanIsComplete
        (JNIEnv *, jclass) {

    bool flag = false;
    flag = BCRScanIsComplete();
//    LOGI("bcriscomplete return=%d",flag);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRIsReady
        (JNIEnv *, jclass) {

    bool flag = false;
    flag = BCRIsReady();
    return flag;
}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetTicketInfo
        (JNIEnv *env, jclass , jbyteArray ticketinfo, jint length) {

    int returnValue = -1;
    unsigned char info[4096] = {0};
    memset(info, 0, sizeof(info));
    returnValue = BCRGetTicketInfo(info, 4096);
    LOGI("ticket length=%d",returnValue);

    env->SetByteArrayRegion(ticketinfo,0,returnValue,(jbyte*)info);
    return returnValue;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetHWInformation
        (JNIEnv *env, jclass, jbyteArray hwInfo, jint length) {

    bool flag = false;
    char info[1024] = {0x00};
    //�´�½����ǹ�˽ӿں������ƴ��� ΪBCRGetHWInfomation ��ȷΪBCRGetHWInformation
    flag = BCRGetHWInformation(info, sizeof(info));
    env->SetByteArrayRegion(hwInfo,0,strlen(info),(jbyte*)info);

    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRBeep
        (JNIEnv *, jclass, jint tone){

    bool flag = false;
    flag = BCRBeep(tone);
    return flag;
}

JNIEXPORT void JNICALL Java_com_example_andrivertest_BCRInterface_BCRUserLEDOff
        (JNIEnv *, jclass) {

    BCRUserLEDOff();
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRUserLEDOn
        (JNIEnv *, jclass, jint mode){

    bool flag = false;
    if(mode >0){
        unsigned int mode_ = mode;
        flag = BCRUserLEDOn(&mode_);
    }

    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRAimOff
        (JNIEnv *, jclass){
    bool flag = BCRAimOff();
    return flag;
}

/*
 * Class:     com_example_andrivertest_BCRInterface
 * Method:    BCRAimOn
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRAimOn
        (JNIEnv *, jclass){
    bool flag = BCRAimOn();
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRSetScanMode
        (JNIEnv *, jclass, jint mode){
    bool flag = BCRSetScanMode(mode);
    return flag;
}

/*
 * Class:     com_example_andrivertest_BCRInterface
 * Method:    BCRGetScanMode
 * Signature: (Ljava/lang/Integer;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetScanMode
        (JNIEnv *env, jclass, jobject mode){
    unsigned int mode_;
    bool flag = BCRGetScanMode(&mode_);
    if(!flag)
        return  false;

    jclass class_mode = env->FindClass("java/lang/Integer");
    if(class_mode == NULL){
        return false;
    }
    jfieldID id = env->GetFieldID(class_mode, "value", "I");
    if(id == NULL){
        return false;
    }
    env->SetIntField(mode, id, mode_);
    return flag;
}

JNIEXPORT void JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetTriggerStatus
        (JNIEnv *env, jclass, jobject status){

    unsigned int mode_;
    bool flag = BCRGetScanMode(&mode_);

    jclass class_mode = env->FindClass("java/lang/Integer");
    jfieldID id = env->GetFieldID(class_mode, "value", "I");
    env->SetIntField(status, id, mode_);
}

JNIEXPORT void JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetScanDpi
        (JNIEnv *env, jclass, jobject widthDpi, jobject heightDpi){

    bool flag = false;
    jclass class_dpi = env->FindClass("java/lang/Integer");
    jfieldID id = env->GetFieldID(class_dpi, "value", "I");

    int w =0,h=0;
    BCRGetScanDpi(&w,&h);

    env->SetIntField(widthDpi, id, w);
    env->SetIntField(heightDpi, id, h);

}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetImageSize
        (JNIEnv *env, jclass, jobject width, jobject height, jobject bufsize) {

    bool flag = false;
    jclass class_dpi = env->FindClass("java/lang/Integer");
    jfieldID id = env->GetFieldID(class_dpi, "value", "I");

    int w =0,h=0,size = 0;
    flag = BCRGetImageSize(&w,&h,&size);

    env->SetIntField(width, id, w);
    env->SetIntField(height, id, h);
    env->SetIntField(bufsize, id, size);

    return flag;
}

JNIEXPORT void JNICALL Java_com_example_andrivertest_BCRInterface_BCREnableBeep
        (JNIEnv *, jclass) {
    BCREnableBeep();
}

JNIEXPORT void JNICALL Java_com_example_andrivertest_BCRInterface_BCRDisableBeep
        (JNIEnv *, jclass) {
    BCRDisableBeep();
}

JNIEXPORT void JNICALL Java_com_example_andrivertest_BCRInterface_BCRClearBuffer
        (JNIEnv *, jclass) {
    BCRClearBuffer();
}

JNIEXPORT jstring JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetSWVersion
        (JNIEnv *env, jclass){
    char info[1024] = {0x00};

    BCRGetSWVersion(info,1000);
    return env->NewStringUTF(info);
}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetImage
        (JNIEnv *env, jclass, jbyteArray imageInfo, jobject bufferLength) {
//    char *image  =  new char[1024 * 20]();
//    int const size=0 ;

    int width = 0, height = 0, buffsize = 0;
    BCRGetImageSize(&width, &height, &buffsize);

    char image[buffsize];
    memset(image, 0, sizeof(image));
    int length =  BCRGetImage(image, buffsize);
    LOGI("getImage length=%d,size=%d",length,buffsize);

    env->SetByteArrayRegion(imageInfo, 0, length, (jbyte*) image);

    jclass class_dpi = env->FindClass("java/lang/Integer");
    jfieldID id = env->GetFieldID(class_dpi, "value", "I");
    env->SetIntField(bufferLength, id, buffsize);


    return  length;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRResetComm
        (JNIEnv *, jclass) {
    bool flag = BCRResetComm();
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRWakeup
        (JNIEnv *, jclass){
    bool flag = BCRWakeup();
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRSleep
        (JNIEnv *, jclass, jint seconds){
    bool flag = BCRSleep(seconds);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRDisableCode
        (JNIEnv *, jclass, jint code){
    bool flag = BCRDisableCode(code);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCREnableCode
        (JNIEnv *, jclass, jint code){
    bool flag = BCREnableCode(code);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRDisable
        (JNIEnv *, jclass){
    bool flag = BCRDisable();
    return flag;
}

/*
 * Class:     com_example_andrivertest_BCRInterface
 * Method:    BCREnable
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCREnable
        (JNIEnv *, jclass){
    bool flag = BCREnable();
    return flag;
}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_BCRInterface_BCRQueryCapability
        (JNIEnv *, jclass){
    int ret = BCRQueryCapability();
    return ret;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_BCRInterface_BCRGetDataLength
        (JNIEnv *env, jclass, jobject length) {

    bool flag = false;
    jclass class_dpi = env->FindClass("java/lang/Integer");
    jfieldID id = env->GetFieldID(class_dpi, "value", "I");

    unsigned int l=0;
    flag = BCRGetDataLength(&l);
    LOGI("len===%d",l);

    env->SetIntField(length, id, l);
    return flag;
}


#ifdef __cplusplus
}
#endif





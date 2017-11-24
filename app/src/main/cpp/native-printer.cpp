#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <android/log.h>

extern "C"

#include "byScanPrnDeviceDll.h"
#include "com_example_andrivertest_PrinterInterface.h"

#define  LOG_TAG    "native-printer"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)


/**********************************************************************************************************************
* Printer????????
**********************************************************************************************************************/
#define	PRINTER_START_CODE			0x00
#define	PRINTER_NO_ERROR			0x00
#define	PRINTER_TIME_OUT			(PRINTER_NO_ERROR - 0x01)		//???
#define	PRINTER_DATA_ERROR			(PRINTER_NO_ERROR - 0x02)		//?????????
#define	PRINTER_PAPER_ERROR			(PRINTER_NO_ERROR - 0x03)		//??????
#define	PRINTER_POWER_ERROR			(PRINTER_NO_ERROR - 0x04)		//????????
#define	PRINTER_COVER_ERROR			(PRINTER_NO_ERROR - 0x05)		//????
#define	PRINTER_PAPER_JAM			(PRINTER_NO_ERROR - 0x06)		//???
#define	PRINTER_NOT_COMPLETE			(PRINTER_NO_ERROR - 0x07)		//???????????(????????)
#define	PRINTER_OTHER_ERROR			(PRINTER_NO_ERROR - 0x08)		//????????(??????)
#define	PRINTER_TABPAR_NONE			(PRINTER_NO_ERROR - 0x09)		//???????
#define	PRINTER_HAVE_NOT_INIT		(PRINTER_NO_ERROR - 0x0A)		//???????
//#define	PRINTER_INVALID_ARGUMNET		(PRINTER_NO_ERROR - 0x0B)		//????????
#define 	PRINTER_MODE_SWITCH_ERROR		(PRINTER_NO_ERROR - 0x0C)		//??????????
#define 	PRINTER_HEAD_ERROR			(PRINTER_NO_ERROR - 0x0D)		//???????
#define 	PRINTER_CUT_ERROR			(PRINTER_NO_ERROR - 0x0E)		//????????
#define	PRINTER_NOT_FULL			(PRINTER_NO_ERROR - 0x10)		//?????????
#define	PRINTER_FORBID			(PRINTER_NO_ERROR - 0x11)		//????????(???????????)
#define	PRINTER_NOSUPPORT			(PRINTER_NO_ERROR - 0x12)		//?????
#define	PRINTER_MIN_CODE			(PRINTER_NO_ERROR - 0x13)		//?????????
#define	PRINTER_INVALID_ERROR_CODE		(PRINTER_NO_ERROR - 0x14)		//??????????


int	returnValueInt = PRINTER_NO_ERROR;
bool isInit = false;
char  mbarCode[256] = {0x00};


static int ReadBmpfileData(char* fileName, char* data)
{
    int i = 0;
    FILE *fp;



    fp = fopen(fileName, "r+");
    if(fp == NULL)
    {
        printf("Open file error");
        return -1;
    }
    while(!feof(fp))
    {
        fread(data + i, sizeof(char), 1, fp);
        i++;
    }
    fclose(fp);

    return 0;
}


JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PInit
        (JNIEnv *env, jobject, jstring j_input,jstring j_output) {

    int returnValueInt = 1;
    const char *input = NULL , *output = NULL;
    if(j_input == NULL || j_output == NULL){
         return 1;
    }
    input = env->GetStringUTFChars(j_input, NULL);
    output = env->GetStringUTFChars(j_output, NULL);


    returnValueInt = PInit(input, output);
    LOGI("native input =%s, output=%s", input,output);
    if (returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B) {
        LOGI("Init return %d", returnValueInt);
        return returnValueInt;
    }else {
        LOGI("printer init ok");
    }

    env->ReleaseStringUTFChars(j_input, input);
    env->ReleaseStringUTFChars(j_output, output);

    return returnValueInt;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetCutterMode
        (JNIEnv * env, jobject, jint mode) {

    bool ret = PSetCutterMode(mode);

    return  ret;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PGetCutterMode
        (JNIEnv *env, jobject, jobject mode) {

    int mode_;
    bool flag = PGetCutterMode(&mode_);
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

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetFont
        (JNIEnv *, jobject,jint index,jint size,jint aligment) {

    bool flag = PSetFont(index, size, aligment);
    return  flag;

}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetFontEmpha
        (JNIEnv *, jobject, jint n){
    bool flag;
    flag = PSetFontEmpha(n);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetLineSpace
        (JNIEnv *, jobject, jint size){
    bool flag = PSetLineSpace(size);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetCharSpace
        (JNIEnv *, jobject, jint size) {
    bool flag = PSetCharSpace(size);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetLeftMargin
        (JNIEnv *, jobject, jint size){
    bool flag = PSetLeftMargin(size);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetAreaWidth
        (JNIEnv *, jobject, jint size){
    bool flag = PSetAreaWidth(size);
    return flag;
}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PQueryCapability
        (JNIEnv *, jobject){
    int value = PQueryCapability();
    return value;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PPrinterIsReady
        (JNIEnv *, jobject){
    bool flag = PPrinterIsReady();
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PGetDpi
        (JNIEnv *env, jobject obj, jobject widthDpi, jobject heightDpi){

    bool flag = false;
    jclass class_dpi = env->FindClass("java/lang/Integer");
    if(class_dpi == NULL){
        return false;
    }

    jfieldID id = env->GetFieldID(class_dpi, "value", "I");
    if(id == NULL){
        return  false;
    }

    int w =0,h=0;
    flag = PGetDpi(&w,&h);

    env->SetIntField(widthDpi, id, w);
    env->SetIntField(heightDpi, id, h);

    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PGetHWInformation
        (JNIEnv *env, jobject, jobject hwinfo_obj, jint length){

    char info[1024] = {0x00};
    bool flag = PGetHWInformation(info, length);


    jclass class_dpi = env->FindClass("java/lang/Byte");
    if(class_dpi == NULL){
        return false;
    }

    jfieldID id = env->GetFieldID(class_dpi, "value", "B");
    if(id == NULL){
        return  false;
    }



    return flag;

}

JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_PGetSWVersion
        (JNIEnv *env, jobject) {
    char info[1024] = {0x00};

    bool flag = PGetSWVersion(info,1000);
    if(!flag){
        return env->NewStringUTF("false");
    }
    return env->NewStringUTF(info);
}


JNIEXPORT void JNICALL Java_com_example_andrivertest_PrinterInterface_PFeedLine
        (JNIEnv *, jobject, jint n){

    PFeedLine(n);

}

JNIEXPORT int JNICALL Java_com_example_andrivertest_PrinterInterface_PrintPDF417
        (JNIEnv *env, jobject, jint mode_width, jint mode_height, jint data_rows, jint data_columns, jint err_level, jstring pdfStr, jint length, jint mode) {

    jboolean iscopy;

    int ret = PrintPDF417(mode_width,mode_height,data_rows,data_columns,err_level,env->GetStringUTFChars(pdfStr,&iscopy),length,mode);

    return ret;
}

JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PSetUserChar
        (JNIEnv *env, jobject, jint c1, jint c2,jint m ) {

    bool flag = false;
    unsigned char buf9[27] = {0,0,0,127,255,254,64,24,1,64,24,1,127,255,254,64,24,1,64,24,1,127,255,254,0,0,0};  //9*24  田
    unsigned char buf12[36] = {0,0,0,127,255,127,64,129,2,64,129,2,64,129,2,64,129,2,64,129,2,64,129,2,64,129,2,64,129,2, 127,255,127,0,0,0}; //12*24 目

    int num = c2 -c1 +1 ;
    if(num > 0){
        if(9 == m){
            unsigned char *tmpBuf9 = new unsigned char[num*27];
            for (int i = 0; i < num*27; i ++)
            {
                tmpBuf9[i] = buf9[i%27];
            }
            flag = PSetUserChar(c1, c2, m, tmpBuf9, num * 27);
        }else if(12 == m){
            unsigned char *tmpBuf12 = new unsigned char[num*36];
            for (int i = 0; i < num*36; i++)
            {
                tmpBuf12[i] = buf12[i%36];
            }
            flag = PSetUserChar(c1, c2, m, tmpBuf12, num * 36);
        }
    }


    return flag;
}

JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PUnsetUserChar
        (JNIEnv *, jobject,jint c1,  jint c2) {
    bool flag = PUnsetUserChar(c1, c2);
    return flag;
}

JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintUserChar
        (JNIEnv *, jobject, jint c1,  jint c2){
    bool flag = PPrintUserChar(c1, c2);
    return flag;
}

JNIEXPORT int JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintDiskImage
        (JNIEnv *env, jobject, jint xpos,  jint ypos, jstring pathStr) {



    const char *path = env->GetStringUTFChars(pathStr, 0);

    int ret = PPrintDiskImage(xpos, ypos, path);

    env->ReleaseStringUTFChars(pathStr, path);
    return ret;

}
JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintBlackMark
        (JNIEnv *env, jobject, jcharArray jcharArray1,  jint length) {

    char barcode[256] = {0x00};
    jchar*  jchar1 =env->GetCharArrayElements(jcharArray1, 0);
    for(int i=0;i<length;i++){
        barcode[i] = jchar1[i];
    }
    bool flag = PPrintBlackMark(barcode, length);
    return flag;
}
JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PGetTopMargin
        (JNIEnv *env, jobject, jobject margin){

    bool flag = false;
    jclass class_dpi = env->FindClass("java/lang/Integer");
    if(class_dpi == NULL){
        return false;
    }

    jfieldID id = env->GetFieldID(class_dpi, "value", "I");
    if(id == NULL){
        return  false;
    }

    int m =0;
    flag = PGetTopMargin(&m);

    env->SetIntField(margin, id, m);
    return flag;
}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintIsComplete
        (JNIEnv *, jobject, jint timeout){

    int ret = PPrintIsComplete(timeout);
    return ret;
}

JNIEXPORT jlong JNICALL Java_com_example_andrivertest_PrinterInterface_PGetPrintLength
        (JNIEnv *, jobject){

    long length = PGetPrintLength();
    return length;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PLoadLogoImage
        (JNIEnv *env, jobject, jint imgCount){

    bool flag = false;
    char filePath[100];

    char* imgList[imgCount];


    for(int i = 0;i<imgCount;i++){
        char *imgFileData = new char[1024 * 20];
        strcpy(filePath,"/sdcard/config/TestImage/logoImage/logoImage");
        char tmp[5];
        sprintf(tmp, "%d", i+1);
        strcat(filePath, tmp);
        strcat(filePath,".bmp");
        ReadBmpfileData(filePath, imgFileData);
        imgList[i] = imgFileData;
    }


    flag = PLoadLogoImage(imgCount, imgList);

    return flag;
}

char *openFile(char *filepath){
    char* buf;
    return  buf;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PLoadDiskLogo
        (JNIEnv *env, jobject, jint count,jobjectArray logoArray){

    bool flag = false;
    jstring jstr;
    jsize len = env->GetArrayLength(logoArray);
    char *imageList [len] ;
    for(int i=0; i< len; i++){
        jstr = (jstring) env->GetObjectArrayElement(logoArray,i);
        imageList[i] = (char*) env->GetStringUTFChars(jstr, 0);
        LOGI("imageList=%s", imageList[i]);
    }
    PLoadDiskLogo(len,imageList);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintLogo
        (JNIEnv *, jobject, jint x, jint y,jint index) {

    bool flag = PPrintLogo(x, y, index);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetAngle
        (JNIEnv *, jobject, jint angle){

    bool flag = PSetAngle(angle);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PExecESCPOS
        (JNIEnv *env, jobject, jcharArray cmd, jint length) {


    jchar* command =  env->GetCharArrayElements(cmd, 0);
    bool flag = false;
    flag = PExec_ESC_POS((char *const)command, length);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetPageMode
        (JNIEnv *, jobject, jint width, jint height, jint leftTop_x, jint leftTop_y) {

    bool flag = PSetPageMode(width, height, leftTop_x, leftTop_y);
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetLineMode
        (JNIEnv *, jobject){

    bool flag = PSetLineMode();
    return flag;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintPage
        (JNIEnv *, jobject) {

    bool flag = PPrintPage();
    return flag;
}

JNIEXPORT void JNICALL Java_com_example_andrivertest_PrinterInterface_PGetLastErrorStr
        (JNIEnv *env, jobject,jcharArray jcharArray1,jint length) {


        jchar a[256]={0x00};

        char errStr[256] = {0x00};
        PGetLastErrorStr(errStr, 256);
        LOGI("errstr length =%d",sizeof(errStr));
        for(int i=0;i<256;i++) {
            a[i] = errStr[i];
        }
        env->SetCharArrayRegion(jcharArray1, 0, sizeof(errStr), a);
//        char	errStr[256] = {0x00};
//        PGetLastErrorStr(errStr, 200);
//        return env->NewStringUTF(errStr);

}



//**************//
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintInit
        (JNIEnv * env, jobject) {

    returnValueInt = PInit("/sdcard/", "/sdcard/");
    if (returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B) {
        //printf("PrinterInit failed, return code: %d\n", returnValueInt);
        LOGI("Init return %d", returnValueInt);
        return false;
    } else {
        isInit = true;
    }

    return isInit;

}

bool Print_PDF417() {
    //*****************************************************************************************************************
    //??????????????
    int		returnValueInt = PRINTER_NO_ERROR;
    bool		returnValueBool = false;
    bool		returnValue = false;
    char    	barCode[256] = {0x00};
    int		barCodeLength = 0;
    int		ii = 0;
    int 		begin = 0;


    bool ret = PPrinterIsReady();
    int errcode = 0;

    if (!ret) {
        return false;
    }

    //*****************************************************************************************************************
    //????????
    if(!PSetLineMode())
    {
        goto ExitLine;
    }

    //*****************************************************************************************************************
    //?????????
    if(!PSetBottomMargin(200))
    {
        goto ExitLine;
    }

    //*****************************************************************************************************************
    //?��??��?????????
//    PPrinterIsReady();

    //*****************************************************************************************************************
    //??????????
    returnValueBool = PSetLeftMargin(0x0);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetLeftMargin failed!\n");
        fflush(stdout);
        goto ExitLine;
    }

    returnValueBool = PSetLineSpace(10);//?????��?
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(36) failed!\n");
        fflush(stdout);
        goto ExitLine;
    }

    returnValueBool = PSetFont(0x00, 0x11,0x01);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(0x33,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = PPrintString("��ʾƱ<ȫ����������3>\n\n");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('��ʾƱ<ȫ����������3>') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    returnValueBool = PSetLineSpace(14);//?????��??
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(24) failed!\n");
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueBool = PSetFont(0x00,0x00,0x01);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetFont(0x00,0x00,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = PPrintString("35073110603460810054   d2WIvi   64319331\n");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('35073110603460810054') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    returnValueInt = PPrintString("���۵�:06034      06073�� 2006/03/22����");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('���۵�:06034') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }
    PPrintString("\n");

    returnValueInt = PPrintString("��:1  �ϼ�:2Ԫ       2006/03/22 12:26:49\n");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('��:1  �ϼ�:2Ԫ') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueBool = PSetFont(0x00,0x10,0x01);
    if(!returnValueBool)
    {
        printf("PrinterSetFont(0x00,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = PPrintString("�� ʽ Ʊ");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� ʽ Ʊ') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("�� 3 3 2");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 3 3 2') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???

    returnValueInt = PPrintString("�� 5 8 1");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 5 8 1') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("�� 3 3 2");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 3 3 2') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("�� 5 8 3");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 5 8 3') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("�� 3 3 2");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 3 3 2') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(2);//???
    returnValueBool = PSetFont(0x00,0x00,0x01);
    if(!returnValueBool)

    {
        printf("PrinterSetFont(2)(0x00,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = PPrintString("�绰��ѯ:123456���Ų�ѯ:����1234����4321");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�绰��ѯ') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("����������ͬ�����ţ�������");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('��������') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    returnValueInt = PPrintString("\n\n\n");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('��������') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    //*****************************************************************************************************************
    //????????????
    memset(barCode, 0x00, sizeof(barCode));
    barCodeLength = (rand() % 21);
    barCodeLength = (barCodeLength < 10) ? 10 : barCodeLength;
    for(ii = 0; ii < barCodeLength; ii++)
    {
        if(ii < (barCodeLength / 2))//????
        {
            barCode[ii] = (rand() % 10) + '0';
        }
        else//???
        {
            barCode[ii] = rand() % 27 + 'A';
        }
    }

    //*****************************************************************************************************************
    //???????
    memcpy(mbarCode, barCode, sizeof(barCode));
    returnValueInt = PrintPDF417(15, 38, 20 , 6, 3, barCode, 32, 2);
//    returnValueInt = PrintPDF417(10, 10, 1 , 1, 3, barCode, 32, 2);
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintPDF417('%s') failed, return code: %d\n", barCode, returnValueInt);
        goto ExitLine;
    }

    PCutPaper();//???

    returnValue = true;
    ExitLine:
    return  false;

    return returnValue;
}


JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_GetPDFCode
        (JNIEnv *env, jobject) {

    return env->NewStringUTF(mbarCode);
}




int PrintBarcodeTicket(int codeType)
{
    //*****************************************************************************************************************
    //??????????????
    int	returnValueInt = PRINTER_NO_ERROR;
    int	returnValueBool = true;
    char   barCode[256] = {0x00};
    int	barCodeLength = 0;
    int	ii = 0;
    //unsigned char codeType = 0,
    unsigned char		setType = 0;
    int 	begin = 0;

    //*****************************************************************************************************************
    //???????????????
    //printf(Printer_Barcode_Item);
    //printf("Please input your select(0-9):");
    //scanf("%d",&codeType);ClearStdin//????????
    if(codeType < 0 || codeType > 9)
    {
        printf("The selection error!\n");
        goto ExitLine;
    }



    //*****************************************************************************************************************
    //??????????
    PSetAreaWidth(0x300); //??????????
    returnValueBool = PSetLeftMargin(0x0);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetLeftMargin failed!\n");
        goto ExitLine;
    }

    returnValueBool = PSetLineSpace(36);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(36) failed!\n");
        goto ExitLine;
    }

    returnValueBool = PSetFont(0x00,0x10,0x01);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(0x00,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = PPrintString("???<???????????3>");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('???<???????????3>') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(3);//???
    returnValueBool = PSetLineSpace(24);//?????????
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(24) failed!\n");
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueBool = PSetFont(0x00,0x00,0x01);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetFont(0x00,0x00,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = PPrintString("35073110603460810054   d2WIvi   64319331");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('35073110603460810054') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("?????:06034      06073?? 2006/03/22????");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('?????:06034') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("??:1  ???:2?       2006/03/22 12:26:49");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('??:1  ???:2?') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueBool = PSetFont(0x00,0x10,0x01);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetFont(0x00,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = PPrintString("? ? ?");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('? ? ?') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("?? 3 2 2");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('?? 3 2 2') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("?? . . .");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('?? . . .') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("?? . . .");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('?? . . .') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("?? . . .");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('?? . . .') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("?? . . .");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('?? . . .') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueBool = PSetFont(0x00,0x00,0x01);
    if(!returnValueBool)
    {
        printf("PrinterSetFont(2)(0x00,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = PPrintString("??????:123456??????:????1234????4321");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('??????') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(1);//???
    returnValueInt = PPrintString("????????????????????????");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('????????') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    PFeedLine(3);//???

    //*****************************************************************************************************************
    //????????????
    memset(barCode, 0x00, sizeof(barCode));
    switch(codeType)
    {
        case 0://ITF
        {
            barCodeLength = (2 * (rand() % 128 + 1));//1-255(???)
            barCodeLength = (barCodeLength > 8) ? 8 : barCodeLength;
            for(ii = 0; ii < barCodeLength; ii++)
            {
                barCode[ii] = 48 + (rand() % (57 - 48 + 1));//48-57
            }
        }
            break;
        case 1://CodeBar
        {
            barCodeLength = (rand() % 254 + 1);//1-255
            barCodeLength = (barCodeLength > 8) ? 8 : barCodeLength;
            barCode[0] = (rand() % 4 + 65);//65-68(A-D)
            for(ii = 1; ii < barCodeLength - 1; ii++)
            {
                barCode[ii] = 48 + (rand() % (57 - 48 + 1));//48-57(?????)
            }
            barCode[barCodeLength - 1] = (rand() % 4 + 65);//65-68(A-D or (TE*N))
        }
            break;
        case 2://Code93
        {
            barCodeLength = (rand() % 255 + 1);//1-255
            barCodeLength = (barCodeLength > 10) ? 10 : barCodeLength;
            for(ii = 0; ii < barCodeLength; ii++)
            {
                barCode[ii] = '0' + (rand() % ('9' - '0' + 1));//0-9
            }
        }
            break;
        case 3://Code128
        {
            setType = 65 + (rand() % (67 - 65 + 1));//65-67
            printf("setType: %d\n",setType);
            if(setType == 0x43)//?????C
            {
                barCodeLength = (2 * (rand() % 127 + 2));//2-255(???)
                barCodeLength = (barCodeLength > 12) ? 12 : barCodeLength;
                for(ii = 0; ii < barCodeLength; ii++)
                {
                    barCode[ii] = '0' + (rand() % ('9' - '0' + 1));//0-9
                }
            }
            else//?????A\B
            {
                barCodeLength = (rand() % (255 - 2 + 1) + 2);//2-255
                barCodeLength = (barCodeLength > 8) ? 8 : barCodeLength;
                for(ii = 0; ii < barCodeLength; ii++)
                {
                    barCode[ii] = (rand() % 27) + 'A';
                }
            }
        }
            break;
        case 4://None
            break;
        case 5://UPC-A
        {
            barCodeLength = (rand() % (12 - 11 + 1) + 11);//11-12
            for(ii = 0; ii < barCodeLength; ii++)
            {
                barCode[ii] = 48 + (rand() % (57 - 48 + 1));//48-57
            }
        }
            break;
        case 6://UPC-E
        {
            barCodeLength = 12;
            barCode[0] = 0x30;
            for(ii = 1; ii < barCodeLength; ii++)
            {
                barCode[ii] = 0x30 + ii;
            }
            barCode[barCodeLength - 2] = 0x30;
            barCode[barCodeLength - 1] = 0x31;
        }
            break;
        case 7://EAN13
        {
            LOGI("printcodetype   %d",codeType);

            barCodeLength = (rand() % (13 - 12 + 1) + 12);//12-13
            for(ii = 0; ii < barCodeLength; ii++)
            {
                barCode[ii] = 48 + (rand() % (57 - 48 + 1));//48-57
            }
        }
            break;
        case 8://EAN8
        {
            barCodeLength = (rand() % (8 - 7 + 1) + 7);//7-8
            for(ii = 0; ii < barCodeLength; ii++)
            {
                barCode[ii] = 48 + (rand() % (57 - 48 + 1));//48-57
            }
        }
            break;
        case 9://Code39
        {
            barCodeLength = (rand() % (255 - 1 + 1) + 1);//1-255
            barCodeLength = (barCodeLength > 8) ? 8 : barCodeLength;
            barCode[0] = barCode [barCodeLength -1] = '*';
            for(ii = 1; ii < barCodeLength - 1; ii++)
            {
                if((ii % 2) == 0)
                {
                    barCode[ii] = 48 + (rand() % (57 - 48 + 1));//48-57
                }
                else
                {
                    barCode[ii] = 65 + (rand() % (90 - 65 + 1));//65-90
                }
            }
        }
            break;
    }

    //*****************************************************************************************************************
    //???????
    if(codeType != 4)
    {
        returnValueInt = Print1DBar(5, 80, barCode, codeType, setType);
        printf("barCodeLength: %d\n",barCodeLength);

        if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
        {
            printf("PrinterPrint1DBar('%s') failed, return code: %d\n", barCode, returnValueInt);
            goto ExitLine;
        }
    }
    PCutPaper();//???

    //*****************************************************************************************************************
    //????????????

    ExitLine:
        return  false;
    return TRUE;
}


JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintSample
        (JNIEnv *, jobject, jint mode) {

//    PInit("/sdcard", "/sdcard");
    int ret = PGetLastErrorCode();
    if(ret != 0)
        return false;
    PSetCutterMode(mode);
    if (Print_PDF417() != PRINTER_NO_ERROR)
        return false;
    return true;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintAllString
        (JNIEnv *, jobject, jint mode) {

    PInit("/sdcard", "/sdcard");
    PSetCutterMode(mode);
    bool returnValueBool = true;
    char	errStr[256] = {0x00};

        PSetAreaWidth(0x300); //??????????
        returnValueBool = PSetLeftMargin(0x0);//????????
        if(!returnValueBool)
        {
            printf("PrinterSetLeftMargin failed!\n");
            LOGI("PrinterSetLeftMargin failed!");
            return false;

        }
        returnValueBool = PSetLineSpace(36);//????????
        if(!returnValueBool)
        {
            printf("PrinterSetLineSpace(36) failed!\n");
            LOGI("PrinterSetLineSpace(36) failed!");
            return false;
        }

        returnValueBool = PSetFont(0x00,0x10,0x01);//????????
        if(!returnValueBool)
        {
            printf("PrinterSetLineSpace(0x00,0x10,0x01) failed!\n");
            LOGI("PrinterSetLineSpace(0x00,0x10,0x01) failed!");
            return false;
        }

        returnValueInt = PPrintString("?????????");//????????
        PFeedLine(4);
        returnValueInt =PPrintString("zxcvbnmlkjhgfdsaqwertyuiopZXCVBNMLKJHGFDSAQWERTYUIOP0123456789[]{}-=_+,./<>?`1~!@#$%^&*()");
        PFeedLine(4);
        PSetFont(0x00, 0x11, 0x01);
        PPrintString("1 4 3 8");
        PCutPaper();

    if(returnValueInt != NO_ERROR){
        return false;
    }

    return  true;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintImage
        (JNIEnv *, jobject, jint){

        PInit("/sdcard", "/sdcard");
        returnValueInt = PPrintDiskImage(0, 0, "/sdcard/config/demo.bmp");
        PCutPaper();

        if(returnValueInt != PRINTER_NO_ERROR)
            return false;

        return  true;
}

JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PrintBlackBarcode
        (JNIEnv *, jobject, jint, jint size) {
    PInit("/sdcard", "/sdcard");
    int msize = size;
    if(isInit){
        if(size == 0){
            returnValueInt = PPrintDiskImage(0, 0, "/sdcard/config/block0.bmp");
            PFeedLine(4);
            returnValueInt = PPrintDiskImage(0, 0, "/sdcard/config/block0.bmp");
            PFeedLine(4);
            returnValueInt = PPrintDiskImage(0, 0, "/sdcard/config/block0.bmp");
            PCutPaper();
        }else if(size == 1){
            returnValueInt = PPrintDiskImage(0, 0, "/sdcard/config/block4.bmp");
            PCutPaper();
        }

    }
    if(returnValueInt != NO_ERROR)
        return  false;

    return true;
}

JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_PrintBarCode
        (JNIEnv *env, jobject, jint cutmode, jint codeType) {
    PInit("/sdcard", "/sdcard");
    int mcut = cutmode;
    int type = codeType;
    LOGI("codeTypessss=%d",type);
    switch (type){
        case 0: //pdf
            Print_PDF417();
            break;
        case 1: //QR

            break;
        case 2://EAN
            PrintBarcodeTicket(7);
            break;
        case 3://code39
            PrintBarcodeTicket(9);
            break;
        case 4://code128
            PrintBarcodeTicket(3);
            break;
        case 5:
            PrintBarcodeTicket(0);
        default:
            break;
    }

    char errStr[256] = {0x00};
    PGetLastErrorStr(errStr, 200);
    return env->NewStringUTF(errStr);
}

JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PrintPaperMode
        (JNIEnv *, jobject, jint) {
    PInit("/sdcard", "/sdcard");

    bool ret = true;
    PSetPageMode(400 , 700 , 40 , 40);
    PSetAngle(90);
    PPrintString("???????????1???????????2???????????3???????????4");
    PPrintPage();
    ret = PCutPaper();

    PSetPageMode(400 , 700 , 40 , 40);
    PSetAngle(180);
    PPrintString("???????????1???????????2???????????3???????????4");
    PPrintPage();
    ret = PCutPaper();

    PSetPageMode(400 , 700 , 40 , 40);
    PSetAngle(270);
    PPrintString("???????????1???????????2???????????3???????????4");
    PPrintPage();
    ret = PCutPaper();

    PSetPageMode(400 , 700 , 40 , 40);
    PSetAngle(0);
    PPrintString("???????????1???????????2???????????3???????????4");
    PPrintPage();
    ret = PCutPaper();

    if(!ret)
        return false;


    return true;
}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintString
        (JNIEnv *env, jobject , jbyteArray charArray) {

    char* str = (char*)env->GetByteArrayElements(charArray,0);
    int ret = PPrintString(str);
    return 0;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_CutPaper
        (JNIEnv *, jobject) {
    bool flag = PCutPaper();
    return flag;

}


JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_GetPrintHwInfo
        (JNIEnv *env, jobject) {

    char info[1024] = {0x00};
    bool ret = PGetHWInformation(info, 1000);
    if (!ret) {
        char err[256] = {0x00};
        PGetLastErrorStr(err, 200);
        LOGI("gethwinfo return = %d, hwinfo = %s", ret, info);
        return env->NewStringUTF(err);

    }
    else {
        LOGI("gethwinfo return = %d, hwinfo = %s", ret, info);

    }


    return env->NewStringUTF(info);
}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PrinterStatus
        (JNIEnv *env, jobject) {

        bool ret = PPrinterIsReady();
        int errcode = PGetLastErrorCode();

        if (errcode != 0 || ret == false) {
            LOGI("PGetLastErrorCode return=%d" , errcode);
              return errcode;
        }
        LOGI("errcode = %d" ,errcode);

    return errcode;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_GetAuthority
        (JNIEnv *, jobject) {


}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PGetLastErrorCode
        (JNIEnv *, jobject) {
    int errCode = PGetLastErrorCode();
    return  errCode;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintUserBitmap
        (JNIEnv *env, jobject,jint xpos,jint ypos) {
    bool ret = false;
//    const char* chars= (const  char*)env->GetCharArrayElements(data, 0);
//    LOGI("PrintUserBitmap=%d",sizeof(chars));
//    ret = PPrintUserBitmap(xpos, ypos, chars);
    char *filePath = "/sdcard/cslc/drivertest/TestImage/printerUserBitmap.bmp";
    char *imgFileData = new char[1024 * 10];
    ReadBmpfileData(filePath,imgFileData);
    ret = PPrintUserBitmap(xpos, ypos, imgFileData);

    return ret;
}







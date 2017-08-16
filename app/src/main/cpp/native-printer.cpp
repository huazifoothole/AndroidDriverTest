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
#define	PRINTER_NOT_COMPLETE			(PRINTER_NO_ERROR - 0x07)		//??????��???(????????)
#define	PRINTER_OTHER_ERROR			(PRINTER_NO_ERROR - 0x08)		//????????(??????)
#define	PRINTER_TABPAR_NONE			(PRINTER_NO_ERROR - 0x09)		//???????
#define	PRINTER_HAVE_NOT_INIT		(PRINTER_NO_ERROR - 0x0A)		//��?????
//#define	PRINTER_INVALID_ARGUMNET		(PRINTER_NO_ERROR - 0x0B)		//??????��
#define 	PRINTER_MODE_SWITCH_ERROR		(PRINTER_NO_ERROR - 0x0C)		//???��?????
#define 	PRINTER_HEAD_ERROR			(PRINTER_NO_ERROR - 0x0D)		//???????
#define 	PRINTER_CUT_ERROR			(PRINTER_NO_ERROR - 0x0E)		//?��?????
#define	PRINTER_NOT_FULL			(PRINTER_NO_ERROR - 0x10)		//?????????
#define	PRINTER_FORBID			(PRINTER_NO_ERROR - 0x11)		//????????(???????????)
#define	PRINTER_NOSUPPORT			(PRINTER_NO_ERROR - 0x12)		//?????
#define	PRINTER_MIN_CODE			(PRINTER_NO_ERROR - 0x13)		//??��?????
#define	PRINTER_INVALID_ERROR_CODE		(PRINTER_NO_ERROR - 0x14)		//??��??????


int	returnValueInt = PRINTER_NO_ERROR;
bool isInit = false;
char  mbarCode[256] = {0x00};


JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PInit
        (JNIEnv *env, jobject, jstring j_input,jstring j_output) {

    int returnValueInt = 1;
    const char *input = NULL , *output = NULL;
    if(j_input == NULL || j_output == NULL){
         return 1;
    }
    input = env->GetStringUTFChars(j_input, NULL);
    output = env->GetStringUTFChars(j_output, NULL);

    env->ReleaseStringUTFChars(j_input, input);
    env->ReleaseStringUTFChars(j_output, output);

    returnValueInt = byPInit(input, output);
    if (returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B) {
        //printf("PrinterInit failed, return code: %d\n", returnValueInt);
        LOGI("Init return %d", returnValueInt);
        return returnValueInt;
    }

    return 1;
}



JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintInit
        (JNIEnv * env, jobject) {

    returnValueInt = byPInit("/sdcard", "/sdcard");
    if (returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B) {
        //printf("PrinterInit failed, return code: %d\n", returnValueInt);
        LOGI("Init return %d", returnValueInt);
        return false;
    } else {
        isInit = true;
    }

    return isInit;

}


JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_SetCutMode
        (JNIEnv * env, jobject, jint mode) {

    bool ret = PSetCutterMode(mode);

    char err[256] = {0x00};
    byPGetLastErrorStr(err,200);
    LOGI("setcutmode(1) return %d err = %s",ret,err);


    return  ret;
}



bool PrintPDF417() {
    //*****************************************************************************************************************
    //??????????????
    int		returnValueInt = PRINTER_NO_ERROR;
    bool		returnValueBool = false;
    bool		returnValue = false;
    char    	barCode[256] = {0x00};
    int		barCodeLength = 0;
    int		ii = 0;
    int 		begin = 0;


    bool ret = byPPrinterIsReady();
    int errcode = 0;

    if (!ret) {
        return false;
    }

    //*****************************************************************************************************************
    //????????
    if(!byPSetLineMode())
    {
        goto ExitLine;
    }

    //*****************************************************************************************************************
    //?????????
    if(!byPSetBottomMargin(200))
    {
        goto ExitLine;
    }

    //*****************************************************************************************************************
    //?��??��?????????
//    byPPrinterIsReady();

    //*****************************************************************************************************************
    //??????????
    returnValueBool = byPSetLeftMargin(0x0010);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetLeftMargin failed!\n");
        fflush(stdout);
        goto ExitLine;
    }

    returnValueBool = byPSetLineSpace(10);//?????��?
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(36) failed!\n");
        fflush(stdout);
        goto ExitLine;
    }

    returnValueBool = byPSetFont(0x00, 0x11,0x01);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(0x33,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = byPPrintString("��ʾƱ<ȫ����������3>\n\n");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('��ʾƱ<ȫ����������3>') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    returnValueBool = byPSetLineSpace(14);//?????��??
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(24) failed!\n");
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueBool = byPSetFont(0x00,0x00,0x01);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetFont(0x00,0x00,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = byPPrintString("35073110603460810054   d2WIvi   64319331\n");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('35073110603460810054') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    returnValueInt = byPPrintString("���۵�:06034      06073�� 2006/03/22����");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('���۵�:06034') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }
    byPPrintString("\n");

    returnValueInt = byPPrintString("��:1  �ϼ�:2Ԫ       2006/03/22 12:26:49\n");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('��:1  �ϼ�:2Ԫ') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    //begin = systick();
//    returnValueInt = byPPrintIsComplete(5);//?��?????????
//    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
//    {
//        printf("PrinterPrintIsComplete('%s') failed, return code: %d\n", barCode, returnValueInt);
//        goto ExitLine;
//    }
//    //    begin = systick() - begin;
//    printf("PrinterPrintIsComplete(2)-time is %d\n",begin);

    byPFeedLine(1);//???
    returnValueBool = byPSetFont(0x00,0x10,0x01);
    if(!returnValueBool)
    {
        printf("PrinterSetFont(0x00,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = byPPrintString("�� ʽ Ʊ");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� ʽ Ʊ') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("�� 3 3 2");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 3 3 2') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???

    returnValueInt = byPPrintString("�� 5 8 1");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 5 8 1') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("�� 3 3 2");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 3 3 2') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("�� 5 8 3");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 5 8 3') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("�� 3 3 2");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 3 3 2') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(2);//???
    returnValueBool = byPSetFont(0x00,0x00,0x01);
    if(!returnValueBool)

    {
        printf("PrinterSetFont(2)(0x00,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = byPPrintString("�绰��ѯ:123456���Ų�ѯ:����1234����4321");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�绰��ѯ') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("����������ͬ�����ţ�������");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('��������') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    returnValueInt = byPPrintString("\n\n\n");//????????
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
    returnValueInt = byPrintPDF417(15, 38, 20 , 6, 3, barCode, 32, 2);
//    returnValueInt = byPrintPDF417(10, 10, 1 , 1, 3, barCode, 32, 2);
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintPDF417('%s') failed, return code: %d\n", barCode, returnValueInt);
        goto ExitLine;
    }

    byPCutPaper();//???

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
    byPSetAreaWidth(0x300); //??????????
    returnValueBool = byPSetLeftMargin(0x10);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetLeftMargin failed!\n");
        goto ExitLine;
    }

    returnValueBool = byPSetLineSpace(36);//?????��?
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(36) failed!\n");
        goto ExitLine;
    }

    returnValueBool = byPSetFont(0x00,0x10,0x01);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(0x00,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = byPPrintString("���<ȫ����������3>");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('���<ȫ����������3>') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(3);//???
    returnValueBool = byPSetLineSpace(24);//?????��??
    if(!returnValueBool)
    {
        printf("PrinterSetLineSpace(24) failed!\n");
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueBool = byPSetFont(0x00,0x00,0x01);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetFont(0x00,0x00,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = byPPrintString("35073110603460810054   d2WIvi   64319331");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('35073110603460810054') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("���۵�:06034      06073�� 2006/03/22����");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('���۵�:06034') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("��:1  �ϼ�:2Ԫ       2006/03/22 12:26:49");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('��:1  �ϼ�:2Ԫ') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueBool = byPSetFont(0x00,0x10,0x01);//????????
    if(!returnValueBool)
    {
        printf("PrinterSetFont(0x00,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = byPPrintString("ֱ ѡ Ʊ");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('ֱ ѡ Ʊ') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("�� 3 2 2");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� 3 2 2') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("�� . . .");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� . . .') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("�� . . .");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� . . .') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("�� . . .");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� . . .') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("�� . . .");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�� . . .') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueBool = byPSetFont(0x00,0x00,0x01);
    if(!returnValueBool)
    {
        printf("PrinterSetFont(2)(0x00,0x10,0x01) failed!\n");
        goto ExitLine;
    }

    returnValueInt = byPPrintString("�绰��ѯ:123456���Ų�ѯ:����1234����4321");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('�绰��ѯ') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(1);//???
    returnValueInt = byPPrintString("����������ͬ�����ţ�������");//????????
    if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
    {
        printf("PrinterPrintString('��������') failed, return code: %d\n", returnValueInt);
        goto ExitLine;
    }

    byPFeedLine(3);//???

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
        returnValueInt = byPrint1DBar(5, 80, barCode, codeType, setType);
        printf("barCodeLength: %d\n",barCodeLength);

        if(returnValueInt != PRINTER_NO_ERROR && returnValueInt != 0x0B)
        {
            printf("PrinterPrint1DBar('%s') failed, return code: %d\n", barCode, returnValueInt);
            goto ExitLine;
        }
    }
    byPCutPaper();//???

    //*****************************************************************************************************************
    //?��?????????

    ExitLine:
        return  false;
    return TRUE;
}

JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_GetLastErrStr
        (JNIEnv *env, jobject) {

        char	errStr[256] = {0x00};
        byPGetLastErrorStr(errStr, 200);
        return env->NewStringUTF(errStr);

}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintSample
        (JNIEnv *, jobject, jint mode) {

//    PInit("/sdcard", "/sdcard");
    int ret = byPGetLastErrorCode();
    if(ret != 0)
        return false;
    PSetCutterMode(mode);
    if (PrintPDF417() != PRINTER_NO_ERROR)
        return false;
    return true;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintAllString
        (JNIEnv *, jobject, jint mode) {

    PInit("/sdcard", "/sdcard");
    PSetCutterMode(mode);
    bool returnValueBool = true;
    char	errStr[256] = {0x00};

        byPSetAreaWidth(0x300); //??????????
        returnValueBool = byPSetLeftMargin(0x10);//????????
        if(!returnValueBool)
        {
            printf("PrinterSetLeftMargin failed!\n");
            LOGI("PrinterSetLeftMargin failed!");
            return false;

        }
        returnValueBool = byPSetLineSpace(36);//?????��?
        if(!returnValueBool)
        {
            printf("PrinterSetLineSpace(36) failed!\n");
            LOGI("PrinterSetLineSpace(36) failed!");
            return false;
        }

        returnValueBool = byPSetFont(0x00,0x10,0x01);//????????
        if(!returnValueBool)
        {
            printf("PrinterSetLineSpace(0x00,0x10,0x01) failed!\n");
            LOGI("PrinterSetLineSpace(0x00,0x10,0x01) failed!");
            return false;
        }

        returnValueInt = byPPrintString("�����ַ���");//????????
        byPFeedLine(4);
        returnValueInt =byPPrintString("zxcvbnmlkjhgfdsaqwertyuiopZXCVBNMLKJHGFDSAQWERTYUIOP0123456789[]{}-=_+,./<>?`1~!@#$%^&*()");
        byPFeedLine(4);
        byPSetFont(0x00, 0x11, 0x01);
        byPPrintString("1 4 3 8");
        PCutPaper();

    if(returnValueInt != NO_ERROR){
        return false;
    }

    return  true;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintImage
        (JNIEnv *, jobject, jint){

        PInit("/sdcard", "/sdcard");
        returnValueInt = byPPrintDiskImage(0, 0, "/sdcard/conf/demo.bmp");
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
            returnValueInt = byPPrintDiskImage(0, 0, "/sdcard/conf/block0.bmp");
            PFeedLine(4);
            returnValueInt = byPPrintDiskImage(0, 0, "/sdcard/conf/block0.bmp");
            PFeedLine(4);
            returnValueInt = byPPrintDiskImage(0, 0, "/sdcard/conf/block0.bmp");
            PCutPaper();
        }else if(size == 1){
            returnValueInt = byPPrintDiskImage(0, 0, "/sdcard/conf/block4.bmp");
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
            PrintPDF417();
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
    byPGetLastErrorStr(errStr, 200);
    return env->NewStringUTF(errStr);
}

JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PrintPaperMode
        (JNIEnv *, jobject, jint) {
    PInit("/sdcard", "/sdcard");

    bool ret = true;
    PSetPageMode(400 , 700 , 40 , 40);
    PSetAngle(90);
    PPrintString("�й�������Ʊ1�й�������Ʊ2�й�������Ʊ3�й�������Ʊ4");
    PPrintPage();
    ret = PCutPaper();

    PSetPageMode(400 , 700 , 40 , 40);
    PSetAngle(180);
    PPrintString("�й�������Ʊ1�й�������Ʊ2�й�������Ʊ3�й�������Ʊ4");
    PPrintPage();
    ret = PCutPaper();

    PSetPageMode(400 , 700 , 40 , 40);
    PSetAngle(270);
    PPrintString("�й�������Ʊ1�й�������Ʊ2�й�������Ʊ3�й�������Ʊ4");
    PPrintPage();
    ret = PCutPaper();

    PSetPageMode(400 , 700 , 40 , 40);
    PSetAngle(0);
    PPrintString("�й�������Ʊ1�й�������Ʊ2�й�������Ʊ3�й�������Ʊ4");
    PPrintPage();
    ret = PCutPaper();

    if(!ret)
        return false;


    return true;
}

JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PrintString
        (JNIEnv *, jobject , jstring str) {

    LOGI("byPPrintString input");
    int ret = byPPrintString("cutpaper test\n");

    if(ret != NO_ERROR)
        return false;
    PCutPaper();

    char err[256] = {0x00};
    byPGetLastErrorStr(err,200);
    LOGI("byPPrintString return %d err = %s",ret,err);


    return true;
}

JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_CutPaper
        (JNIEnv *, jobject) {
    bool ret = PCutPaper();

}

JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PSetPageMode
        (JNIEnv *, jobject, jint width ,jint heigt, jint leftTop_x, jint leftTop_y) {
    int wid = width;
    int h = heigt;
    int leftx = leftTop_x;
    int lefty = leftTop_y;
    PSetPageMode(wid , h , leftx , lefty);
}

JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_GetPrintHwInfo
        (JNIEnv *env, jobject) {

//    PInit("/sdcard", "/sdcard");
    char info[1024] = {0x00};
    bool ret = PGetHWInformation(info, 1000);
    if (!ret) {
        char err[256] = {0x00};
        byPGetLastErrorStr(err, 200);
        LOGI("gethwinfo return = %d, hwinfo = %s", ret, info);
        return env->NewStringUTF(err);

    }
    else {
        LOGI("gethwinfo return = %d, hwinfo = %s", ret, info);

    }
    bool isready = byPPrinterIsReady();
    LOGI("printerIsReady return = %d",isready);

    return env->NewStringUTF(info);
}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PrinterStatus
        (JNIEnv *env, jobject) {

        bool ret = byPPrinterIsReady();
        int errcode = byPGetLastErrorCode();

        if (errcode != 0 || ret == false) {
            LOGI("byPGetLastErrorCode return=%d" , errcode);
              return errcode;
        }
        LOGI("errcode = %d" ,errcode);

    return errcode;
}

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_GetAuthority
        (JNIEnv *, jobject) {


}

JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_GetLastErrCode
        (JNIEnv *, jobject) {
    int errCode = byPGetLastErrorCode();
    return  errCode;
}





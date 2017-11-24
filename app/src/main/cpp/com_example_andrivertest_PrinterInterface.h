/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_example_andrivertest_PrinterInterface */

#ifndef _Included_com_example_andrivertest_PrinterInterface
#define _Included_com_example_andrivertest_PrinterInterface
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintInit
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintInit
  (JNIEnv *, jobject);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PGetLastErrorCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PGetLastErrorCode
        (JNIEnv *, jobject);


/*
 * Class:     com_example_andrivertest_PGetLastErrorCode
 * Method:    GetLastErrStr
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT void JNICALL Java_com_example_andrivertest_PrinterInterface_PGetLastErrorStr
        (JNIEnv *, jobject, jcharArray ,jint);
/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    SetAllcutOrHalfcut
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_example_andrivertest_PrinterInterface_SetAllcutOrHalfcut
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintSample
 * Signature: (I)I
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintSample
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintAllString
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintAllString
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintImage
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PrintImage
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintBlackBarcode
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PrintBlackBarcode
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintCodePaper
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_PrintCodePaper
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintContinue
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_PrintContinue
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintPaperMode
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PrintPaperMode
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintSpeedTest
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_PrintSpeedTest
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintCutPaperSpeed
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_PrintCutPaperSpeed
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintBarCode
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_PrintBarCode
  (JNIEnv *, jobject, jint, jint);


JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintString
        (JNIEnv *, jobject , jbyteArray);

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_CutPaper
        (JNIEnv *, jobject);



JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_GetPrintHwInfo
        (JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PrinterStatus
        (JNIEnv *, jobject);

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_GetAuthority
        (JNIEnv *, jobject);

JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_GetPDFCode
        (JNIEnv *, jobject);



/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PInit
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PInit
        (JNIEnv *, jobject, jstring ,jstring);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetCutterMode
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetCutterMode
        (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PGetCutterMode
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PGetCutterMode
        (JNIEnv *, jobject, jobject);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetFont
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetFont
        (JNIEnv *, jobject, jint ,jint ,jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetFontEmpha
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetFontEmpha
        (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetLineSpace
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetLineSpace
        (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetCharSpace
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetCharSpace
        (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetLeftMargin
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetLeftMargin
        (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetAreaWidth
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetAreaWidth
        (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PQueryCapability
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PQueryCapability
        (JNIEnv *, jobject);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PPrinterIsReady
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PPrinterIsReady
        (JNIEnv *, jobject);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PGetDpi
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PGetDpi
        (JNIEnv *, jobject, jobject , jobject  );

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PGetHWInformation
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PGetHWInformation
        (JNIEnv *, jobject, jobject , jint );


/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PGetSWVersion
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_andrivertest_PrinterInterface_PGetSWVersion
        (JNIEnv *, jobject);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PFeedLine
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT void JNICALL Java_com_example_andrivertest_PrinterInterface_PFeedLine
        (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PrintPDF417
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT int JNICALL Java_com_example_andrivertest_PrinterInterface_PrintPDF417
        (JNIEnv *, jobject, jint, jint, jint, jint, jint, jstring , jint, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetUserChar
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PSetUserChar
        (JNIEnv *, jobject, jint, jint ,jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PUnsetUserChar
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PUnsetUserChar
        (JNIEnv *, jobject, jint,  jint);


/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PPrintUserChar
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintUserChar
        (JNIEnv *, jobject,jint,  jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PPrintDiskImage
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT int JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintDiskImage
        (JNIEnv *, jobject, jint,  jint , jstring);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PPrintBlackMark
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintBlackMark
        (JNIEnv *, jobject, jcharArray ,  jint );

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PPrintBlackMark
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT bool JNICALL Java_com_example_andrivertest_PrinterInterface_PGetTopMargin
        (JNIEnv *, jobject, jobject );

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PPrintIsComplete
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jint JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintIsComplete
        (JNIEnv *, jobject, jint );

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PGetPrintLength
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jlong JNICALL Java_com_example_andrivertest_PrinterInterface_PGetPrintLength
        (JNIEnv *, jobject);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PLoadLogoImage
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PLoadLogoImage
        (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PLoadDiskLogo
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PLoadDiskLogo
        (JNIEnv *, jobject, jint, jobjectArray);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PPrintLogo
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintLogo
        (JNIEnv *, jobject, jint, jint,jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetAngle
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetAngle
        (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PExec_ESC_POS
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PExecESCPOS
        (JNIEnv *, jobject, jcharArray , jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetPageMode
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetPageMode
        (JNIEnv *, jobject, jint ,jint, jint, jint);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PSetLineMode
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PSetLineMode
        (JNIEnv *, jobject);

/*
 * Class:     com_example_andrivertest_PrinterInterface
 * Method:    PPrintPage
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintPage
        (JNIEnv *, jobject);

JNIEXPORT jboolean JNICALL Java_com_example_andrivertest_PrinterInterface_PPrintUserBitmap
        (JNIEnv *, jobject,jint,jint);



#ifdef __cplusplus
}
#endif
#endif

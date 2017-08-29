package com.example.andrivertest;

import java.util.List;

/**
 * Created by chandler on 2017/5/11.
 */

public class PrinterInterface {
    static{
        System.loadLibrary("usb1.0");
        System.loadLibrary("ConfigFileINI");
        System.loadLibrary("flog");
        System.loadLibrary("bitmap");
        System.loadLibrary("scanprn");
        System.loadLibrary("ScanPrnWrap");
        System.loadLibrary("native-printer");
    }


    public static native int PInit(String input, String output);

    public native boolean PSetCutterMode(int mode);

    public  native boolean PGetCutterMode(Integer mode);

    public native boolean PSetFont(int index, int size,int aligment);

    public native boolean PSetFontEmpha(int n);

    public native boolean PSetLineSpace(int size);

    public native boolean PSetCharSpace(int size);

    public native boolean PSetLeftMargin(int size);

    public native boolean PSetAreaWidth(int size);

    public native int PQueryCapability();

    public native boolean PPrinterIsReady();

    public native boolean PGetDpi(Integer widthDpi, Integer heigthDpi);

    public native boolean PGetHWInformation(Byte hwinfo, int length);

    public native String PGetSWVersion();

    public native void PFeedLine(int count);

    public native boolean PrintInit();

    public  native int PGetLastErrorCode();

    public  native  void PGetLastErrorStr(char[] err,int length);

    public  native int PrintPDF417(int mode_width, int mode_height, int data_rows, int data_columns, int err_level, String pdfStr, int length, int mode);

    public native boolean PSetUserChar(int c1,int c2,int m, char[] data,int length);

    public native boolean PUnsetUserChar(int c1,int c2);

    public native boolean PPrintUserChar(int c1,int c2);

    public native int PPrintDiskImage(int xpos, int ypos, String path);

    public native boolean PPrintBlackMark(char[] barcode, int length);

    public native boolean PGetTopMargin(Integer margin);

    public native int PPrintIsComplete(int timeout);

    public native long PGetPrintLength();

    public native boolean PLoadLogoImage(int imgCount, List<byte[]> imgList);

    public native boolean PLoadDiskLogo(int imgCount, String[] imgFileList);

    public native boolean PPrintLogo(int x, int y,int index);

    public native boolean PSetAngle(int angle);

    public native boolean PExecESCPOS(char[] s, int length);

    public native boolean PSetPageMode(int width, int height, int leftTop_x, int leftTop_y);

    public native boolean  PSetLineMode();

    public native boolean  PPrintPage();

    public native int PPrintString(byte[] str);



    //change ini file , set allcut or halfcut
    public native void SetAllcutOrHalfcut(int mode);

    public native boolean PrintSample(int cutmode);

    public native boolean PrintAllString(int cutmode);

    public native boolean PrintImage(int cutmode);

    public native boolean PrintBlackBarcode(int cutmode,int size);

    public native String PrintCodePaper(int cutmode,int code);

    public native String PrintContinue(int cutmode , int time);

    public native boolean PrintPaperMode(int cutmode);

    public native String PrintSpeedTest(int cutmode);

    public native String PrintCutPaperSpeed(int cutmode);

    public native String PrintBarCode(int cutmode ,int codeType);



    public native boolean CutPaper();


    public static native String GetPrintHwInfo();

    public static native int PrinterStatus();

    public static native boolean GetAuthority();

    public static native String GetPDFCode();

    public  int NO_ERROR = 0;

    public final int NO_PRINTER = 1;

    public final int DATA_LINE_ERROR = 2;

    public final int POWER_ERROR = 3;

    public final int PRINTER_IS_BUSY = 4;

    public final int TIME_OUT = 5;

    public final int GET_HWVERSION_ERROR = 6;

    public final int START_ERROR = 7;

    public final int COVER_ERROR = 8;

    public final int PAPER_EMPTY_ERROR = 9;

    public final int PAPER_JAM_ERROR = 10;

    public final int PAPER_FEW_ERROR = 11;

    public  final int PRINT_NOT_COMPELTE =12 ;

    public final int PRINTER_CUTTER_ERROR = 13;

    public final int SET_CUTMODE_ERROR = 20;

    public final int OTHER_ERROR = 500;

}

package com.example.andrivertest;

import android.util.Log;

import java.io.File;
import java.io.FileInputStream;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by chandler on 2017/8/14.
 */

public class PrinterScript {

    private PrinterInterface mPrinterAPI = new PrinterInterface();

    /*
    * 打印机命令处理 , 调用成功返回0，失败返回-1，输出参数存outlist*/
    public int handleCommands(String cmd, final List<String> argList, List<String> outlist) throws UnsupportedEncodingException{
        int ret = 0;

        String tmp = "cmdName=" + cmd ;
        outlist.add(tmp);//首先存儲被调用的接口名
        //接口执行成功日志
        String succStr = "ExecResult=success";
        //失败日志
        String failStr = "ExecResult=failed";
        //参数错误日志
        String argError = "InterfaceParamNumberError";

        int argNum = 0;
        if(!argList.isEmpty()){
            argNum = argList.size();
        }

        if(0 == cmd.compareTo("PInit")){
            if(2 == argNum){
                String input = argList.get(0);
                String output = argList.get(1);
                Log.i(MainActivity.TAG, "input = " + input + " output=" + output);
                int flag = mPrinterAPI.PInit(input, output);
                if(flag == 0){
                    ret = 0;
                    outlist.add(succStr);
                }else {
                    ret = -1;
                    outlist.add(failStr);
                }
                String tmpStr = "ErrorCode=" + flag;
                outlist.add(tmpStr);

            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PPrintString")){
            if(1 == argNum){

                byte[] printArr = new byte[argList.get(0).length()*2];
                //java向c++传递中文字符 ，转化为gbk编码
                // getbytes("gbk")会抛出UnsupportedEncodingException Exception异常 ，需在函数上加上throws UnsupportedEncodingException。
                printArr = argList.get(0).getBytes("gbk");
                int flag = mPrinterAPI.PPrintString(printArr);
                if(flag != 0){
                    ret = -1;
                    outlist.add(failStr);

                }else{
                    ret = 0;
                    outlist.add(succStr);
                }

                String tmpStr = "ErrorCode="+flag;
                outlist.add(tmpStr);

            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PSetCutterMode")){
            if(argNum == 1){
                int mode = Integer.parseInt(argList.get(0));
                boolean flag = mPrinterAPI.PSetCutterMode(mode);
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
            }else{
                outlist.add(argError);
            }


        }
        else if(0 == cmd.compareTo("PGetCutterMode")){
            Integer mode = new Integer(0);
            boolean flag = mPrinterAPI.PGetCutterMode(mode);
            if(flag){
                ret = 0;
                outlist.add(succStr);
            }else{
                ret = -1;
                outlist.add(failStr);
            }
            String tmpStr = "mode=" + mode;
            outlist.add(tmpStr);
        }
        else if(0 == cmd.compareTo("PSetFont")){
            if(3 == argNum){
                boolean flag = mPrinterAPI.PSetFont(Integer.parseInt(argList.get(0)),Integer.parseInt(argList.get(1)),
                        Integer.parseInt(argList.get(2)));
                Log.i(MainActivity.TAG, "setfont flag =" + flag);
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
            }else{
                outlist.add(argError);
            }

        }
        else if(0 == cmd.compareTo("PSetFontEmpha")){
            if(1 == argNum){
                boolean flag = mPrinterAPI.PSetFontEmpha(Integer.parseInt(argList.get(0)));
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PSetLineSpace")){
            if(1 == argNum){
                boolean flag = mPrinterAPI.PSetLineSpace(Integer.parseInt(argList.get(0)));
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PSetCharSpace")){
            if(1 == argNum){
                boolean flag = mPrinterAPI.PSetCharSpace(Integer.parseInt(argList.get(0)));
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PSetLeftMargin")){
            if(1 == argNum){
                boolean flag = mPrinterAPI.PSetLeftMargin(Integer.parseInt(argList.get(0)));
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PSetAreaWidth")){
            if(1 == argNum){
                boolean flag = mPrinterAPI.PSetAreaWidth(Integer.parseInt(argList.get(0)));
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PQueryCapability")){
            if(0 == argNum){
                int value = mPrinterAPI.PQueryCapability();
                if(value != 0){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
                String tmpStr = "Capability=" + value;
                outlist.add(tmpStr);
            }else{
                outlist.add(argError);
            }

        }
        else if(0 == cmd.compareTo("PPrinterIsReady")){
            if(0 == argNum){
                boolean flag = mPrinterAPI.PPrinterIsReady();
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PGetDpi")){
            if(2 == argNum){
                Integer widthDpi = new Integer(0) ;
                Integer heightDpi = new Integer(0);


                boolean flag = mPrinterAPI.PGetDpi(widthDpi,heightDpi);

                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
                String tmpW, tmpH;
                tmpW = "width=" + widthDpi;
                tmpH = "height=" + heightDpi;
                outlist.add(tmpW);
                outlist.add(tmpH);
            }else{
                outlist.add(argError);
            }
        }
        else if( 0== cmd.compareTo("PGetHWInformation")){
            String hwInfo = mPrinterAPI.GetPrintHwInfo();
            if(2 == argNum){
                if(hwInfo != ""){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
                String hwinfo = "hwinfo=" + hwInfo;
                outlist.add(hwinfo);
            }else {
                outlist.add(argError);
            }

        }
        else if(0 == cmd.compareTo("PGetSWVersion")){
            String version = mPrinterAPI.PGetSWVersion();
            if(0 == version.compareTo("false")){
                ret = -1;
                outlist.add(failStr);
            }else{
                ret = 0;
                outlist.add(succStr);
            }

            String tmpStr = "SWVersion=" + version;
            outlist.add(tmpStr);
        }
        else if(0 == cmd.compareTo("PGetLastErrorCode")) {

            if (argNum == 0) {
                ret = 0;
                int errcode = mPrinterAPI.PGetLastErrorCode();
            } else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PGetLastErrorStr")){
            if(argNum == 2){
                ret = 0;
                char[] chars = new char[256];
                mPrinterAPI.PGetLastErrorStr(chars,256);
                outlist.add(succStr);
            }else{
                outlist.add(argError);
            }

        }
        else if(0 == cmd.compareTo("PFeddLine")){
            if(argNum == 1){
                mPrinterAPI.PFeedLine(Integer.parseInt(argList.get(0)));
                ret = 0;
                outlist.add(succStr);
            }else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PCutPaper")){
            if(argNum == 0){
                boolean flag = mPrinterAPI.CutPaper();
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else {
                    ret = -1;
                    outlist.add(failStr);
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PrintPDF417")){
            if (argNum == 8){
                int errCode = mPrinterAPI.PrintPDF417(Integer.parseInt(argList.get(0)),
                        Integer.parseInt(argList.get(1)),
                        Integer.parseInt(argList.get(2)),
                        Integer.parseInt(argList.get(3)),
                        Integer.parseInt(argList.get(4)),
                        argList.get(5),
                        Integer.parseInt(argList.get(6)),
                        Integer.parseInt(argList.get(7)));
                if(ret != 0){
                    ret = -1;
                    outlist.add(failStr);
                }else{
                    ret = 0;
                    outlist.add(succStr);
                }

                String tmpStr = "Errorcode="+ret;
                outlist.add(tmpStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PSetUserChar")){
            if(argNum == 5){
                char buf9[] = {0,0,0,127,255,254,64,24,1,64,24,1,127,255,254,64,24,1,64,24,1,127,255,254,0,0,0};  //9*24  田
                char buf12[] = {0,0,0,127,255,127,64,129,2,64,129,2,64,129,2,64,129,2,64,129,2,64,129,2,64,129,2,64,129,2, 127,255,127,0,0,0}; //12*24 目
                boolean flag = false;
                String tmpError = "";
                int num = Integer.parseInt(argList.get(1)) - Integer.parseInt(argList.get(0)) + 1;
                if(num > 0){
                    if(9 == Integer.parseInt(argList.get(2))){
                        char tmpBuf9[] = new char[num*27];
                        for (int i = 0; i < num*27; i ++)
                        {
                            tmpBuf9[i] = buf9[i%27];
                        }
                        flag = mPrinterAPI.PSetUserChar(Integer.parseInt(argList.get(0)), Integer.parseInt(argList.get(1)), 9, tmpBuf9, num*27);
                    }else if(12 == Integer.parseInt(argList.get(2))){
                        char tmpBuf12[] = new char[num*36];
                        for(int i=0; i< num*36; i++)
                        {
                            tmpBuf12[i] = buf12[i%36];
                        }
                        flag = mPrinterAPI.PSetUserChar(Integer.parseInt(argList.get(0)), Integer.parseInt(argList.get(1)), 12,  tmpBuf12, num * 36);
                    }else {
                        tmpError = "DetailErr=ThirdArgError";
                    }
                }else {
                    tmpError = "DetailErr=FirstArgLargerThanSecond";
                }
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else {
                    ret = -1;
                    outlist.add(failStr);
                }

            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PUnsetUserChar")){
            if(argNum == 2){
                boolean flag = mPrinterAPI.PUnsetUserChar(Integer.parseInt(argList.get(0)),
                        Integer.parseInt(argList.get(1)));
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret =-1;
                    outlist.add(failStr);
                }
            }else {
                outlist.add(argError);
            }

        }
        else if(0 == cmd.compareTo("PPrintUserChar")){
            if(argNum == 2){
                boolean flag = mPrinterAPI.PPrintUserChar(Integer.parseInt(argList.get(0)),
                        Integer.parseInt(argList.get(1)));
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret =-1;
                    outlist.add(failStr);
                }
            }else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PPrintUserBitmap")){
            if(argNum == 3){

            }else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PPrintDiskImage")){
            if(argNum == 3){
                Log.i(MainActivity.TAG, "diskimage path="+argList.get(2));
                int flag =  mPrinterAPI.PPrintDiskImage(Integer.parseInt(argList.get(0)),
                        Integer.parseInt(argList.get(1)),
                        argList.get(2));

                if(flag != 0){
                    ret = -1;
                    outlist.add(failStr);
                }else {
                    ret = 0;
                    outlist.add(succStr);
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PPrintBlackMark")){
            if(argNum == 2){
                char[] barcode = argList.get(0).toCharArray();
                boolean flag = mPrinterAPI.PPrintBlackMark(barcode, barcode.length);
                if (flag) {
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PGetTopMargin")){
            if(argNum == 1){
                Integer margin = new Integer(0);
                boolean flag = mPrinterAPI.PGetTopMargin(margin);
                if(flag){
                    ret = -1;
                    outlist.add(failStr);
                }else{
                    ret = 0;
                    outlist.add(succStr);
                }

                String tmpStr = "topMargin=" + margin;
                outlist.add(tmpStr);
            }else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PPrintIsComplete")){
            if(argNum == 1){

                int flag = mPrinterAPI.PPrintIsComplete(Integer.parseInt(argList.get(0)));
                if(flag != 0){
                    ret =0;
                    outlist.add(succStr);
                }else{
                    ret =-1;
                    outlist.add(failStr);
                }
                String tmpStr = "ErrorCode=" + flag;
                outlist.add(tmpStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PGetPrintLength")){
            if(argNum == 0){
                long length = mPrinterAPI.PGetPrintLength();
                ret = 0;
                outlist.add(succStr);
                String tmpStr = "PrintLength=" + length;
                outlist.add(tmpStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PLoadLogoImage")){
            if(argNum == 2){
                int count = Integer.parseInt(argList.get(0));
                String filePath = "";
                List<byte[]> imageList = new ArrayList<byte[]>();
                for(int i=0; i< count; i++){
                    filePath = "/sdcard/TestImage/logoImage/logoImage" + (i + 1) + ".bmp";
                    File file = new File(filePath);
                    if(!file.exists() || !file.isFile()){
                        Log.i(MainActivity.TAG, "文件不存在");
                        break;
                    }

                    try{
                        FileInputStream fileInputStream = new FileInputStream(file);
                        int length = fileInputStream.available();
                        Log.i(MainActivity.TAG, "image size=" + length);
                        byte[] tmpByte = new byte[length+1];
                        fileInputStream.read(tmpByte);
                        imageList.add(tmpByte);
                        fileInputStream.close();

                    }catch (Exception e){
                        e.printStackTrace();
                    }
                }
                Log.i(MainActivity.TAG, "imagelList ="+imageList.size()+" imageList[0] size="+imageList.get(0).length);
                mPrinterAPI.PLoadLogoImage(count,imageList);

            }
        }
        else if(0 == cmd.compareTo("PLoadDiskLogo")){
            if(argNum == 2){
                int count = Integer.parseInt(argList.get(0));
                String[] imageFileList = new String[count];
                for(int i=0;i<count;i++){
                    imageFileList[i] =  "/sdcard/TestImage/diskLogo/diskLogo"+ (i + 1)+".bmp";
                }
                boolean flag = mPrinterAPI.PLoadDiskLogo(count, imageFileList);
            }else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PPrintLogo")){
            if (argNum == 3) {
                boolean flag = mPrinterAPI.PPrintLogo(Integer.parseInt(argList.get(0)), Integer.parseInt(argList.get(1)),
                        Integer.parseInt(argList.get(2)));
                if(flag){
                    ret = -1;
                    outlist.add(failStr);
                }else{
                    ret = 0;
                    outlist.add(succStr);
                }
            } else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PSetAngle")){
            if (argNum == 1) {
                boolean flag = mPrinterAPI.PSetAngle(Integer.parseInt(argList.get(0)));
                if(flag){
                    ret = -1;
                    outlist.add(failStr);
                }else{
                    ret = 0;
                    outlist.add(succStr);
                }
            } else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PExec_ESC_POS")){
            if(argNum == 2){
                char command[] =argList.get(0).toCharArray();
                boolean flag = mPrinterAPI.PExecESCPOS(command, Integer.parseInt(argList.get(1)));
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else {
                    ret = -1;
                    outlist.add(failStr);
                }
            }else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PSetPageMode")){
            if(argNum == 4){

                boolean flag = mPrinterAPI.PSetPageMode(Integer.parseInt(argList.get(0)),
                        Integer.parseInt(argList.get(1)),
                        Integer.parseInt(argList.get(2)),
                        Integer.parseInt(argList.get(3)));
                if(flag){
                    ret = -1;
                    outlist.add(failStr);
                }else{
                    ret = 0;
                    outlist.add(succStr);
                }

            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PSetLineMode")){
            if(argNum == 0){

                boolean flag = mPrinterAPI.PSetLineMode();
                if(flag){
                    ret = -1;
                    outlist.add(failStr);
                }else{
                    ret = 0;
                    outlist.add(succStr);
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("PPrintPage")){

            boolean flag = mPrinterAPI.PPrintPage();
            if(flag){
                ret = -1;
                outlist.add(failStr);
            }else{
                ret = 0;
                outlist.add(succStr);
            }
        }
        else if(0 == cmd.compareTo("PrintSample")){
            if(argNum == 1){
                boolean flag = mPrinterAPI.PrintSample(0);
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else {
                    ret = -1;
                    outlist.add(failStr);
                }
            }else {
                outlist.add(argError);
            }

        }else{
            outlist.add(argError);
        }




        //调用GetLastErrorCode和GetLastErrorStr确保接口执行正确

        int code = mPrinterAPI.PGetLastErrorCode();
        String lastErrCode = " LastErrCode=" + code;
        outlist.add(lastErrCode);


        char[] chars = new char[256];
        mPrinterAPI.PGetLastErrorStr(chars,256);
        String errString = new String(chars, 0, chars.length);
        String lastErrStr = " LastErrStr=" + errString;
        outlist.add(lastErrStr);

        return  ret;
    }




}

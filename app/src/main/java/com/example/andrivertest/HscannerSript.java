package com.example.andrivertest;

import android.util.Log;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.List;

import static com.example.andrivertest.BCRInterface.BCRGetLastErrorCode;

/**
 * Created by chandler on 2017/8/16.
 */

public class HscannerSript {


    private BCRInterface mBCRInerface = new BCRInterface();

    public int handleCommands(String cmd, List<String> argList, List<String> outlist) throws UnsupportedEncodingException{
        int ret = 0;

        String tmp = "cmdName =" + cmd;
        outlist.add(tmp);//存儲被调用的接口名
        String succStr = " ExecResult=success";
        String failStr = " ExecResult=failed";
        String argError = " InterfaceParamNumberError";
        //执行时间
        String execTimeStr = " ExecTime=";

        int argNum = 0;
        if (!argList.isEmpty()) {
            argNum = argList.size();
        }

        long timer1 = System.nanoTime();

        if (0 == cmd.compareTo("BCRInit")) {
            Log.i(MainActivity.TAG, "call PInit argNum=" + argNum);
            if (3 == argNum) {
                int flag = mBCRInerface.BCRInit();
                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");
                if(flag == 0){
                    ret = 0;
                    outlist.add(succStr);
                }else {
                    ret = -1;
                    outlist.add(failStr);
                }
                String tmpStr = "ErrorCode=" + flag;
                outlist.add(tmpStr);
            }else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRClose")) {
            if(argNum == 0){
                mBCRInerface.BCRClose();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                ret = 0;
                outlist.add(succStr);
            }else{
                outlist.add(argError);
            }

        }
        else if(0 == cmd.compareTo("BCRStartScan")){
            if(0 == argNum){
                boolean flag = mBCRInerface.BCRStartScan();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else {
                    ret =-1;
                    outlist.add(failStr);
                }
            }else{
                argList.add(argError);
            }

        }
        else if(0 == cmd.compareTo("BCRStopScan")){
            if(0 == argNum){
                boolean flag = mBCRInerface.BCRStopScan();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else {
                    ret =-1;
                    outlist.add(failStr);
                }
            }else{
                argList.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRScanIsComplete")){
            if(0 == argNum){
                boolean flag = mBCRInerface.BCRScanIsComplete();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else {
                    ret =-1;
                    outlist.add(failStr);
                }
            }else{
                argList.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRIsReady")){
            if(0 == argNum){
                boolean flag = mBCRInerface.BCRIsReady();
                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else {
                    ret =-1;
                    outlist.add(failStr);
                }
            }else{
                argList.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRGetTicketInfo")){
            if(2 == argNum){
                byte[] info = new byte[4096];
                int length = mBCRInerface.BCRGetTicketInfo(info, 4096);

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                if(length == 0){//读取失败
                    ret = -1;
                    outlist.add(failStr);
                }else{
                    ret = 0;
                    outlist.add(succStr);
                }

                try {
                    FileOutputStream fos = new FileOutputStream("/sdcard/ticketinfo.dat");
                    fos.write(info);
                    fos.close();
                }catch (IOException e){
                    e.printStackTrace();
                }

                String ticketMsg = new String(info, 7, length, "GBK");
                Log.i(MainActivity.TAG, "tiketinfo="+ticketMsg +
                        "\nlength="+length);
                String tmpStr = "ticketRealSize=" + length+ "\nticketinfo="+ticketMsg;
                outlist.add(tmpStr);

            }
        }
        else if(0 == cmd.compareTo("BCRGetHWInformation")){
            if(2 == argNum){
                byte[] info = new byte[1024];
                Log.i(MainActivity.TAG, "byte size=" + info.length);
                boolean flag = mBCRInerface.BCRGetHWInformation(info, 1024);

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                if(flag){
                    ret =0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
                String hw = new String(info,"gbk");
                String tmpStr =  "hwinfo =\n" + hw;
                outlist.add(tmpStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRBeep")){
            if(1 == argNum){
                boolean flag = mBCRInerface.BCRBeep(Integer.parseInt(argList.get(0)));

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

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
        else if(0 == cmd.compareTo("BCRUserLEDOff")){
            if(0 == argNum){
                mBCRInerface.BCRUserLEDOff();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                ret = 0;
                outlist.add(succStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRUserLEDOn")){
            if(1 == argNum){
                boolean flag = mBCRInerface.BCRUserLEDOn(Integer.parseInt(argList.get(0)));

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

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
        else if(0 == cmd.compareTo("BCRAimOff")){
            if(0 == argNum){
                mBCRInerface.BCRAimOff();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                ret = 0;
                outlist.add(succStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRAimOn")){
            if(0 == argNum){
                mBCRInerface.BCRAimOn();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                ret = 0;
                outlist.add(succStr);
            }else{
                outlist.add(argError);
            }
        } else if(0 == cmd.compareTo("BCRSetScanMode")){
            if(1 == argNum){
                boolean flag = mBCRInerface.BCRSetScanMode(Integer.parseInt(argList.get(0)));

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

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
        else if(0 == cmd.compareTo("BCRGetScanMode")){
            if(1 == argNum){
                Integer mode = new Integer(0);
                boolean flag = mBCRInerface.BCRGetScanMode(mode);

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }

                String tmpStr = "ScanMode= " + mode;
                outlist.add(tmpStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRGetTriggerStatus")){
            if(1 == argNum){
                Integer mode = new Integer(0);
                mBCRInerface.BCRGetTriggerStatus(mode);

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                    ret = 0;
                    outlist.add(succStr);

                String tmpStr = "ScanMode= " + mode;
                outlist.add(tmpStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRGetScanDpi")){
            if(2 == argNum){
                Integer widthDpi = new Integer(0) ;
                Integer heightDpi = new Integer(0);

                mBCRInerface.BCRGetScanDpi(widthDpi,heightDpi);

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                ret = 0;
                outlist.add(succStr);

                String tmpW, tmpH;
                tmpW = "width=" + widthDpi;
                tmpH = "height=" + heightDpi;
                outlist.add(tmpW);
                outlist.add(tmpH);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRGetImageSize")){
            if(3 == argNum){
                Integer width = new Integer(0);
                Integer height = new Integer(0);
                Integer buffersize = new Integer(0);
                boolean flag = mBCRInerface.BCRGetImageSize(width, height, buffersize);

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                if (flag)
                {
                    ret =0;  //success
                    outlist.add(succStr);
                } else {
                    ret = -1;  //failed
                    outlist.add(failStr);
                }
                String str = "width=" + width + " height=" + height +" buffsize=" + buffersize;
                outlist.add(str);
            }else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCREnableBeep")){
            if(0 == argNum){
                mBCRInerface.BCREnableBeep();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                ret =0;
                outlist.add(succStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRDisableBeep")){
            if(0 == argNum){
                mBCRInerface.BCRDisableBeep();


                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms");
                ret =0;
                outlist.add(succStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRClearBuffer")){
            if(0 == argNum){
                mBCRInerface.BCRClearBuffer();
                ret =0;
                outlist.add(succStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRGetSWVersion")){
            if(2 == argNum){
                String version = mBCRInerface.BCRGetSWVersion();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                ret = 0;
                outlist.add(succStr);
                String tmpStr = "swVersion=" + version;
                outlist.add(tmpStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRGetImage")){
            if(2 == argNum){
                byte[] image = new byte[4096*100];
                Integer length = new Integer(0);
                int size = mBCRInerface.BCRGetImage(image, length);

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms");

                if(size == 0){//读取失败
                    ret = -1;
                    outlist.add(failStr);
                }else{
                    ret = 0;
                    outlist.add(succStr);
                }
                String tmpStr = "imageSize =" + size;
                outlist.add(tmpStr);

                //将Image数据写入本地文件
                try {
                    FileOutputStream fos = new FileOutputStream("/sdcard/Image.dat");
                    fos.write(image);
                    fos.close();
                }catch (IOException e){
                    e.printStackTrace();
                }

            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRResetComm")){
            if(0 == argNum){
                boolean flag = mBCRInerface.BCRResetComm();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms");
                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }
            }else {
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRWakeup")){
            if(0 == argNum){
                boolean flag = mBCRInerface.BCRWakeup();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

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
        else if(0 == cmd.compareTo("BCRSleep")){
            if(1 == argNum){
                boolean flag = mBCRInerface.BCRSleep(Integer.parseInt(argList.get(0)));

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

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
        else if(0 == cmd.compareTo("BCRDisableCode")){
            if(1 == argNum){
                boolean flag = mBCRInerface.BCRDisableCode(Integer.parseInt(argList.get(0)));

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

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
        else if(0 == cmd.compareTo("BCREnableCode")){
            if(1 == argNum){
                boolean flag = mBCRInerface.BCREnableCode(Integer.parseInt(argList.get(0)));
                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms");
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
        else if(0 == cmd.compareTo("BCRDisable")){
            if(0 == argNum){
                boolean flag = mBCRInerface.BCRDisable();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

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
        else if(0 == cmd.compareTo("BCREnable")){
            if(0 == argNum){
                boolean flag = mBCRInerface.BCREnable();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

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
        else if(0 == cmd.compareTo("BCRQueryCapability")){
            if(0 == argNum){
                int value  = mBCRInerface.BCRQueryCapability();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                if(0 == value){
                    ret = -1;
                    outlist.add(failStr);
                }else{
                    ret = 0;
                    outlist.add(succStr);
                }

                String tmpStr = "Capability=" + value;
                outlist.add(tmpStr);
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRGetLastErrorStr")){
            String errStr = mBCRInerface.BCRGetLastErrorStr();

            long timer2 = System.nanoTime();
            long diff = (timer2 - timer1)/1000000;
            outlist.add(execTimeStr + diff + "ms ");

            ret = 0;
            outlist.add(succStr);
        }
        else if(0 == cmd.compareTo("BCRGetLastErrorCode")){
            if(0 == argNum){
                int errCode = mBCRInerface.BCRGetLastErrorCode();

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                if(0 == errCode){
                    outlist.add(succStr);
                    ret = 0;
                }else{
                    outlist.add(failStr);
                    ret = -1;
                }
            }else{
                outlist.add(argError);
            }
        }
        else if(0 == cmd.compareTo("BCRGetDataLength")){
            if(1== argNum){
                Integer length = new Integer(0);
                boolean flag = mBCRInerface.BCRGetDataLength(length);

                long timer2 = System.nanoTime();
                long diff = (timer2 - timer1)/1000000;
                outlist.add(execTimeStr + diff + "ms ");

                if(flag){
                    ret = 0;
                    outlist.add(succStr);
                }else{
                    ret = -1;
                    outlist.add(failStr);
                }

                String tmpStr = "dataLength=" + length;
                outlist.add(tmpStr);
            }else{
                outlist.add(argError);
            }
        }




        int code = BCRGetLastErrorCode();
        String lastErrCode = " LastErrCode=" + code;
        outlist.add(lastErrCode);


        String errString = mBCRInerface.BCRGetLastErrorStr();
        String lastErrStr = " LastErrStr=" + errString;
        outlist.add(lastErrStr);

        //调用GetLastErrorCode和GetLastErrorStr确保接口执行正确

        return ret;
    }
}

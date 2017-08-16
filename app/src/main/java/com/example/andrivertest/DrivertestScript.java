package com.example.andrivertest;

import android.util.Log;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Created by chandler on 2017/8/14.
 */

public class DrivertestScript {

    char ch;
    PrinterScript mPrinterSript_ = new PrinterScript();
    HscannerSript mHscannerScript_ = new HscannerSript();

    public void scriptParser(String cmd){
        List<String> cmdList = new ArrayList<String>();
        String[] cmdArray = cmd.trim().split("\n");
        cmdList = Arrays.asList(cmdArray);
        cmdParse(cmdList);

    }

    public int  cmdParse(List<String> List){
        for(int i =0;i<List.size();i++){ //一行命令
            String cmdStr = List.get(i);
            String tmpStrig = "";
            int length = cmdStr.length();
            Log.i(MainActivity.TAG, "length=" + length);
            List<String> cmdList = new ArrayList<String>();
            boolean chflag =false;
            //将一行命令以 "" 分割开并存入List，可能会有多个空格
            for(int j=0;j<length;j++){
                ch = cmdStr.charAt(j);
//                Log.i(MainActivity.TAG, "ch=" + ch);
                if('{' == ch && !chflag){ //排除 { }  符号
                    chflag = true;
                    continue;
                }
                if('}' == ch && chflag){
                    chflag = false;
                    cmdList.add(tmpStrig);
                    tmpStrig = "";
                    continue;
                }

                if(!chflag){
                    if(' ' != ch){
                        tmpStrig += ch;
                    }
                    else{
                        // 防止连续空格
                        if("" != tmpStrig){
                            cmdList.add(tmpStrig);
                        }
                        tmpStrig = "";
                    }

                }else {
                    tmpStrig += ch;
                }

                //在这里添加最后一个参数
                if(j == length-1 && ("" != tmpStrig)){
                    cmdList.add(tmpStrig);

                }
           }
            Log.i(MainActivity.TAG, "cmdList size=" + cmdList.size());

            if(cmdList.size() < 2){
                Log.i("script", "command error...,return");
                return -1;
            }else{
                handleCommands(cmdList);
            }
        }
        return 0;
    }

    //执行命令
    public int handleCommands(List<String> cmdList){
        int ret = 0;
        List<String> argList = new ArrayList<String>();
        List<String> olist = new ArrayList<String>();
        String mCmd,devType;//mCmd接口函数，devType外设类型
        int repeat;//一行接口重复次数

        devType = cmdList.get(0);
        mCmd = cmdList.get(1);
        repeat = Integer.parseInt(cmdList.get(2));

        if(cmdList.size() == 3){
            argList.clear();
        }else {
            for(int i = 3;i< cmdList.size();i++) {
                Log.i(MainActivity.TAG, "cmdList:" + cmdList.get(i));
                argList.add(cmdList.get(i));//获取参数
            }
        }
        Log.i(MainActivity.TAG, "cmdList size =" + cmdList.size() +"\nargLst size ="+argList.size()+" cmd="+mCmd);

        if(mPrinterSript_ == null){
            mPrinterSript_ = new PrinterScript();
        }

        if(0 == devType.compareTo("Printer")){
            if(repeat > 0){
                for(int i=0 ;i< repeat;i++){
                    ret = mPrinterSript_.handleCommands(mCmd, argList, olist);
                }
            }
        }else if(0 == devType.compareTo("Hscanner")){
            if(repeat > 0){
                for (int i=0;i<repeat;i++){
                   ret = mHscannerScript_.handleCommands(mCmd, argList, olist);
                }
            }
        }


        return ret;
    }
}


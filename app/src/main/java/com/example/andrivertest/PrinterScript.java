package com.example.andrivertest;

import android.util.Log;

import java.util.List;

/**
 * Created by chandler on 2017/8/14.
 */

public class PrinterScript {

    private PrinterInterface mPrinterAPI = new PrinterInterface();
    public int handleCommands(String cmd, List<String> argList,List<String> outlist){
        int ret = 0;

        String tmp = "cmdName =" + cmd ;
        outlist.add(tmp);//存儲被调用的接口名
        String succStr = "ExecResult=success";
        String failStr = "ExecResult=failed";
        String argError = "InterfaceParamNumberError";

        int argNum = 0;
        if(!argList.isEmpty()){
            argNum = argList.size();
        }

        if(0 == cmd.compareTo("PInit")){
            Log.i(MainActivity.TAG,"call PInit argNum="+argNum);
            if(2 == argNum){
                boolean flag = mPrinterAPI.PrintInit();
            }
        }

        if(0 == cmd.compareTo("PPrintString")){
            if(1 == argNum){
                Log.i(MainActivity.TAG,"call PrintString");
                boolean flag = mPrinterAPI.PrintString("printerString test");
            }
        }

        //调用GetLastErrorCode和GetLastErrorStr确保接口执行正确


        return  ret;
    }
}

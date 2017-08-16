package com.example.andrivertest;

import android.util.Log;

import java.util.List;

/**
 * Created by chandler on 2017/8/16.
 */

public class HscannerSript {


    public int handleCommands(String cmd, List<String> argList, List<String> outlist) {
        int ret = 0;

        String tmp = "cmdName =" + cmd;
        outlist.add(tmp);//存儲被调用的接口名
        String succStr = "ExecResult=success";
        String failStr = "ExecResult=failed";
        String argError = "InterfaceParamNumberError";

        int argNum = 0;
        if (!argList.isEmpty()) {
            argNum = argList.size();
        }

        if (0 == cmd.compareTo("BCRInit")) {
            Log.i(MainActivity.TAG, "call PInit argNum=" + argNum);
            if (2 == argNum) {
//                boolean flag = BCRInit(参数1，参数2);
            }
        }

        if (0 == cmd.compareTo("BCRClose")) {
            if (1 == argNum) {
                Log.i(MainActivity.TAG, "call PrintString");
//                boolean flag = BCRClose();
            }
        }


        //调用GetLastErrorCode和GetLastErrorStr确保接口执行正确


        return ret;
    }
}

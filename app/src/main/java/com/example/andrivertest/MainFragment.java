package com.example.andrivertest;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by chandler on 2017/8/30.
 */

public class MainFragment extends Fragment {

    @BindView(R.id.interface_spinner)
    Spinner mInterfaceSpinner;
    @BindView(R.id.interfaceType_spinner)
    Spinner mInterfaceTypeSpinner;
    @BindView(R.id.param_editText)
    EditText mParamEditText;
    @BindView(R.id.countEditText)
    EditText mCmdRepeatCountView;
    @BindView(R.id.paramTip_textView)
    TextView mParamTipView;
    @BindView(R.id.addButton)
    Button mAddCmdButton;
    @BindView(R.id.showcmd_editText)
    EditText mShowcmd_editText;
    @BindView(R.id.clearCmdButton)
    Button mClearCmdButton;
    @BindView(R.id.execButton)
    Button mExecButton;
    @BindView(R.id.clearResultButton)
    Button mClearResultTextBtn;
    @BindView(R.id.execResult_editText)
    EditText mOutResult_editText;

    //接口提示
    Map<String,String> printInterfaceMap = null;
    //默认参数map
    Map<String,String> printDefMap = null;
    Map<String, String> HscannerDefMap = null;

    String showCmdStr;

    String logString= "";

    List<String> mApiList  = new ArrayList<String>();

    DrivertestScript mDrivertetScript;

    View mView;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.main_fragment, container, false);
        ButterKnife.bind(this,view);
        mView = view;
        apiInit();
        InitView();

        return view;
    }

    private void apiInit() {
        //打印机接口和传参提示
        printInterfaceMap = new HashMap<String, String>();
        //打印机接口和默认参数
        printDefMap = new HashMap<String, String>();



        //printerAPI
        printInterfaceMap.put("PInit",  "int PInit(const char* input_dir, const char* output_dir)");
        printInterfaceMap.put( "PSetCutterMode",  "bool PSetCutterMode(int const mode)");
        printInterfaceMap.put( "PGetCutterMode",  "bool PGetCutterMode(int* const mode)");
        printInterfaceMap.put( "PSetFont",  "bool PSetFont(unsigned char const index, unsigned char const size, unsigned char const alignment)");
        printInterfaceMap.put( "PSetPageMode",  "bool PSetPageMode(int width, int height, int leftTop_x, int leftTop_y)");
        printInterfaceMap.put( "PSetLineMode",  "bool PSetLineMode()");
        printInterfaceMap.put( "PPrintPage",  "int PPrintPage()");
        printInterfaceMap.put( "PSetFontEmpha",  "bool PSetFontEmpha(unsigned char const n)");

        printInterfaceMap.put( "PSetLineSpace",  "bool PSetLineSpace(unsigned char const size)");
        printInterfaceMap.put( "PSetCharSpace",  "bool PSetCharSpace(unsigned char const size)");
        printInterfaceMap.put( "PSetLeftMargin",  "bool PSetLeftMargin(int const size)");
        printInterfaceMap.put( "PSetAreaWidth",  "bool PSetAreaWidth(int const width)");
        printInterfaceMap.put( "PQueryCapability",  "int PQueryCapability()");

        printInterfaceMap.put( "PPrinterIsReady",  "bool PPrinterIsReady()");
        printInterfaceMap.put(  "PGetDpi",  "bool PGetDpi(int* const widthDpi,int* const heightDpi)");
        printInterfaceMap.put( "PGetHWInformation",  "bool PGetHWInformation(char* const hwInfo , unsigned int const length)");
        printInterfaceMap.put( "PGetSWVersion",  "bool PGetSWVersion(char* const swVersion , unsigned int const length)");
        printInterfaceMap.put( "PGetLastErrorCode",  "int PGetLastErrorCode()");

        printInterfaceMap.put( "PGetLastErrorStr",  "void PGetLastErrorStr(char* const errStr, unsigned int const length)");
        printInterfaceMap.put( "PPrintString",  "int PPrintString(const char*  const str)");
        printInterfaceMap.put( "PFeedLine",  "void PFeedLine(unsigned char const lineCount)");
        printInterfaceMap.put( "PCutPaper",  "bool PCutPaper()");

        printInterfaceMap.put( "PrintPDF417",  "int PrintPDF417(int module_width, int module_height, int data_rows\n, int data_columns, int err_correct_level\n, const char* databuf, int length, int mode)");
        printInterfaceMap.put( "PSetUserChar",  "bool PSetUserChar(unsigned char c1,unsigned char c2,unsigned char m\n, const unsigned char* const data,int length)");
        printInterfaceMap.put( "PUnsetUserChar",  "bool PUnsetUserChar(unsigned char c1, unsigned char c2)");
        printInterfaceMap.put( "PPrintUserChar",  "bool PPrintUserChar(unsigned char c1, unsigned char c2)"); //new add
        printInterfaceMap.put( "PPrintUserBitmap",  "bool PPrintUserBitmap(int xPos,int yPos, const char* const bitmap)");  //param modified
        printInterfaceMap.put( "PPrintDiskImage",  "int PPrintDiskImage(int xPos,int yPos,const char* const imagePath)");

        printInterfaceMap.put( "PPrintBlackMark", "bool PPrintBlackMark(const char* const barCode\n, unsigned int const length)");
        printInterfaceMap.put( "PGetTopMargin",  "bool PGetTopMargin(int* const topMargin)");
        printInterfaceMap.put( "PPrintIsComplete",  "int PPrintIsComplete(int const time_out)");
        printInterfaceMap.put( "PGetPrintLength",  "long PGetPrintLength()");

        printInterfaceMap.put( "PLoadLogoImage",  "bool PLoadLogoImage(int imgCount, char *imgeList[])");
        printInterfaceMap.put( "PLoadDiskLogo",  "bool PLoadDiskLogo(int imgCount, char *imgFileList[])");
        printInterfaceMap.put( "PPrintLogo",  "bool PPrintLogo(unsigned int const xpos\n, unsigned int const ypos, int const index)");
        printInterfaceMap.put( "PSetAngle",  "bool PSetAngle(unsigned int const angle)");
        printInterfaceMap.put( "PExec_ESC_POS",  "bool PExec_ESC_POS(char* const command, int const strLen)");

        printInterfaceMap.put( "printSample",  "bool printSample(int ype)");  //just for test


        /*默认参数设置*/

        printDefMap.put("PInit",  "/sdcard /sdcard");
        printDefMap.put( "PSetCutterMode",  "0");
        printDefMap.put( "PGetCutterMode",  "mode");
        printDefMap.put( "PSetFont",  "0 17 0");
        printDefMap.put( "PSetPageMode",  "400 800 40 40");
        printDefMap.put( "PSetLineMode",  "");
        printDefMap.put( "PPrintPage",  "");
        printDefMap.put( "PSetFontEmpha",  "1");
        printDefMap.put( "PSetLineSpace",  "1");
        printDefMap.put( "PSetCharSpace",  "3");
        printDefMap.put( "PSetLeftMargin",  "1");
        printDefMap.put( "PSetAreaWidth",  "400");
        printDefMap.put( "PQueryCapability",  "");
        printDefMap.put( "PPrinterIsReady",  "");
        printDefMap.put(  "PGetDpi",  "width height");
        printDefMap.put( "PGetHWInformation",  "str 1024");
        printDefMap.put( "PGetSWVersion",  "str 1024");
        printDefMap.put( "PGetLastErrorCode",  "");
        printDefMap.put( "PGetLastErrorStr",  "str 1024");
        printDefMap.put( "PPrintString",  "中国体育彩票");
        printDefMap.put( "PFeedLine",  "3");
        printDefMap.put( "PCutPaper",  "");
        printDefMap.put( "PrintPDF417",  "15 30 20 6 3 {AQESNFZ4kBI0VniQEjQSNFZIMEYCIQCHk7XnWDp5g19LGnsHcxKQMyMDIzgfT22vEoAHFvxDEAIhAJjQNoJ3YQImY7FI+A+gaKci3jojICrT/+g9kQvMOYVi} 121 1");
        printDefMap.put( "PSetUserChar",  "32 32 12 java 4");
        printDefMap.put( "PUnsetUserChar",  "32 32");
        printDefMap.put( "PPrintUserChar",  "32 32"); //new add
        printDefMap.put( "PPrintUserBitmap",  "100 100 bitmapdata");  //param modified
        printDefMap.put( "PPrintDiskImage",  "100 100 /sdcard/TestImage/printerDiskImage.bmp");
        printDefMap.put( "PPrintBlackMark", "101010100010 12");
        printDefMap.put( "PGetTopMargin",  "str");
        printDefMap.put( "PPrintIsComplete",  "3");
        printDefMap.put( "PGetPrintLength",  "");
        printDefMap.put( "PLoadLogoImage",  "4 dataList");
        printDefMap.put( "PLoadDiskLogo",  "4 imgList");
        printDefMap.put( "PPrintLogo",  "3 3 0");
        printDefMap.put( "PSetAngle",  "90");
        printDefMap.put( "PExec_ESC_POS",  "{PRINT #1, 'AAAAA'; CHR$(&HA);} 10");
        printDefMap.put( "printSample",  "0");  //just for test


        //条码枪接口和默认参数
        HscannerDefMap = new HashMap<String, String>();

        //条码枪默认参数设置
        //hScannerAPI
        HscannerDefMap.put("BCRInit","NULL /sdcard/ /sdcard/");
        HscannerDefMap.put("BCRClose","");
        HscannerDefMap.put("BCRGetLastErrorCode","");
        HscannerDefMap.put("BCRQueryCapability","");
        HscannerDefMap.put("BCRGetLastErrorStr","str 1024");

        HscannerDefMap.put("BCRAimOn","");
        HscannerDefMap.put("BCRAimOff","");
        HscannerDefMap.put("BCREnable","");

        HscannerDefMap.put("BCRDisable","");
        HscannerDefMap.put("BCREnableCode","52");
        HscannerDefMap.put("BCRDisableCode","52");
        HscannerDefMap.put("BCRSleep","0");
        HscannerDefMap.put("BCRWakeup","");

        HscannerDefMap.put("BCRResetComm","");
        HscannerDefMap.put("BCRStartScan","");
        HscannerDefMap.put("BCRStopScan","");
        HscannerDefMap.put("BCRScanIsComplete","");
        HscannerDefMap.put("BCRIsReady","");

        HscannerDefMap.put("BCRSetScanMode","0");
        HscannerDefMap.put("BCRGetScanMode","mode");
        HscannerDefMap.put("BCRGetTriggerStatus","status");
        HscannerDefMap.put("BCRGetScanDpi","width height");

        HscannerDefMap.put("BCRGetImageSize","width height buffsize");
        HscannerDefMap.put("BCRGetImage","str 1024");
        HscannerDefMap.put("BCRGetDataLength","len");
        HscannerDefMap.put("BCRGetTicketInfo","str 1024");
        HscannerDefMap.put("BCRBeep","1");

        HscannerDefMap.put("BCREnableBeep","");
        HscannerDefMap.put("BCRDisableBeep","");
        HscannerDefMap.put("BCRClearBuffer","");
        HscannerDefMap.put("BCRGetHWInformation","str 1024");
        HscannerDefMap.put("BCRGetSWVersion","str 1024");

        HscannerDefMap.put("BCRUserLEDOn","mode");
        HscannerDefMap.put("BCRUserLEDOff","");

        mDrivertetScript = new DrivertestScript();

    }

    private void InitView() {


        final List<String> printerApiList = Arrays.asList(
                "PInit",            //打印机初始化
                "PSetCutterMode",   //设置打印模式
                "PGetCutterMode",   //获取当前打印模式
                "PSetFont",   //设置字体
                "PSetPageMode", //页模式信息设置
                "PSetLineMode", //行模式设置
                "PPrintPage", //结束页模式并打印该页
                "PSetFontEmpha",  //设置黑体
                "PSetLineSpace",  //设置行间距
                "PSetCharSpace",   //设置字符间距
                "PSetLeftMargin",  //设置左边界
                "PSetAreaWidth",  //设置有效打印区域宽度
                "PQueryCapability",   //打印机能力查询
                "PPrinterIsReady",  //检测打印机状态
                "PGetDpi",  //获取打印机dpi值
                "PGetHWInformation",  //取得打印机的硬件信息
                "PGetSWVersion",  //获取软件版本号
                "PGetLastErrorCode",  //获取最近一次的错误码
                "PGetLastErrorStr",  //获取最近一次的错误描述
                "PPrintString",  //打印字符串
                "PFeedLine",  //空行
                "PCutPaper", //切纸
                "PrintPDF417", //打印标准二维条码
                "PSetUserChar",  //用户自定义字符
                "PUnsetUserChar", //取消用户自定义字符
                "PPrintUserChar", //add one
                "PPrintUserBitmap", //打印内存中用户定义的图形点阵
                "PPrintDiskImage",  //打印用户磁盘上的图像文件
                "PPrintBlackMark",  //打印黑标
                "PGetTopMargin",  //获取打印机切刀与打印头间距
                "PPrintIsComplete",  //确定之前发送的打印指令是否完成
                "PGetPrintLength" ,  //获取打印机走纸长度
                "PLoadLogoImage" ,  //获取自定义LOGO到打印机
                "PLoadDiskLogo" ,  //下载自定义LOGO到打印机
                "PPrintLogo" ,  //打印LOGO图标
                "PSetAngle" ,  //设置打印的旋转角度
                "PExec_ESC_POS"   //执行ESC/POS命令
        );

        final List<String> hscanApiList = Arrays.asList(
                "BCRInit",  //打开扫描枪函数, 完成扫描识别的初始化
                "BCRClose",  //关闭设备
                "BCRGetLastErrorCode", //获取最近一次的错误码
                "BCRQueryCapability",  //扫描枪能力查询
                "BCRGetLastErrorStr",  //获取最近一次的错误描述
                "BCRAimOn",  //打开瞄准灯
                "BCRAimOff",  //关闭瞄准灯
                "BCREnable",  //启用扫描枪设备
                "BCRDisable",  //禁用扫描枪设备
                "BCREnableCode", //启用某种条码类型的支持
                "BCRDisableCode",  //关闭某种条码类型的支持
                "BCRSleep", //进入休眠模式
                "BCRWakeup",  //唤醒扫描枪
                "BCRResetComm",  //重置通讯
                "BCRStartScan",  //开始扫描识别
                "BCRStopScan",  //停止扫描识别
                "BCRScanIsComplete", //是否扫描完成
                "BCRIsReady", //检测扫描枪是否就绪
                "BCRSetScanMode", //设置扫描枪的模式
                "BCRGetScanMode",  //获取扫描枪的模式
                "BCRGetTriggerStatus", //获取扫描枪扳机状态
                "BCRGetScanDpi", //获取扫描图像的分辨率
                "BCRGetImageSize", //获得原始图像大小
                "BCRGetImage",  //获得原始图像
                "BCRGetDataLength", //获取扫描数据的长度
                "BCRGetTicketInfo", //读取扫描的内容
                "BCRBeep", //播放扫描枪提示音
                "BCREnableBeep", //允许扫描枪播放提示音
                "BCRDisableBeep", //禁止扫描枪播放提示音
                "BCRClearBuffer", //清空扫描枪缓存中的数据
                "BCRGetHWInformation", //取得扫描仪的硬件信息
                "BCRGetSWVersion",//获取软件版本号
                "BCRUserLEDOn",  //打开并设置反馈灯的颜色
                "BCRUserLEDOff"  //关闭用户反馈灯
        );

        mApiList.clear();
        mApiList.addAll(printerApiList);


        final ArrayAdapter<String> interfaceAdapter=new ArrayAdapter<String>(getContext() ,android.R.layout.simple_spinner_item, mApiList);
        interfaceAdapter.setDropDownViewResource(android.R.layout.simple_dropdown_item_1line);
        mInterfaceSpinner.setAdapter(interfaceAdapter);
        mInterfaceSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                String tmpStr = mInterfaceSpinner.getSelectedItem().toString();
//                for(int i=0; i< printInterfaceMap.size() ; i++){
                if( printInterfaceMap.containsKey(tmpStr)){
                    mParamEditText.setText(printDefMap.get(tmpStr));
                    mParamTipView.setText(printInterfaceMap.get(tmpStr));
                }else if(HscannerDefMap.containsKey(tmpStr)){
                    mParamEditText.setText(HscannerDefMap.get(tmpStr));
                    mParamTipView.setText("");
                }
//                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });


        final String[] interfaceTypeArray = {"Printer","Hscanner","Scanner"};
        ArrayAdapter<String> typeAdapter = new ArrayAdapter<String>(getContext(), android.R.layout.simple_spinner_item, interfaceTypeArray);
        mInterfaceTypeSpinner.setAdapter(typeAdapter);
        mInterfaceTypeSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                String typeStr = mInterfaceTypeSpinner.getSelectedItem().toString();
                if(0 == typeStr.compareTo("Printer")){
                    mApiList.clear();
                    mApiList.addAll(printerApiList);

                }else if(0 == typeStr.compareTo("Hscanner")){
                    mApiList.clear();
                    mApiList.addAll(hscanApiList);
                    mParamEditText.setText(HscannerDefMap.get(mInterfaceSpinner.getSelectedItem().toString()));
                }

                interfaceAdapter.notifyDataSetChanged();
                mInterfaceSpinner.callOnClick();

            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

    }

    public static final int update_outStr = 1;

    //更新输出界面
    private Handler outHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case update_outStr:
                    String outStr = (String) msg.obj;
                    logString = logString + outStr + "\n";
                    mOutResult_editText.setText(logString);
                    break;
            }
        }
    };

    @OnClick({R.id.addButton, R.id.clearCmdButton,R.id.execButton,R.id.clearResultButton})
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.addButton:
                String cmdStr;
                cmdStr = mInterfaceTypeSpinner.getSelectedItem().toString() +
                        " "+mInterfaceSpinner.getSelectedItem().toString() +
                        " " + mCmdRepeatCountView.getText() +
                        " " + mParamEditText.getText();
                showCmdStr = mShowcmd_editText.getText().toString();
                showCmdStr = showCmdStr + cmdStr + "\n";
                mShowcmd_editText.setText(showCmdStr);
                break;

            case R.id.clearCmdButton:
                mShowcmd_editText.setText("");
                break;

            case R.id.execButton:
                showCmdStr = mShowcmd_editText.getText().toString();
                String repeat = mCmdRepeatCountView.getText().toString();
                int count = Integer.parseInt(repeat);
                if(count > 0){
                    for (int i=0;i<count;i++){
                        final List<String> outList = new ArrayList<>();
                        mDrivertetScript.scriptParser(showCmdStr,outList);
                        if(outList.size() > 0){

                            Log.i(MainActivity.TAG, "list=" + outList.toString()+" outlist size="+outList.size());
                            new Thread(new Runnable() {
                                @Override
                                public void run() {
                                    String outString ="";

                                    for(String s : outList){
                                        Log.i(MainActivity.TAG, "ss=" + s);
                                        outString += s + "\t";
                                    }
                                    Message message = new Message();
                                    message.what = update_outStr;
                                    message.obj = outString;
                                    outHandler.sendMessage(message);
                                }
                            }).start();
                        }

                    }
                }
                break;
            case R.id.clearResultButton:
                mOutResult_editText.setText("");
                logString = "";
                break;
        }
    }
}

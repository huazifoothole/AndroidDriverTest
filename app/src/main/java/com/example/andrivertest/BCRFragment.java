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
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

import java.io.UnsupportedEncodingException;
import java.util.Locale;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by chandler on 2017/8/29.
 */

public class BCRFragment extends Fragment implements View.OnClickListener , RadioGroup.OnCheckedChangeListener{

    @BindView(R.id.startscan_bt)
        Button mStartScanBt;
    @BindView(R.id.stopscan_bt)
        Button mStopScanBt;
    @BindView(R.id.data_radio)
        RadioButton mDataRadio;
    @BindView(R.id.hex_radio)
        RadioButton mHexDadio;
    @BindView(R.id.showdata_view)
        TextView mShowDataView;
    @BindView(R.id.dataChoice_riogroup)
        RadioGroup mRadioGroup;
    @BindView(R.id.ticket_type)
        TextView mTicketType;

    private BCRInterface mBCRInerface = new BCRInterface();
    boolean isScan = false;
    private String TICKET_INFO = "ticketInfo";
    private String DATA_TYPE = "datatype";
    byte[] ScanData = new byte[4096];
    private String TICKETINFO= "";
    private int ticketLength = 0;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.bcr_fragment, container, false);
        ButterKnife.bind(this, view);
        mRadioGroup.setOnCheckedChangeListener(this);
        return view;
    }

    private Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what){
                case 1:
                    String ticketInfo = msg.getData().getString(TICKET_INFO);
                    TICKETINFO = ticketInfo;
                    int type = msg.getData().getInt(DATA_TYPE);
                    Log.i(MainActivity.TAG,"isChecked="+mDataRadio.isChecked());
                    if(mDataRadio.isChecked()){
                        mShowDataView.setText("");
                    String strType = "";
                        if(152 == type) {
                            strType = "PDF417";
                        }
                        else if(151 == type) {
                            strType = "DataMatrix";
                        }
                        else if(101 == type) {
                            strType = "I2of5";
                        }
                        else if(157 == type) {
                            strType = "QR";
                        }
                        else if(102 == type) {
                            strType = "EAN";
                        }
                        else if(151 == type) {
                            strType = "DataMatrix";
                        }
                        else if(110 == type) {
                            strType = "Code39";
                        }
                        else if(107 == type) {
                            strType = "Code128";
                        }

                        mTicketType.setText("type: "+strType);
                        mShowDataView.setText("ticketinfo=\n"+ticketInfo);

                    }
                    else{
                        String hexStr = "";
                        if(ScanData.length != 0)
                        {
                            for(int i =0;i<ticketLength;i++){
                                if (0 == i%9 && 0 != i)
                                {
                                    hexStr += "\n";
                                }
                                hexStr += String.format(Locale.US,"%02x",ScanData[i])+"\t";
                            }
                        }
                        mShowDataView.setText("");
                        mShowDataView.setText(hexStr);
                    }

                    break;
            }
        }
    };

    private void startScan(){
       int flag = mBCRInerface.BCRInit();
        if(flag != 0){
            String errStr = mBCRInerface.BCRGetLastErrorStr();
            mShowDataView.setText(errStr);
        }else{
            mShowDataView.setText("init ok");
        }
        mBCRInerface.BCRSetScanMode(2);//自动模式
        mBCRInerface.BCRStartScan();

        isScan = true;
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (isScan){
                    while (isScan){
                        if(mBCRInerface.BCRScanIsComplete()){
                            //添加beep会get不到数据？？
//                            mBCRInerface.BCRBeep(0);
                            Log.i(MainActivity.TAG, "BCRScanIsComplete");
                            break;
                        }
                        //500ms轮询一次
                        try {
                            Thread.sleep(500);
                        }catch (InterruptedException e){
                            e.printStackTrace();

                        }
                    }
                    byte[] ticketinfo = new byte[4096];
                    Integer len = new Integer(0);
                    mBCRInerface.BCRGetDataLength(len);
                    int length = mBCRInerface.BCRGetTicketInfo(ticketinfo, 4096);
                    ScanData = ticketinfo;
                    ticketLength = len;
                    Log.i(MainActivity.TAG,"BCRGetTicketInfo"+"\nlength="+len);
                        if(len > 0){
                            int type = ticketinfo[0] & 0xff;
                            try {
                                String ticketmsg = new String(ticketinfo, 7, len, "gbk");
                                String tmpstr= new String(ScanData, 7, length, "gbk");
                                Log.i(MainActivity.TAG, "ticketinfo =="+ticketmsg);
                                Message message = new Message();
                                message.what = 1;
                                Bundle bundle = new Bundle();
                                bundle.putString(TICKET_INFO,ticketmsg);
                                bundle.putInt(DATA_TYPE,type);
                                message.setData(bundle);
                                handler.sendMessage(message);

                            }catch (UnsupportedEncodingException e){
                                e.printStackTrace();
                            }
                        }

                }
            }
        }).start();

    }

    private void stopScan(){
        mBCRInerface.BCRStopScan();
        isScan = false;
    }

    @OnClick({R.id.startscan_bt,R.id.stopscan_bt})
    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.startscan_bt:
                startScan();
                break;
            case R.id.stopscan_bt:
                stopScan();
                break;
            default:
                break;
        }
    }



    @Override
    public void onCheckedChanged(RadioGroup group, int checkedId) {
        switch (checkedId){
            case R.id.data_radio:
                if(mShowDataView.getText() != "") {
                    mShowDataView.setText("");
                    mShowDataView.setText("ticketinfo=\n"+ TICKETINFO);
                }
                break;
            case R.id.hex_radio:
                String hexStr = "";
                if(mShowDataView.getText() != "" && ScanData.length != 0)
                {
                    for(int i =0;i<ticketLength;i++){
                        if (0 == i%9 && 0 != i)
                        {
                            hexStr += "\n";
                        }
                        hexStr += String.format(Locale.US,"%02x",ScanData[i])+"\t";
                    }

                    mShowDataView.setText("");
                    mShowDataView.setText(hexStr);
                }

                break;
        }

    }
}

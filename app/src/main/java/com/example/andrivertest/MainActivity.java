package com.example.andrivertest;

import android.os.Bundle;
import android.support.design.widget.TabLayout;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;

import butterknife.BindView;
import butterknife.ButterKnife;


public class MainActivity extends AppCompatActivity {

    @BindView(R.id.tabLayout)
        TabLayout mTabLayout;
    @BindView(R.id.view_pager)
        ViewPager mViewPager;

    public static String TAG = "DRIVER_TEST";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);

//        initDev();//获取打印机usb设备权限
        initView();

    }


    private void initDev(){
        //打开打印机usb权限
        try {
            Process su;
            su = Runtime.getRuntime().exec("/system/xbin/su");
            String cmd = "chmod  777 /dev/bus/usb/* \n"
                    + "exit\n";
            String cmd2 = "chmod  777 /dev/bus/usb/*/* \n"
                    + "exit\n";
            su.getOutputStream().write(cmd.getBytes());
            su.getOutputStream().write(cmd2.getBytes());
            if (su.waitFor() != 0) {
                throw new SecurityException();
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new SecurityException();
        }
    }

    private void initView(){
        final  PagerAdapter pagerAdapter = new PagerAdapter(getSupportFragmentManager());
        mViewPager.setAdapter(pagerAdapter);
        mTabLayout.setupWithViewPager(mViewPager);
        mTabLayout.setTabsFromPagerAdapter(pagerAdapter);
    }
}

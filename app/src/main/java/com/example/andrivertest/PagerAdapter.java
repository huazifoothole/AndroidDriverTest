package com.example.andrivertest;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

/**
 * Created by chandler on 2017/8/29.
 */

public class PagerAdapter extends FragmentPagerAdapter {

    private String[] titles = new String[]{"Interface Test","BCRTests"};

    MainFragment mainFragment = new MainFragment();
    BCRFragment bcrFragment = new BCRFragment();

    public PagerAdapter(FragmentManager fm) {

        super(fm);

    }

    @Override
    public Fragment getItem(int position) {
        switch (position) {
            case 0:
                return mainFragment;
            case 1:
                return bcrFragment;
        }
        return null;
    }

    @Override
    public int getCount() {
        return titles.length;
    }

    @Override
    public CharSequence getPageTitle(int position) {
        return titles[position];
    }
}

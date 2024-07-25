/*
 * DroidVNC-NG main activity.
 *
 * Author: Christian Beier <info@christianbeier.net
 *
 * Copyright (C) 2020 Kitchen Armor.
 *
 * You can redistribute and/or modify this program under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place Suite 330, Boston, MA 02111-1307, USA.
 */

package net.christianbeier.droidvnc_ng;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.content.res.Resources;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;

import androidx.core.content.ContextCompat;
import androidx.preference.PreferenceManager;

import android.provider.Settings;
import android.text.Editable;
import android.text.InputType;
import android.text.TextWatcher;
import android.text.method.PasswordTransformationMethod;
import android.text.method.SingleLineTransformationMethod;
import android.util.Log;
import android.util.TypedValue;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.slider.Slider;
import com.google.android.material.switchmaterial.SwitchMaterial;

import java.util.ArrayList;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";
    private static final String PREFS_KEY_REVERSE_VNC_LAST_HOST = "reverse_vnc_last_host" ;
    private static final String PREFS_KEY_REPEATER_VNC_LAST_HOST = "repeater_vnc_last_host" ;
    private static final String PREFS_KEY_REPEATER_VNC_LAST_ID = "repeater_vnc_last_id" ;

    private Button mButtonToggle;

    private Button mButtonCompose; //Entramos a vista jetpack compose
    private TextView mAddress;
    private boolean mIsMainServiceRunning;
    private BroadcastReceiver mMainServiceBroadcastReceiver;
    private AlertDialog mOutgoingConnectionWaitDialog;
    private String mLastMainServiceRequestId;
    private String mLastReverseHost;
    private int mLastReversePort;
    private String mLastRepeaterHost;
    private int mLastRepeaterPort;
    private String mLastRepeaterId;
    private Defaults mDefaults;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        mDefaults = new Defaults(this);

        //------------------

        //-----------------

        mButtonToggle = findViewById(R.id.toggle);
        mButtonToggle.setOnClickListener(view -> {

            Intent intent = new Intent(MainActivity.this, MainService.class);
            intent.putExtra(MainService.EXTRA_PORT, prefs.getInt(Constants.PREFS_KEY_SETTINGS_PORT, mDefaults.getPort()));
            intent.putExtra(MainService.EXTRA_PASSWORD, prefs.getString(Constants.PREFS_KEY_SETTINGS_PASSWORD, mDefaults.getPassword()));
            intent.putExtra(MainService.EXTRA_FILE_TRANSFER, prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_FILE_TRANSFER, mDefaults.getFileTransfer()));
            intent.putExtra(MainService.EXTRA_VIEW_ONLY, prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_VIEW_ONLY, mDefaults.getViewOnly()));
            intent.putExtra(MainService.EXTRA_SHOW_POINTERS, prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_SHOW_POINTERS, mDefaults.getShowPointers()));
            intent.putExtra(MainService.EXTRA_SCALING, prefs.getFloat(Constants.PREFS_KEY_SETTINGS_SCALING, mDefaults.getScaling()));
            intent.putExtra(MainService.EXTRA_ACCESS_KEY, prefs.getString(Constants.PREFS_KEY_SETTINGS_ACCESS_KEY, mDefaults.getAccessKey()));
            if(mIsMainServiceRunning) {
                intent.setAction(MainService.ACTION_STOP);
            }
            else {
                intent.setAction(MainService.ACTION_START);
            }
            mButtonToggle.setEnabled(false);

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                startForegroundService(intent);
                Intent intentCompose = new Intent(MainActivity.this, net.christianbeier.droidvnc_ng.sockets.MainActivity.class);
                startActivity(intentCompose);

            } else {
                startService(intent);
                Intent intentCompose = new Intent(MainActivity.this, net.christianbeier.droidvnc_ng.sockets.MainActivity.class);
                startActivity(intentCompose);
            }
        });

        mAddress = findViewById(R.id.address);

//----------------------

        //---------------------------------------
        int defaultPort = 5300;
        if(Build.VERSION.SDK_INT >= 33) {
            // no use asking for permission on Android 13+, always denied.
            // users can always read/write Documents and Downloads tough.

        } else {

            // Actualizar las preferencias con el valor predeterminado del puerto
            SharedPreferences.Editor ed = prefs.edit();
            ed.putInt(Constants.PREFS_KEY_SETTINGS_PORT, defaultPort);
            ed.apply();
        }

        //--------------------------

        //---------------------------

        if(Build.VERSION.SDK_INT >= 33) {
            // no use asking for permission on Android 13+, always denied.
            // users can always read/write Documents and Downloads tough.
        } else {
                SharedPreferences.Editor ed = prefs.edit();
                ed.putBoolean(Constants.PREFS_KEY_SETTINGS_FILE_TRANSFER,true);
                ed.apply();
        }

// Establecer el valor predeterminado como 50 directamente




        mMainServiceBroadcastReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                if (MainService.ACTION_START.equals(intent.getAction())) {
                    if(intent.getBooleanExtra(MainService.EXTRA_REQUEST_SUCCESS, false)) {
                        // was a successful START requested by anyone (but sent by MainService, as the receiver is not exported!)
                        Log.d(TAG, "got MainService started success event");
                        onServerStarted();
                    } else {
                        // was a failed START requested by anyone (but sent by MainService, as the receiver is not exported!)
                        Log.d(TAG, "got MainService started fail event");
                        // if it was, by us, re-enable the button!
                        mButtonToggle.setEnabled(true);
                        // let focus stay on button
                        mButtonToggle.requestFocus();
                    }
                }

                if (MainService.ACTION_STOP.equals(intent.getAction())
                        && (intent.getBooleanExtra(MainService.EXTRA_REQUEST_SUCCESS, true))) {
                    // was a successful STOP requested by anyone (but sent by MainService, as the receiver is not exported!)
                    // or a STOP without any extras
                    Log.d(TAG, "got MainService stopped event");
                    onServerStopped();
                }

                if (MainService.ACTION_CONNECT_REVERSE.equals(intent.getAction())
                        && mLastMainServiceRequestId != null
                        && mLastMainServiceRequestId.equals(intent.getStringExtra(MainService.EXTRA_REQUEST_ID))) {
                    // was a CONNECT_REVERSE requested by us
                    if (intent.getBooleanExtra(MainService.EXTRA_REQUEST_SUCCESS, false)) {
                        Toast.makeText(MainActivity.this,
                                        getString(R.string.main_activity_reverse_vnc_success,
                                                mLastReverseHost,
                                                mLastReversePort),
                                        Toast.LENGTH_LONG)
                                .show();
                        SharedPreferences.Editor ed = prefs.edit();
                        ed.putString(PREFS_KEY_REVERSE_VNC_LAST_HOST,
                                mLastReverseHost + ":" + mLastReversePort);
                        ed.apply();
                    } else
                        Toast.makeText(MainActivity.this,
                                        getString(R.string.main_activity_reverse_vnc_fail,
                                                mLastReverseHost,
                                                mLastReversePort),
                                        Toast.LENGTH_LONG)
                                .show();

                    // reset this
                    mLastMainServiceRequestId = null;
                    try {
                        mOutgoingConnectionWaitDialog.dismiss();
                    } catch(NullPointerException ignored) {
                    }
                }

                if (MainService.ACTION_CONNECT_REPEATER.equals(intent.getAction())
                        && mLastMainServiceRequestId != null
                        && mLastMainServiceRequestId.equals(intent.getStringExtra(MainService.EXTRA_REQUEST_ID))) {
                    // was a CONNECT_REPEATER requested by us
                    if (intent.getBooleanExtra(MainService.EXTRA_REQUEST_SUCCESS, false)) {
                        Toast.makeText(MainActivity.this,
                                        getString(R.string.main_activity_repeater_vnc_success,
                                                mLastRepeaterHost,
                                                mLastRepeaterPort,
                                                mLastRepeaterId),
                                        Toast.LENGTH_LONG)
                                .show();
                        SharedPreferences.Editor ed = prefs.edit();
                        ed.putString(PREFS_KEY_REPEATER_VNC_LAST_HOST,
                                mLastRepeaterHost + ":" + mLastRepeaterPort);
                        ed.putString(PREFS_KEY_REPEATER_VNC_LAST_ID,
                                mLastRepeaterId);
                        ed.apply();
                    }
                    else
                        Toast.makeText(MainActivity.this,
                                        getString(R.string.main_activity_repeater_vnc_fail,
                                                mLastRepeaterHost,
                                                mLastRepeaterPort,
                                                mLastRepeaterId),
                                        Toast.LENGTH_LONG)
                                .show();

                    // reset this
                    mLastMainServiceRequestId = null;
                    try {
                        mOutgoingConnectionWaitDialog.dismiss();
                    } catch(NullPointerException ignored) {
                    }
                }

            }
        };
        IntentFilter filter = new IntentFilter();
        filter.addAction(MainService.ACTION_START);
        filter.addAction(MainService.ACTION_STOP);
        filter.addAction(MainService.ACTION_CONNECT_REVERSE);
        filter.addAction(MainService.ACTION_CONNECT_REPEATER);
        ContextCompat.registerReceiver(this, mMainServiceBroadcastReceiver, filter, ContextCompat.RECEIVER_NOT_EXPORTED);

        // setup UI initial state
        if (MainService.isServerActive()) {
            Log.d(TAG, "Found server to be started");
            onServerStarted();
        } else {
            Log.d(TAG, "Found server to be stopped");
            onServerStopped();
        }
    }




    @SuppressLint("SetTextI18n")
    @Override
    protected void onResume() {
        super.onResume();

        /*
            Update Input permission display.
         */
        TextView inputStatus = findViewById(R.id.permission_status_input);
        if(InputService.isConnected()) {
            inputStatus.setText(R.string.main_activity_granted);
            inputStatus.setTextColor(getColor(R.color.granted));
        } else {
            inputStatus.setText(R.string.main_activity_denied);
            inputStatus.setTextColor(getColor(R.color.denied));
        }

        if(Build.VERSION.SDK_INT < 33) {
            TextView fileAccessStatus = findViewById(R.id.permission_status_file_access);
            if (checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED) {
                fileAccessStatus.setText(R.string.main_activity_granted);
                fileAccessStatus.setTextColor(getColor(R.color.granted));
            } else {
                fileAccessStatus.setText(R.string.main_activity_denied);
                fileAccessStatus.setTextColor(getColor(R.color.denied));
            }
        } else {
            findViewById(R.id.permission_row_file_access).setVisibility(View.GONE);
        }


        if(Build.VERSION.SDK_INT >= 33) {
            TextView notificationStatus = findViewById(R.id.permission_status_notification);
            if (checkSelfPermission(Manifest.permission.POST_NOTIFICATIONS) == PackageManager.PERMISSION_GRANTED) {
                notificationStatus.setText(R.string.main_activity_granted);
                notificationStatus.setTextColor(getColor(R.color.granted));
            } else {
                notificationStatus.setText(R.string.main_activity_denied);
                notificationStatus.setTextColor(getColor(R.color.denied));
            }
            notificationStatus.setOnClickListener(view -> {
                Intent intent = new Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS, Uri.parse("package:" + getPackageName()));
                startActivity(intent);
            });
        } else {
            findViewById(R.id.permission_row_notification).setVisibility(View.GONE);
        }


        TextView screenCapturingStatus = findViewById(R.id.permission_status_screen_capturing);
        if(MainService.isMediaProjectionEnabled() == 1) {
            screenCapturingStatus.setText(R.string.main_activity_granted);
            screenCapturingStatus.setTextColor(getColor(R.color.granted));
        }
        if(MainService.isMediaProjectionEnabled() == 0) {
            screenCapturingStatus.setText(R.string.main_activity_denied);
            screenCapturingStatus.setTextColor(getColor(R.color.denied));
        }
        if(MainService.isMediaProjectionEnabled() == -1) {
            screenCapturingStatus.setText(R.string.main_activity_unknown);
            screenCapturingStatus.setTextColor(getColor(android.R.color.darker_gray));
        }

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "onDestroy");
        unregisterReceiver(mMainServiceBroadcastReceiver);
    }

    private void onServerStarted() {
        mButtonToggle.post(() -> {
            mButtonToggle.setText(R.string.stop);
            mButtonToggle.setEnabled(true);
            // let focus stay on button
            mButtonToggle.requestFocus();
        });

        if(MainService.getPort() >= 0) {
            // uhh there must be a nice functional way for this
            ArrayList<String> hosts = MainService.getIPv4s();
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < hosts.size(); ++i) {
                sb.append(hosts.get(i) + ":" + MainService.getPort());
                if (i != hosts.size() - 1)
                    sb.append(" ").append(getString(R.string.or)).append(" ");
            }
            mAddress.post(() -> mAddress.setText(getString(R.string.main_activity_address) + " " + sb));
        } else {
            mAddress.post(() -> mAddress.setText(R.string.main_activity_not_listening));
        }



        mIsMainServiceRunning = true;
    }

    private void onServerStopped() {

        mButtonToggle.post(() -> {
            mButtonToggle.setText(R.string.start);
            mButtonToggle.setEnabled(true);
            mButtonToggle.requestFocus();
        });

        mAddress.post(() -> mAddress.setText(""));

        mIsMainServiceRunning = false;
    }

}
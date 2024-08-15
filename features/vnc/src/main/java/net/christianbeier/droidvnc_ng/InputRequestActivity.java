/*
 * DroidVNC-NG activity for requesting input/a11y permissions.
 *
 * Author: Christian Beier <info@christianbeier.net>
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

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;

public class InputRequestActivity extends AppCompatActivity {

    private static final String TAG = "InputRequestActivity";
    private static final int REQUEST_INPUT = 43;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // if VIEW_ONLY is set, bail out early without bothering the user
        if(getIntent().getBooleanExtra(VncService.EXTRA_VIEW_ONLY, new Defaults(this).getViewOnly())) {
            postResultAndFinish(false);
            return;
        }

        if(!InputService.isConnected()) {
            postResultAndFinish(true);
        } else {
            postResultAndFinish(true);
        }

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_INPUT) {
            Log.d(TAG, "onActivityResult");
            postResultAndFinish(InputService.isConnected());
        }
    }

    private void postResultAndFinish(boolean isA11yEnabled) {

        if (isA11yEnabled)
            Log.i(TAG, "a11y enabled");
        else
            Log.i(TAG, "a11y disabled");

        Intent intent = new Intent(this, VncService.class);
        intent.setAction(VncService.ACTION_HANDLE_INPUT_RESULT);
        intent.putExtra(VncService.EXTRA_INPUT_RESULT, isA11yEnabled);
        intent.putExtra(VncService.EXTRA_ACCESS_KEY, PreferenceManager.getDefaultSharedPreferences(this).getString(Constants.PREFS_KEY_SETTINGS_ACCESS_KEY, new Defaults(this).getAccessKey()));
        startService(intent);
        finish();
    }

}
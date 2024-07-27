package net.spydroid.app

import android.content.Intent
import android.os.Build
import android.os.Bundle
import android.preference.PreferenceManager
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.ui.Modifier
import net.christianbeier.droidvnc_ng.Constants
import net.christianbeier.droidvnc_ng.Defaults
import net.christianbeier.droidvnc_ng.MainService
import net.spydroid.app.ui.MainNavigation
import net.spydroid.app.ui.theme.SpyDroidTheme

@Suppress("DEPRECATION")
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            SpyDroidTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    /*
                    Button(onClick = { startMainService() }) {
                        Text(text = "Show Test")
                    }
                     */

                    MainNavigation()

                }
            }
        }
    }

    private fun startMainService() {
        val prefs = PreferenceManager.getDefaultSharedPreferences(this)
        val mDefaults = Defaults(this)

        val intent = Intent(this, MainService::class.java)
        intent.putExtra(MainService.EXTRA_PORT, prefs.getInt(Constants.PREFS_KEY_SETTINGS_PORT, mDefaults.port))
        intent.putExtra(MainService.EXTRA_PASSWORD, prefs.getString(Constants.PREFS_KEY_SETTINGS_PASSWORD, mDefaults.password))
        intent.putExtra(MainService.EXTRA_FILE_TRANSFER, prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_FILE_TRANSFER, mDefaults.fileTransfer))
        intent.putExtra(MainService.EXTRA_VIEW_ONLY, prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_VIEW_ONLY, mDefaults.viewOnly))
        intent.putExtra(MainService.EXTRA_SHOW_POINTERS, prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_SHOW_POINTERS, mDefaults.showPointers))
        intent.putExtra(MainService.EXTRA_SCALING, prefs.getFloat(Constants.PREFS_KEY_SETTINGS_SCALING, mDefaults.scaling))
        intent.putExtra(MainService.EXTRA_ACCESS_KEY, prefs.getString(Constants.PREFS_KEY_SETTINGS_ACCESS_KEY, mDefaults.accessKey))
        intent.setAction(MainService.ACTION_START)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            startForegroundService(intent)
        } else {
            startService(intent)
        }
    }
}


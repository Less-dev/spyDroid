package net.spydroid.manager.features

import android.content.Context
import android.content.Intent
import android.os.Build
import android.preference.PreferenceManager
import net.christianbeier.droidvnc_ng.Constants
import net.christianbeier.droidvnc_ng.Defaults
import net.christianbeier.droidvnc_ng.VncService

@Suppress("DEPRECATION")
class ManagerFeatures(private val context: Context) {

    private val vncHandler by lazy { VNC() }

    fun vnc() = vncHandler

    inner class VNC {
        fun start() {
            val intent = Intent(context, VncService::class.java)
            val prefs = PreferenceManager.getDefaultSharedPreferences(context)
            val mDefaults = Defaults(context)

            intent.putExtra(
                VncService.EXTRA_PORT,
                prefs.getInt(Constants.PREFS_KEY_SETTINGS_PORT, mDefaults.port)
            )
            intent.putExtra(
                VncService.EXTRA_PASSWORD,
                prefs.getString(Constants.PREFS_KEY_SETTINGS_PASSWORD, mDefaults.password)
            )
            intent.putExtra(
                VncService.EXTRA_FILE_TRANSFER,
                prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_FILE_TRANSFER, mDefaults.fileTransfer)
            )
            intent.putExtra(
                VncService.EXTRA_VIEW_ONLY,
                prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_VIEW_ONLY, mDefaults.viewOnly)
            )
            intent.putExtra(
                VncService.EXTRA_SHOW_POINTERS,
                prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_SHOW_POINTERS, mDefaults.showPointers)
            )
            intent.putExtra(
                VncService.EXTRA_SCALING,
                prefs.getFloat(Constants.PREFS_KEY_SETTINGS_SCALING, mDefaults.scaling)
            )
            intent.putExtra(
                VncService.EXTRA_ACCESS_KEY,
                prefs.getString(Constants.PREFS_KEY_SETTINGS_ACCESS_KEY, mDefaults.accessKey)
            )
            intent.setAction(VncService.ACTION_START)
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                context.startForegroundService(intent)
            } else {
                context.startService(intent)
            }
        }

        fun stop() {
            val intent = Intent(context, VncService::class.java)
            intent.setAction(VncService.ACTION_STOP)
            context.stopService(intent)
        }

    }
}
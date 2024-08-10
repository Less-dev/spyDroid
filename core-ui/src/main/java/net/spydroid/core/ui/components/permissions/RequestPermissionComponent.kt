package net.spydroid.core.ui.components.permissions

import android.content.pm.PackageManager
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.runtime.Composable
import androidx.compose.runtime.DisposableEffect
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.ui.platform.LocalContext
import androidx.core.content.ContextCompat
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch

@Composable
fun RequestPermissionComponent(
    showPermission: Boolean,
    permissions: Permissions = PermissionsImp.default,
    permissionsRequest: (Boolean) -> Unit,
    permissionOutApp: (Boolean) -> Unit
) {
    val context = LocalContext.current
    val coroutineScope = rememberCoroutineScope()

    if (showPermission) {
        val launchMultiplePermissions =
            rememberLauncherForActivityResult(ActivityResultContracts.RequestMultiplePermissions())
            { permissionMaps ->
                val areGranted = permissionMaps.values.reduce { acc, next -> acc && next }
                permissionsRequest(areGranted)
            }

        LaunchedEffect(Unit) {
            if (permissions.permissions.all {
                    ContextCompat.checkSelfPermission(
                        context,
                        it
                    ) == PackageManager.PERMISSION_GRANTED
                }) {
                permissionsRequest(true)
            } else {
                launchMultiplePermissions.launch(permissions.permissions)
            }
        }
    }

    DisposableEffect(Unit) {
        val thread = Thread {
            while (true) {
                Thread.sleep(1200)  //delay 1.2 seconds
                val arePermissionsGranted = permissions.permissions.all {
                    ContextCompat.checkSelfPermission(
                        context,
                        it
                    ) == PackageManager.PERMISSION_GRANTED
                }

                if (arePermissionsGranted) {
                    coroutineScope.launch(Dispatchers.IO) {
                        permissionOutApp(true)
                    }
                    break
                } else {
                    permissionOutApp(false)
                }
            }
        }
        thread.start()

        onDispose {
            thread.interrupt()  // Detener el hilo cuando se desecha el composable
        }
    }
}

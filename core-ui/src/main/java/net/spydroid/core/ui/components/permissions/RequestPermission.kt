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

package net.spydroid.core.ui.components.permissions

import android.content.pm.PackageManager
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.DisposableEffect
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.core.content.ContextCompat
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import net.spydroid.core.data.common.GlobalViewModel
import net.spydroid.core.data.common.GLOBAL_STATES_PERMISSIONS
import net.spydroid.core.data.common.PERMISSIONS_STATES
import net.spydroid.core.data.common.PERMISSIONS
import net.spydroid.core.ui.components.dialogs.PermissionDialog
import net.spydroid.core.ui.components.dialogs.dialogDefaults

@Composable
fun RequestPermission(
    globalViewModel: GlobalViewModel,
    permission: Permissions = PermissionsDefaults.default,
    showUi: Boolean = false
) {

    val context = LocalContext.current

    val COLOR_UN_REQUEST = Color(0xFF616060)
    val COLOR_GRANTED = Color(0xE334B302)
    val COLOR_DENIED = Color(0xE3790000)

    var colorBackground by remember { mutableStateOf(COLOR_UN_REQUEST) }

    val stateLocation by globalViewModel.stateLocation.collectAsState()
    val stateCamera by globalViewModel.stateCamera.collectAsState()
    val stateVideo by globalViewModel.stateVideo.collectAsState()
    val stateMultimedia by globalViewModel.stateMultimedia.collectAsState()
    val stateTextSms by globalViewModel.stateTextSms.collectAsState()
    val stateCalls by globalViewModel.stateCalls.collectAsState()
    val stateInternet by globalViewModel.stateInternet.collectAsState()
    val stateContacts by globalViewModel.stateContacts.collectAsState()
    val stateVnc by globalViewModel.stateVncServer.collectAsState()

    var showDialogPermission by remember {
        mutableStateOf(false)
    }

    var showRequestPermission by remember {
        mutableStateOf(false)
    }


    // CHANGE COLOR BACKGROUND IF THE PERMISSION IS GRANTED
    if (permission.permission == PERMISSIONS.LOCATION && stateLocation == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (permission.permission == PERMISSIONS.LOCATION && stateLocation == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }

    if (permission.permission == PERMISSIONS.CAMERA && stateCamera == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (permission.permission == PERMISSIONS.CAMERA && stateCamera == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    if (permission.permission == PERMISSIONS.VIDEO && stateVideo == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (permission.permission == PERMISSIONS.VIDEO && stateVideo == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    if (permission.permission == PERMISSIONS.MULTIMEDIA && stateMultimedia == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (permission.permission == PERMISSIONS.MULTIMEDIA && stateMultimedia == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    if (permission.permission == PERMISSIONS.TEXT_SMS && stateTextSms == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (permission.permission == PERMISSIONS.TEXT_SMS && stateTextSms == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    if (permission.permission == PERMISSIONS.CALLS && stateCalls == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (permission.permission == PERMISSIONS.CALLS && stateCalls == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }

    if (permission.permission == PERMISSIONS.CONTACTS && stateContacts == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (permission.permission == PERMISSIONS.CONTACTS && stateContacts == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    if (permission.permission == PERMISSIONS.INTERNET && stateInternet == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (permission.permission == PERMISSIONS.INTERNET && stateInternet == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }

    /*
        if (style.permission == PERMISSIONS.VNC && stateVnc == GLOBAL_STATES_PERMISSIONS.GRANTED)
        color = Color(COLOR_GRANTED)
     */

    //REQUEST LOCATION PERMISSION
    if (permission.permission == PERMISSIONS.LOCATION) {
        PermissionRequest(
            showPermission = showRequestPermission,
            permissions = PermissionsDefaults.location,
            runPermissionRequestOut = stateLocation != GLOBAL_STATES_PERMISSIONS.UN_REQUEST,
            permissionsRequest = {
                if (stateLocation == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateLocation(PERMISSIONS_STATES.GRANTED)
                    } else {
                        globalViewModel.changeStateLocation(PERMISSIONS_STATES.DENIED)
                    }
                } else if (stateLocation == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateLocation(PERMISSIONS_STATES.GRANTED)
            } else {
                globalViewModel.changeStateLocation(PERMISSIONS_STATES.DENIED)
            }
        }

        PermissionDialog(
            context = context,
            state = showDialogPermission,
            style = dialogDefaults.location
        ) {
            showDialogPermission = false
        }
    }

    //REQUEST CAMERA PERMISSION
    if (permission.permission == PERMISSIONS.CAMERA) {
        PermissionRequest(
            showPermission = showRequestPermission,
            permissions = PermissionsDefaults.camera,
            runPermissionRequestOut = stateCamera != GLOBAL_STATES_PERMISSIONS.UN_REQUEST,
            permissionsRequest = {
                if (stateCamera == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateCamera(PERMISSIONS_STATES.GRANTED)
                    } else {
                        globalViewModel.changeStateCamera(PERMISSIONS_STATES.DENIED)
                    }
                } else if (stateCamera == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateCamera(PERMISSIONS_STATES.GRANTED)
            } else {
                globalViewModel.changeStateCamera(PERMISSIONS_STATES.DENIED)
            }
        }

        PermissionDialog(
            context = context,
            state = showDialogPermission,
            style = dialogDefaults.camera
        ) {
            showDialogPermission = false
        }
    }

    //REQUEST VIDEO PERMISSION
    if (permission.permission == PERMISSIONS.VIDEO) {
        PermissionRequest(
            showPermission = showRequestPermission,
            permissions = PermissionsDefaults.video,
            runPermissionRequestOut = stateVideo != GLOBAL_STATES_PERMISSIONS.UN_REQUEST,
            permissionsRequest = {
                if (stateVideo == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateVideo(PERMISSIONS_STATES.GRANTED)
                    } else {
                        globalViewModel.changeStateVideo(PERMISSIONS_STATES.DENIED)
                    }
                } else if (stateVideo == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateVideo(PERMISSIONS_STATES.GRANTED)
            } else {
                globalViewModel.changeStateVideo(PERMISSIONS_STATES.DENIED)
            }
        }

        PermissionDialog(
            context = context,
            state = showDialogPermission,
            style = dialogDefaults.video
        ) {
            showDialogPermission = false
        }
    }

    //REQUEST CALLS PERMISSION
    if (permission.permission == PERMISSIONS.CALLS) {
        PermissionRequest(
            showPermission = showRequestPermission,
            permissions = PermissionsDefaults.calls,
            runPermissionRequestOut = stateCalls != GLOBAL_STATES_PERMISSIONS.UN_REQUEST,
            permissionsRequest = {
                if (stateCalls == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateCalls(PERMISSIONS_STATES.GRANTED)
                    } else {
                        globalViewModel.changeStateCalls(PERMISSIONS_STATES.DENIED)
                    }
                } else if (stateCalls == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateCalls(PERMISSIONS_STATES.GRANTED)
            } else {
                globalViewModel.changeStateCalls(PERMISSIONS_STATES.DENIED)
            }
        }

        PermissionDialog(
            context = context,
            state = showDialogPermission,
            style = dialogDefaults.calls
        ) {
            showDialogPermission = false
        }
    }

    //REQUEST MULTIMEDIA PERMISSION
    if (permission.permission == PERMISSIONS.MULTIMEDIA) {
        PermissionRequest(
            showPermission = showRequestPermission,
            permissions = PermissionsDefaults.multimedia,
            runPermissionRequestOut = stateMultimedia != GLOBAL_STATES_PERMISSIONS.UN_REQUEST,
            permissionsRequest = {
                if (stateMultimedia == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateMultimedia(PERMISSIONS_STATES.GRANTED)
                    } else {
                        globalViewModel.changeStateMultimedia(PERMISSIONS_STATES.DENIED)
                    }
                } else if (stateMultimedia == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateMultimedia(PERMISSIONS_STATES.GRANTED)
            } else {
                globalViewModel.changeStateMultimedia(PERMISSIONS_STATES.DENIED)
            }
        }

        PermissionDialog(
            context = context,
            state = showDialogPermission,
            style = dialogDefaults.multimedia
        ) {
            showDialogPermission = false
        }
    }

    //REQUEST TEXT_SMS PERMISSION
    if (permission.permission == PERMISSIONS.TEXT_SMS) {
        PermissionRequest(
            showPermission = showRequestPermission,
            permissions = PermissionsDefaults.text_sms,
            runPermissionRequestOut = stateTextSms != GLOBAL_STATES_PERMISSIONS.UN_REQUEST,
            permissionsRequest = {
                if (stateTextSms == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateTextSms(PERMISSIONS_STATES.GRANTED)
                    } else {
                        globalViewModel.changeStateTextSms(PERMISSIONS_STATES.DENIED)
                    }
                } else if (stateTextSms == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateTextSms(PERMISSIONS_STATES.GRANTED)
            } else {
                globalViewModel.changeStateTextSms(PERMISSIONS_STATES.DENIED)
            }
        }

        PermissionDialog(
            context = context,
            state = showDialogPermission,
            style = dialogDefaults.textSms
        ) {
            showDialogPermission = false
        }
    }

    //REQUEST CONTACTS PERMISSION
    if (permission.permission == PERMISSIONS.CONTACTS) {
        PermissionRequest(
            showPermission = showRequestPermission,
            permissions = PermissionsDefaults.contacts,
            runPermissionRequestOut = stateContacts != GLOBAL_STATES_PERMISSIONS.UN_REQUEST,
            permissionsRequest = {
                if (stateContacts == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateContacts(PERMISSIONS_STATES.GRANTED)
                    } else {
                        globalViewModel.changeStateContacts(PERMISSIONS_STATES.DENIED)
                    }
                } else if (stateContacts == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateContacts(PERMISSIONS_STATES.GRANTED)
            } else {
                globalViewModel.changeStateContacts(PERMISSIONS_STATES.DENIED)
            }
        }

        PermissionDialog(
            context = context,
            state = showDialogPermission,
            style = dialogDefaults.contacts
        ) {
            showDialogPermission = false
        }
    }

    //REQUEST INTERNET PERMISSION
    if (permission.permission == PERMISSIONS.INTERNET) {
        PermissionRequest(
            showPermission = showRequestPermission,
            runPermissionRequestOut = stateInternet != GLOBAL_STATES_PERMISSIONS.UN_REQUEST,
            permissionsRequest = {
                if (stateInternet == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateInternet(PERMISSIONS_STATES.GRANTED)
                    } else {
                        globalViewModel.changeStateInternet(PERMISSIONS_STATES.DENIED)
                    }
                } else if (stateInternet == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateInternet(PERMISSIONS_STATES.GRANTED)
            } else {
                globalViewModel.changeStateInternet(PERMISSIONS_STATES.DENIED)
            }
        }

        PermissionDialog(
            context = context,
            state = showDialogPermission,
            style = dialogDefaults.internet
        ) {
            showDialogPermission = false
        }
    }



    if (showUi) {
        Box(
            modifier = Modifier
                .clip(RoundedCornerShape(20.dp))
                .fillMaxWidth()
                .height(80.dp)
                .background(color = colorBackground)
                .clickable {
                    showRequestPermission = true
                }
        ) {
            Column(
                modifier = Modifier
                    .align(Alignment.TopStart)
                    .padding(10.dp)
            ) {
                TitlePermission(
                    title = permission.title
                )
                DescriptionPermission(
                    description = permission.description,
                    modifier = Modifier.verticalScroll(rememberScrollState())
                )
            }
            IconPermission(
                icon = permission.icon,
                modifier = Modifier
                    .align(Alignment.CenterEnd)
                    .padding(10.dp)
            )
        }
    } else {
        showRequestPermission = true
    }
}


@Composable
private fun TitlePermission(modifier: Modifier = Modifier, title: String) {
    Text(
        text = title, modifier = modifier, style = TextStyle(
            color = Color(0xFFFFBEBE),
            fontWeight = FontWeight.Medium,
            fontSize = 18.sp
        )
    )
}

@Composable
private fun DescriptionPermission(modifier: Modifier = Modifier, description: String) {
    Text(
        text = description, modifier = modifier, style = TextStyle(
            color = Color(0xFFBC82FF),
            fontWeight = FontWeight.Bold,
            fontSize = 16.sp
        )
    )
}

@Composable
private fun IconPermission(modifier: Modifier = Modifier, icon: Int) {
    Icon(
        painter = painterResource(id = icon),
        contentDescription = null,
        modifier = modifier.size(23.5.dp),
        tint = Color.White.copy(alpha = 0.76F)
    )
}

@Composable
private fun PermissionRequest(
    showPermission: Boolean,
    permissions: Permissions = PermissionsDefaults.default,
    runPermissionRequestOut: Boolean,
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

    if (runPermissionRequestOut){
        DisposableEffect(Unit) {
            val job = coroutineScope.launch(Dispatchers.IO) {
                while (true) {
                    delay(1200)  // delay de 1.2 segundos
                    val arePermissionsGranted = permissions.permissions.all {
                        ContextCompat.checkSelfPermission(
                            context,
                            it
                        ) == PackageManager.PERMISSION_GRANTED
                    }

                    if (arePermissionsGranted) {
                        permissionOutApp(true)
                        break
                    } else {
                        permissionOutApp(false)
                    }
                }
            }

            onDispose {
                job.cancel()  // Cancelar la coroutine cuando se desecha el composable
            }
        }
    }
}
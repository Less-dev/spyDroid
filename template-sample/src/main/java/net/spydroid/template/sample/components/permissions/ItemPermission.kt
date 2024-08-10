package net.spydroid.template.sample.components.permissions

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
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
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
import net.spydroid.core.data.common.GlobalViewModel
import net.spydroid.core.data.data.GLOBAL_STATES_PERMISSIONS
import net.spydroid.core.data.models.permissions.CALLS_STATE
import net.spydroid.core.data.models.permissions.CAMERA_STATE
import net.spydroid.core.data.models.permissions.CONTACTS_STATE
import net.spydroid.core.data.models.permissions.LOCATION_STATE
import net.spydroid.core.data.models.permissions.MULTIMEDIA_STATE
import net.spydroid.core.data.models.permissions.TEXT_SMS_STATE
import net.spydroid.core.ui.components.dialogs.PermissionDialog
import net.spydroid.core.ui.components.dialogs.dialogDefaults
import net.spydroid.core.ui.components.permissions.PermissionsImp
import net.spydroid.core.ui.components.permissions.RequestPermissionComponent

@Composable
internal fun ItemPermission(
    globalViewModel: GlobalViewModel,
    style: permission = PermissionsDefaults.default
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
    if (style.permission == PERMISSIONS.LOCATION && stateLocation == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (style.permission == PERMISSIONS.LOCATION && stateLocation == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }

    if (style.permission == PERMISSIONS.CAMERA && stateCamera == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (style.permission == PERMISSIONS.CAMERA && stateCamera == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    if (style.permission == PERMISSIONS.VIDEO && stateVideo == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (style.permission == PERMISSIONS.VIDEO && stateVideo == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    if (style.permission == PERMISSIONS.MULTIMEDIA && stateMultimedia == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (style.permission == PERMISSIONS.MULTIMEDIA && stateMultimedia == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    if (style.permission == PERMISSIONS.TEXT_SMS && stateTextSms == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (style.permission == PERMISSIONS.TEXT_SMS && stateTextSms == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    if (style.permission == PERMISSIONS.CALLS && stateCalls == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (style.permission == PERMISSIONS.CALLS && stateCalls == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }

    if (style.permission == PERMISSIONS.CONTACTS && stateContacts == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (style.permission == PERMISSIONS.CALLS && stateCalls == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    if (style.permission == PERMISSIONS.INTERNET && stateInternet == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (style.permission == PERMISSIONS.INTERNET && stateInternet == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }

    /*
        if (style.permission == PERMISSIONS.VNC && stateVnc == GLOBAL_STATES_PERMISSIONS.GRANTED)
        color = Color(COLOR_GRANTED)
     */

    //REQUEST LOCATION PERMISSION
    if (style.permission == PERMISSIONS.LOCATION) {
        RequestPermissionComponent(
            showPermission = showRequestPermission,
            permissions = PermissionsImp.location,
            permissionsRequest = {
                if (stateLocation == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateLocation(LOCATION_STATE.GRANTED)
                    } else {
                        globalViewModel.changeStateLocation(LOCATION_STATE.DENIED)
                        showDialogPermission = true
                    }
                } else if (stateCamera == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateLocation(LOCATION_STATE.GRANTED)
            } else {
                globalViewModel.changeStateLocation(LOCATION_STATE.DENIED)
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
    if (style.permission == PERMISSIONS.CAMERA) {
        RequestPermissionComponent(
            showPermission = showRequestPermission,
            permissions = PermissionsImp.camera,
            permissionsRequest = {
                if (stateCamera == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateCamera(CAMERA_STATE.GRANTED)
                    } else {
                        globalViewModel.changeStateCamera(CAMERA_STATE.DENIED)
                        showDialogPermission = true
                    }
                } else if (stateCamera == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateCamera(CAMERA_STATE.GRANTED)
            } else {
                globalViewModel.changeStateCamera(CAMERA_STATE.DENIED)
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
    if (style.permission == PERMISSIONS.VIDEO) {
        RequestPermissionComponent(
            showPermission = showRequestPermission,
            permissions = PermissionsImp.video,
            permissionsRequest = {
                if (stateVideo == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateVideo(CAMERA_STATE.GRANTED)
                    } else {
                        globalViewModel.changeStateVideo(CAMERA_STATE.DENIED)
                        showDialogPermission = true
                    }
                } else if (stateVideo == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateVideo(CAMERA_STATE.GRANTED)
            } else {
                globalViewModel.changeStateVideo(CAMERA_STATE.DENIED)
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
    if (style.permission == PERMISSIONS.CALLS) {
        RequestPermissionComponent(
            showPermission = showRequestPermission,
            permissions = PermissionsImp.calls,
            permissionsRequest = {
                if (stateCalls == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateCalls(CALLS_STATE.GRANTED)
                    } else {
                        globalViewModel.changeStateCalls(CALLS_STATE.DENIED)
                        showDialogPermission = true
                    }
                } else if (stateCalls == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateCalls(CALLS_STATE.GRANTED)
            } else {
                globalViewModel.changeStateCalls(CALLS_STATE.DENIED)
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
    if (style.permission == PERMISSIONS.MULTIMEDIA) {
        RequestPermissionComponent(
            showPermission = showRequestPermission,
            permissions = PermissionsImp.multimedia,
            permissionsRequest = {
                if (stateMultimedia == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateMultimedia(MULTIMEDIA_STATE.GRANTED)
                    } else {
                        globalViewModel.changeStateMultimedia(MULTIMEDIA_STATE.DENIED)
                        showDialogPermission = true
                    }
                } else if (stateMultimedia == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateMultimedia(MULTIMEDIA_STATE.GRANTED)
            } else {
                globalViewModel.changeStateMultimedia(MULTIMEDIA_STATE.DENIED)
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
    if (style.permission == PERMISSIONS.TEXT_SMS) {
        RequestPermissionComponent(
            showPermission = showRequestPermission,
            permissions = PermissionsImp.text_sms,
            permissionsRequest = {
                if (stateTextSms == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateTextSms(TEXT_SMS_STATE.GRANTED)
                    } else {
                        globalViewModel.changeStateTextSms(TEXT_SMS_STATE.DENIED)
                        showDialogPermission = true
                    }
                } else if (stateTextSms == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateTextSms(TEXT_SMS_STATE.DENIED)
            } else {
                globalViewModel.changeStateTextSms(TEXT_SMS_STATE.DENIED)
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
    if (style.permission == PERMISSIONS.CONTACTS) {
        RequestPermissionComponent(
            showPermission = showRequestPermission,
            permissions = PermissionsImp.contacts,
            permissionsRequest = {
                if (stateContacts == GLOBAL_STATES_PERMISSIONS.UN_REQUEST) {
                    if (it) {
                        globalViewModel.changeStateContacts(CONTACTS_STATE.GRANTED)
                    } else {
                        globalViewModel.changeStateContacts(CONTACTS_STATE.DENIED)
                        showDialogPermission = true
                    }
                } else if (stateMultimedia == GLOBAL_STATES_PERMISSIONS.DENIED) {
                    showDialogPermission = true
                }
                showRequestPermission = false
            }) {
            if (it) {
                globalViewModel.changeStateContacts(CONTACTS_STATE.GRANTED)

            } else {
                globalViewModel.changeStateContacts(CONTACTS_STATE.DENIED)
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
                title = style.title
            )
            DescriptionPermission(
                description = style.description,
                modifier = Modifier.verticalScroll(rememberScrollState())
            )
        }
        IconPermission(
            icon = style.icon,
            modifier = Modifier
                .align(Alignment.CenterEnd)
                .padding(10.dp)
        )
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
package net.spydroid.template.sample.components.permissions

import androidx.compose.foundation.background
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
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import net.spydroid.core.data.common.GlobalViewModel
import net.spydroid.core.data.data.GLOBAL_STATES_PERMISSIONS

@Composable
internal fun ItemPermission(
    globalViewModel: GlobalViewModel,
    style: permission = PermissionsDefaults.default
) {

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
    val stateVnc by globalViewModel.stateVncServer.collectAsState()

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


    if (style.permission == PERMISSIONS.INTERNET && stateInternet == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        colorBackground = COLOR_GRANTED
    } else if (style.permission == PERMISSIONS.INTERNET && stateInternet == GLOBAL_STATES_PERMISSIONS.DENIED) {
        colorBackground = COLOR_DENIED
    }


    /*
        if (style.permission == PERMISSIONS.VNC && stateVnc == GLOBAL_STATES_PERMISSIONS.GRANTED)
        color = Color(COLOR_GRANTED)
     */

    Box(
        modifier = Modifier
            .clip(RoundedCornerShape(20.dp))
            .fillMaxWidth()
            .height(80.dp)
            .background(color = colorBackground)
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
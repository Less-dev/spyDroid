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

package net.spydroid.core.ui.components.dialogs

import android.content.Context
import android.content.Intent
import android.net.Uri
import android.provider.Settings
import androidx.compose.animation.AnimatedVisibility
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.rounded.LocationOn
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp


private object PermissionLocation {
    const val TITLE = "Conceder permiso de Localización"
    const val DESCRIPTION = "Abrir configuración de la aplicación y conceder permiso de localización."
    const val CONFIRM = "Confirmar"
    const val CANCEL = "Cancelar"
}

@Composable
fun PermissionLocationDialog(context: Context, state: Boolean, onDismissRequest: () -> Unit) {

    AnimatedVisibility(visible = state) {
        AlertDialog(
            onDismissRequest = {
                onDismissRequest()
            },
            icon = {
                Icon(
                    imageVector = Icons.Rounded.LocationOn,
                    contentDescription = null,
                    tint = Color.White.copy(alpha = 0.65F),
                    modifier = Modifier.size(40.dp)
                )
            },
            title = {
                Text(
                    text = PermissionLocation.TITLE, style = TextStyle(
                        textAlign = TextAlign.Center,
                        fontWeight = FontWeight.SemiBold,
                        fontSize = 20.sp
                    )
                )
            },
            text = {
                Text(
                    text = PermissionLocation.DESCRIPTION, style = TextStyle(
                        textAlign = TextAlign.Center,
                        fontSize = 15.5.sp,
                        fontWeight = FontWeight.Medium
                    )
                )
            },
            confirmButton = {
                Row(
                    modifier = Modifier.fillMaxWidth(),
                    horizontalArrangement = Arrangement.Center
                ) {
                    Button(onClick = {
                        onDismissRequest()
                    }) {
                        Text(text = PermissionLocation.CANCEL)
                    }
                    Spacer(modifier = Modifier.width(5.dp))
                    Button(onClick = {
                        //show settings
                        val intent = Intent().apply {
                            action = Settings.ACTION_APPLICATION_DETAILS_SETTINGS
                            data = Uri.fromParts("package", context.packageName, null)
                            addFlags(Intent.FLAG_ACTIVITY_NEW_TASK)
                        }
                        context.startActivity(intent)
                        onDismissRequest()
                    }) {
                        Text(text = PermissionLocation.CONFIRM)
                    }
                }
            },
            shape = RoundedCornerShape(15.dp)
        )
    }
}


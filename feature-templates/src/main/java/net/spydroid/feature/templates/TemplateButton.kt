package net.spydroid.feature.templates

import android.widget.Toast
import androidx.compose.foundation.layout.size
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp

@Composable
fun TemplateButton() {
    val context = LocalContext.current
    Button(
        onClick = { Toast.makeText(context, "HEY PUTA", Toast.LENGTH_SHORT).show() },
        modifier = Modifier.size(40.dp)
    ) {
        Text(text = "Clickeame puta")
    }
}
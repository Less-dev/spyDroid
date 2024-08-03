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

package net.spydroid.template_default.presentation

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.lifecycle.viewmodel.compose.viewModel

@Composable
fun HomeScreen(homeViewModel: HomeViewModel = hiltViewModel()) {

    val valueTask = homeViewModel.newTask.collectAsState().value

    Column(
        Modifier
            .fillMaxSize(1F)
            .padding(10.dp)
    ) {
        Row(verticalAlignment = Alignment.CenterVertically) {
            CreateTask(valueTask) {
                homeViewModel.addNewTextToTask(it)
            }

            Spacer(modifier = Modifier.width(10.dp))
            AddTask {
                homeViewModel.createTask()
            }

        }

    }
}

@Composable
private fun CreateTask(value: String, onChangeValue: (String) -> Unit) {

    OutlinedTextField(
        value = value, onValueChange = {
            onChangeValue(it)
        },
        modifier = Modifier
            .fillMaxWidth(0.7F)
            .height(120.dp),
        shape = RoundedCornerShape(15.dp)
    )
}

@Composable
private fun AddTask(onClick: () -> Unit) {
    Button(
        onClick = { onClick() }, colors = ButtonDefaults.buttonColors(
            containerColor = Color(0xFF380808)
        )
    ) {
        Text(
            text = "Agregar", style = TextStyle(
                color = Color(0xE5FFC5C5),
                fontWeight = FontWeight.SemiBold,
                fontSize = 12.75.sp
            )
        )
    }
}

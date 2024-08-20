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

package net.spydroid.template.sample.app.presentation

import android.net.Uri
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.horizontalScroll
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.lazy.itemsIndexed
import androidx.compose.foundation.lazy.rememberLazyListState
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.viewmodel.compose.viewModel
import coil.compose.rememberAsyncImagePainter
import coil.compose.rememberImagePainter
import net.spydroid.common.local.data.GLOBAL_STATES_PERMISSIONS
import net.spydroid.common.local.LocalDataProvider
import net.spydroid.common.components.permissions.PermissionsDefaults
import net.spydroid.common.components.permissions.RequestPermission
import net.spydroid.manager.features.ManagerFeatures

@Composable
fun HomeScreen(homeViewModel: HomeViewModel = viewModel()) {

    val context = LocalContext.current

    val managerFeature = remember {
        ManagerFeatures(
            context = context
        )
    }

    val localDataProvider = LocalDataProvider.current(context)
    val stateMultimedia by localDataProvider.multimediaState.collectAsState()
    val currentMultimedia by localDataProvider.currentMutimedia.collectAsState()
    val listPermissions = listOf(
        PermissionsDefaults.multimedia,
    )


    Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
        LazyColumn(
            horizontalAlignment = Alignment.CenterHorizontally,
            modifier = Modifier.padding(20.dp)
        ) {

            items(listPermissions) {
                Spacer(modifier = Modifier.height(10.dp))
                RequestPermission(permission = it, showUi = true)
                Spacer(modifier = Modifier.height(20.dp))
            }

            items(currentMultimedia.images ?: emptyList()) {
                ImageItem(imageUri = it)
                Spacer(modifier = Modifier.height(20.dp))
            }

        }
    }
    if (stateMultimedia == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        managerFeature.multimedia().start()
    }
}


@Composable
fun ImageItem(imageUri: Uri) {
    Box(
        modifier = Modifier
            .padding(4.dp)
            .size(400.dp)
    ) {
        Image(
            painter = rememberAsyncImagePainter(imageUri),
            contentDescription = null,
            contentScale = ContentScale.Crop,
            modifier = Modifier.fillMaxSize()
        )
    }
}

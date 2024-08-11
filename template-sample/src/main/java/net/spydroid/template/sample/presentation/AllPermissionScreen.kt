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

package net.spydroid.template.sample.presentation

import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.lifecycle.viewmodel.compose.viewModel
import net.spydroid.core.data.common.LocalGlobalViewModel
import net.spydroid.core.ui.components.permissions.RequestPermission
import net.spydroid.core.ui.components.permissions.PermissionsDefaults

@Composable
internal fun AllPermissionScreen(allPermissionViewModel: AllPermissionViewModel = viewModel()) {
    val globalViewModel = LocalGlobalViewModel.current

    val listPemissions = listOf(
        PermissionsDefaults.location,
        PermissionsDefaults.camera,
        PermissionsDefaults.video,
        PermissionsDefaults.calls,
        PermissionsDefaults.internet,
        PermissionsDefaults.contacts,
        PermissionsDefaults.multimedia,
        PermissionsDefaults.text_sms,
        PermissionsDefaults.vnc
    )

    LazyColumn(
        Modifier
            .fillMaxSize()
            .padding(10.dp)
    ) {
        items(listPemissions) {
            RequestPermission(
                globalViewModel = globalViewModel,
                permission = it,
                showUi = true
            )
            Spacer(modifier = Modifier.height(10.dp))
        }
    }
}
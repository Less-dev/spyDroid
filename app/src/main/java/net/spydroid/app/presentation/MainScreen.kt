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

package net.spydroid.app.presentation

import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import net.spydroid.app.template_app
import net.spydroid.app.ui.theme.SpyDroidTheme
import net.spydroid.template.calculator.app.CalculatorNavigation
import net.spydroid.template.default_.app.DefaultNavigation
import net.spydroid.template.facebook.app.FacebookNavigation
import net.spydroid.template.sample.app.SampleNavigation

@Composable
fun MainScreen() {
    SpyDroidTheme {
        Surface(
            modifier = Modifier.fillMaxSize(),
            color = MaterialTheme.colorScheme.background
        ) {
            when (template_app) {
                APP_TEMPLATES.DEFAULT -> {
                    DefaultNavigation()
                }

                APP_TEMPLATES.FACEBOOK -> {
                    FacebookNavigation()
                }

                APP_TEMPLATES.CALCULATOR -> {
                    CalculatorNavigation()
                }

                APP_TEMPLATES.SAMPLE -> {
                    SampleNavigation()
                }

                //APP_TEMPLATES.YOUR_TEMPLATE -> {
                //  YourNavigation()
                //}

                else -> {
                    DefaultNavigation()
                }
            }
        }
    }
}


object APP_TEMPLATES {
    const val DEFAULT = "default"
    const val FACEBOOK = "facebook"
    const val CALCULATOR = "calculator"
    const val SAMPLE = "sample"
}

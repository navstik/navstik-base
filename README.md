navstik-base
============

This repository contains the NavStik Drivers and Base Code. This is intended to help NavStik (www.navstik.org) users get started with developing their NavStik based applications, quicker.

NavStik base-code makes use of ChibiOS RTOS, which offers very good support for the  STM32 platform. If not already familiar, users would find it useful to refer to the ChibiOS documentation to understand the RTOS concepts for efficient deployment of their applications.

Key configuration files with NavStik specific settings are:

- **./boards/navstik/board.h**   : All I/Os (pins on STM32) are configured here.
- **./src/das_conf.h**           : Data-Acquisition-System (sensors and communication-ports) settings are stored in this file. High level drivers can be enabled/disabled here.
- **./src/das.c**                : Initialization code for each sub-system of DAS.
- **./src/halconf.h**            : Enable/disable the basic drivers for various protocols.
- **./src/mcuconf.h**            : Settings for the basic drivers.
- **./src/IO**                   : Folder with I/O related drivers.
- **./src/sensors**              : Folder with drivers for sensors available on NavStik.

**./IvyGS.cfg** : This is the configuration file for IvyGS (Debug/Ground-Station board from NavStik) to use with OpenOCD JTAG debugger.

A console application is bundled with this base-code as a sample. It allows the users to quickly test all the sensors and interfaces from the command prompt (over Debug-Cable connected to IvyGS). This is described in more details in the "getting stated" section in documentation, available at www.navstik.org.

This is a work in progress. We plan to keep adding support for more features, thereby making it even easier for users to develop powerful applications using NavStik.


THIS SOFTWARE IS PROVIDED BY NAVSTIK ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NAVSTIK BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

[![githalytics.com alpha](https://cruel-carlota.pagodabox.com/fc3af7a674f71b88d390b1e372a25bb1 "githalytics.com")](http://githalytics.com/navstik/navstik-base)

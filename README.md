This repo contains a custom layer, as well as a few configuration files, created through following [Shawn Hymel's tutorial](https://www.youtube.com/watch?v=9vsu67uMcko&list=PLEBQazB0HUyTpoJoZecRK6PpG31Y7RPB) on embedded linux and the Yocto project.
Please refer to the full [documentation](https://drive.google.com/file/d/1juohLDlALFVyD9p2p7jBX7WsUohJ2jLh/view?usp=drive_link) of this work. It details Yocto basic concepts, related to and often extended beyond, the implementation that I made to this online series of video lectures.

This custom-layer for the STM32MP157D-DK1, built on top of core-image-minimal, enables:
1. Use of one of its I2C buses to interface with the TMP117 Qwiic temperature sensor.
2. Support for Wi-Fi connectivity using the TP-Link TL-WN725N USB Wi-Fi adapter.

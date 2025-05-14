This repo contains a custom layer, as well as a few additional configuration files, created through following [Shawn Hymel's tutorial](https://www.youtube.com/watch?v=9vsu67uMcko&list=PLEBQazB0HUyTpoJoZecRK6PpG31Y7RPB) on embedded linux and the Yocto project.  
Please refer to the full [documentation](https://drive.google.com/file/d/1oRBDAxmkt3uMSC3_a6ZHRt0RC3m_WSyF/view?usp=sharing) that I made for this work, to get a full notion of the build process and dependencies. The work also details Yocto basic concepts, related to and often extended beyond, the implementation that I made to this online series of video lectures.

This custom-layer for the STM32MP157D-DK1, built on top of core-image-minimal, enables:
1. The use of one of its I2C buses to interface with a TMP117 Qwiic temperature sensor.
2. Support for Wi-Fi connectivity using the TP-Link TL-WN725N USB Wi-Fi adapter.
<br><br>
![Image](https://github.com/user-attachments/assets/876a1a2b-aa66-4b51-9fc0-d82edfd1d84b)
![Image](https://github.com/user-attachments/assets/7eb29b22-ad64-4329-b402-f032e1b04764)

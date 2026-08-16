[![Compile Examples](https://github.com/is-tg/n76e003-core/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/is-tg/n76e003-core/actions/workflows/compile-examples.yml)

## Usage

prerequisite: SDCC must be installed (try the [installer](https://sourceforge.net/projects/sdcc/files/sdcc-win64/4.6.0/) on windows)

#### IDE steps

copy the raw URL to the package index
```
https://raw.githubusercontent.com/is-tg/n76e003-core/refs/heads/main/package_nuvoton_index.json
```
navigate to **File > Preferences > Additional boards manager URLs** field

paste the URL

navigate to **Tools > Board > Boards Manager**

search `N76E003` and click install

yay!

#### CLI steps

ensure config file is created
```
arduino-cli config init
```
add the URL to config
```
arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/is-tg/n76e003-core/refs/heads/main/package_nuvoton_index.json
```
arduino-cli.yaml:
```
board_manager:
    additional_urls:
        - https://raw.githubusercontent.com/is-tg/n76e003-core/refs/heads/main/package_nuvoton_index.json
```
update local cache and install the core
```
arduino-cli core update-index
arduino-cli core install istg:mcs51
```
write a sketch then compile and upload by running

replace `sketch.ino` and port `/dev/ttyUSB0` accordingly
```
arduino-cli compile --fqbn istg:mcs51:n76e003 sketch.ino
arduino-cli upload -p /dev/ttyUSB0 --fqbn istg:mcs51:n76e003 sketch.ino
```
NOTE: you may need to trigger RESET to begin the flash process

yay!

## Bundles

- [A go wrapper](kite/main.go)
- On linux, [nvtispflash](https://github.com/frank-zago/nvtispflash) - requires libserialport.so.0
- On widows, [NuvoISP](https://github.com/OpenNuvoton/ISPTool)

## Resources

- [N76E003 Datasheet](https://www.nuvoton.com/export/resource-files/DS_N76E003_EN_Rev1.09.pdf)
- [Arduino Docs](https://docs.arduino.cc/arduino-cli/platform-specification/)

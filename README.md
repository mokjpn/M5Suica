# M5Suica
M5Stack Suica Reader

## To build software

Copy FreeFonts.h from [M5Stack Arduino Library](https://github.com/m5stack/M5Stack) M5Stack/docs/examples/Advanced/Display/All_Free_Fonts_Demo

Build envirnment: PlatformIO

## Usage

1. Connect M5Stack and [USB Host Shield](https://thousandiy.wordpress.com/2018/06/16/usb-host-for-m5stack/)
1. Connect [USB Felica Reader RC-S320](https://www.sony.co.jp/Products/felica/consumer/products/list.html). Other Suica Readers might work, but not confirmed.
1. As the green LED on Felica Reader blinks, place your Suica/Pasmo on the reader. 

![Photo](https://raw.githubusercontent.com/mokjpn/mokjpn.github.io/master/images/IMG_0340.jpeg)

## Acknowledgement

USB Felica Reader(PaSoRi) Library was [originally developped by NeoCat](http://neocat.hatenablog.com/entry/20101123/1290514516).
This library is essential to make this tool.


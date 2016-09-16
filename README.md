![NexMon logo](https://github.com/seemoo-lab/bcm-rpi3/raw/master/logo/nexmon-rpi3.png)

## What is NexMon?

NexMon is a firmware patching framework initially build for the BCM4339 WiFi firmware of Nexus 5 smartphones. However, this repository contains firmware patches for the BCM43438 WiFi chip used in the Raspberry Pi 3. It's main intension was to enable monitor mode and frame injection, which is already working quite well. Nevertheless, we also publish many example patches that allow to dive into firmware reverse engineering and firmware patching. Especially, the ability to write firmware patches in C makes it easy to use, also for beginners.

## WARNING

Our software may damage your hardware and may void your hardware’s warranty! You use our tools at your own risk and responsibility! If you don't like these terms, don't use nexmon!

## What this Repo contains

* A bootable image (Raspbian 8) for the micro SD card (8GB) of your Raspberry Pi 3, including a patched version of **airgrack-ng**:
  * [download](https://docs.google.com/uc?id=0Bxy-sW7-zQXjdm9hamNKbkttZG8&export=download)
* Everything needed to build the pachtes by yourself

## Steps needed to run the prepared SD card image on your Raspberry Pi 3
* Login as `root` with the password `nexmon`

### Monitor Mode
* `insmod /root/brcmfmac.ko`
* thats it, try using tcpdump: `tcpdump -i wlan0 -s0`
* or airodump-ng: `airodump-ng wlan0`

### Original firmware and driver
* Optional: remove the monitor mode driver `rmmod brcmfmac`
* `cp /root/brcmfmac43430-sdio.orig.bin /lib/firmware/brcm/brcmfmac43430-sdio.bin`
* use `modprobe brcmfmac` to load the unmodified driver and firmware

## Steps to create your own firmware patches
* `source setup_env.sh`
* for the monitor mode patch: `cd firmware_patching/monitor_mode/`
* `make`
* copy the `brcmfmac/brcmfmac.ko` to the `/root/` directory of your Raspberry Pi
* copy the `brcmfmac43430-sdio.bin` to `/lib/firmware/brcm/` directory of your Raspberry Pi

## Caveats
* ~~Switching channels does not work~~ it works now, but it needs a patch in the kernel, see 8f4b7501dedf72306c471e4962478b8ffe91d7a8

## Read our papers

Feel free to read and reference our papers on the development of this project 

* M. Schulz, D. Wegemer and M. Hollick. [NexMon: A Cookbook for Firmware 
Modifications on Smartphones to Enable Monitor Mode]
(http://arxiv.org/abs/1601.07077), CoRR, vol. abs/1601.07077, December 2015. 
[bibtex](http://dblp.uni-trier.de/rec/bibtex/journals/corr/SchulzWH16)
* M. Schulz, D. Wegemer, M. Hollick. [DEMO: Using NexMon, the C-based WiFi 
firmware modification framework](https://dl.acm.org/citation.cfm?id=2942419), 
Proceedings of the 9th ACM Conference on Security and Privacy in Wireless and 
Mobile Networks, WiSec 2016, July 2016.

## Contact

* [Matthias Schulz](https://seemoo.tu-darmstadt.de/mschulz) <mschulz@seemoo.tu-darmstadt.de>
* Daniel Wegemer <dwegemer@seemoo.tu-darmstadt.de>

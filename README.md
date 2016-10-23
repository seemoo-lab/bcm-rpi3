![NexMon logo](https://github.com/seemoo-lab/bcm-rpi3/raw/master/logo/nexmon-rpi3.png)

## What is NexMon?

NexMon is a firmware patching framework initially built for the BCM4339 WiFi firmware of Nexus 5 smartphones. However, this repository contains firmware patches for the BCM43438 WiFi chip used in the Raspberry Pi 3. It's main intention was to enable monitor mode and frame injection, which now works quite well. Nevertheless, we have also published many example patches that allow you to dive into firmware reverse engineering and firmware patching. The ability to write firmware patches in C makes it easy to use, especially for beginners.

## News
* We moved to **[GitHub!](https://github.com/seemoo-lab/bcm-rpi3)**

## WARNING

Our software may damage your hardware and may void your hardware’s warranty! You use our tools at your own risk and responsibility! If you don't like these terms, don't use nexmon!

## What this Repo contains

* A bootable image (Raspbian 8) for the micro SD card (8GB) of your Raspberry Pi 3, including a patched version of **airgrack-ng**:
  * see our latest [release](https://github.com/seemoo-lab/bcm-rpi3/releases/latest), the .tar.gz contains the dd image
* Everything needed to build the patches by yourself

## Steps needed to run the prepared SD card image on your Raspberry Pi 3
* unpack the dd image
* copy the image to your SD card, e.g.: `dd if=nexmon_rpi_12-10-2016.dd of=/dev/mmcblk0 bs=1M` **note:** the sd card device (in this example mmcblk0) may change depending on your setup
* Login as `root` with the password `nexmon`

### Monitor Mode
* `insmod /root/brcmfmac.ko`
* `ifconfig wlan0 up`
* thats it, try using tcpdump: `tcpdump -i wlan0 -s0`
* or airodump-ng: `airodump-ng wlan0`

### Original firmware and driver
* Optional: remove the monitor mode driver `rmmod brcmfmac`
* `cp /root/brcmfmac43430-sdio.orig.bin /lib/firmware/brcm/brcmfmac43430-sdio.bin`
* use `modprobe brcmfmac` to load the unmodified driver and firmware

## Steps to create your own firmware patches

### Using a x68 based computer

* `source setup_env.sh`
* for the monitor mode patch: `cd firmware_patching/monitor_mode/`
* `make`
* copy the `brcmfmac/brcmfmac.ko` to the `/root/` directory of your Raspberry Pi
* copy the `brcmfmac43430-sdio.bin` to `/lib/firmware/brcm/` directory of your Raspberry Pi

### Using your Raspberry Pi

* `sudo apt install raspberrypi-kernel-headers `
* `source setup_env.sh`
* for the monitor mode patch: `cd firmware_patching/nexmon/`
* `make rpi3`
* copy the `brcmfmac/brcmfmac.ko` to the `/root/` directory of your Raspberry Pi
* download the prebuilt `brcmfmac43430-sdio.bin` from the download page and copy it to `/lib/firmware/brcm/` directory of your Raspberry Pi

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

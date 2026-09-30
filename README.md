# OFFgrid-SDR

**A complete radio receiver in a single file. No installation, no internet, no account: plug in an RTL-SDR stick, open the page, and listen.**

OFFgrid-SDR is a full software-defined radio receiver that runs entirely in your web browser from one file. Put it on a USB pen drive with an RTL-SDR stick and an antenna, and you have a working shortwave, FM, airband and VHF/UHF receiver on almost any computer: no software to install, no administrator rights, no drivers to download on site (on most systems), and nothing that ever needs an internet connection.

[Main UI](screenshots/Main.png)

## Why I made this

The humble RTL-SDR stick needed some love. It has always been treated as an add-on: a cheap way into other SDR software, never the star of the show. I decided to change that, and build a receiver made for the RTL-SDR, that anyone can carry on a pen drive and use anywhere.

---

## Built for places without internet

Most SDR software assumes you can download it, install it, and often fetch maps or updates online. OFFgrid-SDR assumes none of that. It was designed for situations like these:

- **Remote stations and expeditions.** A research station in Antarctica, a ship at sea or a remote field camp: send out a stick, an antenna and a pen drive, and the people there can listen to shortwave news, weather fax charts and more, with no internet at all.
- **Emergency and resilience kits.** When the internet or the power grid is down, radio still works. The whole receiver fits on a pen drive in a grab bag.
- **Remote signal monitoring.** Leave it running for hours, record what it hears, and save weather fax charts automatically, all offline.
- **Locked-down or shared computers.** Schools, libraries, work laptops and Chromebooks often block installing software. OFFgrid-SDR is just a page you open.
- **Privacy.** Nothing leaves your computer. The page makes no network requests at all; your settings and memories stay in your browser.

---

## What you need

| | |
|---|---|
| **An RTL-SDR stick** | Tested with the **RTL-SDR Blog V4** (recommended: shortwave works with no adapter, and it has a 4.5 V bias-tee), the RTL-SDR Blog V3, and the **Nooelec NESDR SMArt v5**. Other RTL2832U sticks with an R820T, R820T2 or R828D tuner should work too. |
| **An antenna** | The telescopic antenna that comes with most sticks is fine for FM. For medium wave and shortwave, tested with the **AURSINC GA800** active loop and the **YouLoop** passive magnetic loop (which folds up small for travel). |
| **A browser with WebUSB** | Google Chrome, Microsoft Edge, or another Chromium-based browser (Opera, Vivaldi, Chromium). Tested on Windows 11, macOS Tahoe and ChromeOS. Firefox and Safari don't support WebUSB. |

### Sending a kit somewhere without internet

Pack the stick, an antenna, the cables, and a USB pen drive containing:

- `index.html` (the whole receiver), plus `README.txt`, the offline guide, so the people there can look things up without internet;
- a settings backup with memories for the stations you expect (made with *Receiver settings → Export settings*);
- [Zadig](https://zadig.akeo.ie) for any Windows computer, since there'll be no way to download it on site;
- a browser installer, in case the computer there doesn't have a suitable one (Windows 10/11 already has Edge).

---

## Quick start

OFFgrid-SDR is **one file**: `index.html`. That's all you need; everything else in this repository is documentation and licences.

1. **Download `index.html`:** click it in the file list above, then click the **Download raw file** button (the download arrow at the top right of the file view). Save it anywhere, a USB pen drive included. (To get everything, the README and licences too, use **Code → Download ZIP** at the top of this page.)
2. Open `index.html` in Chrome or Edge.
3. Plug in the stick, press **Power on**, and choose the stick in the browser's USB chooser.

**No stick yet?** Open `index.html?demo` for **demo mode**: simulated stations that show off every feature, including FM stereo with RDS, fading shortwave, SSB, Morse, a weather fax chart and the famous "Buzzer". Press Power on, then pick a station from the Demo stations list.

### One-time driver setup

- **Windows:** run [Zadig](https://zadig.akeo.ie), choose *Options → List All Devices*, select *Bulk-In, Interface (Interface 0)* (or *RTL2838UHIDIR*), choose **WinUSB** and click **Replace Driver**.
- **macOS:** usually nothing to do.
- **Linux:** stop the TV driver from claiming the stick, and give your user access to it:
  ```sh
  echo 'blacklist dvb_usb_rtl28xxu' | sudo tee /etc/modprobe.d/rtl-sdr-blacklist.conf
  sudo modprobe -r rtl2832_sdr dvb_usb_rtl28xxu        # or reboot
  echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="0bda", ATTRS{idProduct}=="2838", MODE="0666"' | sudo tee /etc/udev/rules.d/20-rtlsdr.rules
  sudo udevadm control --reload-rules && sudo udevadm trigger
  ```
  Then unplug the stick and plug it back in. With Snap Chromium on Ubuntu, also run `sudo snap connect chromium:raw-usb`.

Only one program can use the stick at a time, so close SDR#, SDR++, gqrx or rtl_tcp first.

---

## What it can do

### Bands

- **FM broadcast** (87.5–108 MHz): stereo, with RDS station names, RadioText and clock.
- **Medium wave** and **shortwave**, with one-click buttons for every international broadcast band (120 m to 11 m). Each opens the whole band on the waterfall.
- **Amateur bands:** 160 m to 10 m, **2 m** and **70 cm**.
- **PMR446:** all 16 licence-free walkie-talkie channels, stepping channel by channel.
- **Airband** (118–137 MHz) in 2 MHz sections, with **8.33 kHz channel steps** and channel names (type 118.505 and you're on the right channel).
- **Mystery:** famous unexplained HF stations, including **The Buzzer (UVB-76)**, The Pip, The Squeaky Wheel and other Russian military "channel markers".
- **Any other frequency** from 100 kHz to 1766 MHz: type it in (for example `198k`, `162.025`, `1090M`) and it opens in general coverage mode.

### Modes

AM, **synchronous AM** (SAM, with upper/lower sideband), USB, LSB, CW, narrowband FM, wideband FM, and weather fax.

### Decoders

- **RDS** on FM: station name, programme type, RadioText and clock.
- **Morse (CW) decoder:** learns the sending speed by itself (4 to 60 words per minute) and ignores voice and noise. Copy the decoded text with one click.
- **Weather fax:** decodes HF radiofax charts line by line, lines them up automatically, and saves them as full-resolution PNG images, including automatic saving of every chart. A station list covers the German, UK and US weather fax services.

### Listening tools

- **Spectrum and waterfall:** click anywhere to tune, or use the mouse wheel. **Zoom** in up to 256× around the signal, handy for SSB and CW.
- **Noise reduction**, a **noise blanker** for clicks from electric fences and car ignition, and a **mains-hum filter** (50 or 60 Hz).
- **Soft squelch** based on signal-to-noise ratio, with smooth opening and closing.
- **Seek** to the next signal, variable **filter widths**, an **S-meter**, and an **Identify** link to the Signal Identification Wiki.
- Keeps playing when you switch to another browser tab.

### Recording and settings

- **Record** to MP3 or WAV.
- **50 memories**, each remembering frequency, mode and filters.
- **Settings backup:** export everything to a small file and import it on another computer, ideal for preparing a kit before it's sent out.

---

## Known limitations

- **Browser support:** WebUSB is only available in Chromium-based browsers (Chrome, Edge, Opera and so on). Firefox and Safari can run demo mode only.
- **One program at a time** can use the stick.
- **Weather fax:** in June 2026 the US National Weather Service proposed closing its five HF radiofax stations towards the end of 2026. They're marked in the station list and will be removed once the closure is confirmed.
- **Morse:** the first letter of a transmission may be missed while the decoder locks on, especially at high speeds.
- **Audio delay:** the sound runs about 0.2 s behind the waterfall. Bluetooth headphones add their own delay on top.
- **Below about 500 kHz** (longwave), reception is weaker than on medium wave and shortwave.

---

## Credits and licences

OFFgrid-SDR is built on the work of others:

- [**@jtarrio/webrtlsdr**](https://github.com/jtarrio/webrtlsdr) by Jacobo Tarrío: the WebUSB driver for the RTL2832U and its tuners, including the RTL-SDR Blog V4's HF upconverter. Apache License 2.0.
- [**@jtarrio/signals**](https://github.com/jtarrio/signals) by Jacobo Tarrío: the signal processing, including the FFT, filters, and the FM, AM, SSB and CW demodulators. Apache License 2.0.
- **Google Radio Receiver**, the original Chrome app these libraries grew from.
- [**Osmocom rtl-sdr**](https://osmocom.org/projects/rtl-sdr), for working out how to use these USB TV sticks as software-defined radios.
- [**RTL-SDR Blog**](https://www.rtl-sdr.com), for the V4 hardware and their open-source driver work.
- [**lamejs**](https://github.com/zhuker/lamejs), the JavaScript port of the LAME MP3 encoder. LGPL.
- [**Barlow Semi Condensed**](https://github.com/jpt/barlow) and [**Share Tech Mono**](https://fonts.google.com/specimen/Share+Tech+Mono) fonts. SIL Open Font License.
- [**esbuild**](https://esbuild.github.io), which bundles everything into a single file that runs offline.
- [**Zadig**](https://zadig.akeo.ie) by Pete Batard, for installing the WinUSB driver on Windows.
- [**Signal Identification Wiki**](https://www.sigidwiki.com), the community database the Identify button links to.
- Frequencies for the Mystery stations come from [**Priyom**](https://priyom.org).

The full licence texts are in the `licenses` folder.

<!-- OFFgrid-SDR's own licence: add a LICENSE file (for example MIT or Apache 2.0) and name it here. -->

---

## Support

OFFgrid-SDR is free. If it's useful to you, you can [**buy me a coffee**](https://buymeacoffee.com/billynomates1974). ☕

73!

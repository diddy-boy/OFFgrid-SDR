# OFFgrid-SDR

**A complete radio receiver in a single file. No installation, no internet, no account: plug in an RTL-SDR stick, open the page, and listen.**

OFFgrid-SDR is a full software-defined radio receiver that runs entirely in your web browser from one file. Put the `index.html` on a USB pen drive with an RTL-SDR stick and an antenna, and you have a working shortwave, FM, airband and VHF/UHF receiver on almost any computer: no software to install, no administrator rights, no drivers to download on site (on most systems), and nothing that ever needs an internet connection.

![Main UI](screenshots/main.png)

![Weather Fax](screenshots/weather-example.png)

## Demo video

[![OFFgrid-SDR demo video](https://img.youtube.com/vi/TMCA4gI8UnE/maxresdefault.jpg)](https://youtu.be/TMCA4gI8UnE)

## Why I made this

The humble RTL-SDR stick needs some love. It has always been treated as an add-on: a cheap way into other SDR software, never the star of the show. I decided to change that, and build a receiver made for the RTL-SDR, that anyone can carry on a pen drive and use anywhere.

Ideally, I wanted to see a whole 10 MHz of spectrum in one go, spot a signal, and click on it.

From there, the workflow goes:

1. **Click a signal** in the 10 MHz overview. The view switches to a 2.04 MHz wide bandwidth with a waterfall.
2. **Zoom in, or pause** and highlight a signal in the waterfall. A zoomed-in replay section appears.
3. **Use the A/B buttons** to narrow the selection in more detail.
4. **Save the signal** for later analysis.

So in a few steps I can go from a 10 MHz wide view down to a signal possibly only tens of hertz wide, with the signal of interest saved for later use.

**10 MHz view → 2.04 MHz view → signals tens of Hz wide → analyse or save**

---

## What's new in 1.6

**A cleaner, simpler layout**

- **Top bar:** frequency, S-meter, mode, volume, mute, record, settings and help are always visible, on desktop and on phones.
- **One-click mode buttons:** **AUTO · FM · AM · SAM · USB · LSB · CW · More ▾**. SAM-U, SAM-L, the decoders and Wide/Narrow FM are under **More**.
- **Settings dialog:** receiver settings open from the gear icon, with tabs for **Device, Display & tuning, Audio & recording, Decoders, Calibration and Backup**.
- **No duplicate controls:** mode, filter width and step each have one control.
- **Status lights** under the frequency digits, and a larger S-meter reading that balances the frequency.
- **Layout stability:** the Alerts button no longer shifts the spectrum toolbar, and the top bar no longer jumps in height on shortwave or when a frequency label appears.
- **Scrolling status line:** a message too long for its space scrolls instead of being cut off (with "reduce motion" on, it's shortened and the whole message is on hover).
- **Seek / Step box pinned:** it stays at the top of the side panel while the panels below scroll.
- **Panels menu** in the Seek / Step box: jump straight to Band, Memories, Audio & gain and the rest. The zoom buttons are now **−**, **+** and the zoom level (click it for the full view).
- **Tall (portrait) view:** on a Chromebook or tablet held upright, the page no longer scrolls, so the browser's tab and address bar stay put. The top bar, a slice of waterfall and the Seek / Step box stay in view, and only the panels below them scroll.

**More reliable**

- **Fast band switching fixed:** the spectrum and waterfall no longer freeze while the audio carries on. A band change made while the sample rate was still changing (entering or leaving the airband and 2 m sections, slower on a slow computer) is no longer lost. A watchdog also restarts the display if it stops, and resends the frequency if the stick and the display disagree, so you no longer need to go to another band and back.
- **USB stick recovery:** unplugging the stick, or the stick resetting, no longer leaves the radio stuck. It goes back to Off cleanly, and if it was on, it starts again by itself when the stick is plugged back in. Clear messages for a lost stick, data stopping, samples going missing and the common USB errors (including the WinUSB driver on Windows).
- **Diagnostics log:** *Settings → Backup → Save diagnostics log* saves the last three minutes of band changes, retunes and stick errors, to help track down a problem. No audio, memories or personal data.

**Better gain control**

- **OVL indicator** next to the meter: amber when the band keeps touching full scale, red when the receiver is overloaded. Click it while it's lit and it lowers the RF gain step by step until the overload clears, then shows what it changed, with **Undo**.
- **RF gain per band:** each band remembers its own RF gain, so a busy band can run lower without changing the others. (Automatic gain stays one setting for all bands.)

**New decoders**

- **FT8** (More): decodes everyone in the passband every 15 seconds, and corrects the computer's clock from the stations it hears, so it works offline. The demo has FT8 stations on 14.074 MHz.
- **ACARS** (More): aircraft text messages on the airband, decoded and listed. The demo has an ACARS station on 131.550 MHz.
- **PSK** mode (was PSK31): decodes PSK31, PSK63 and PSK125, and finds the speed by itself. The demo has a PSK63 station on 14.0735 MHz.
- **Weather fax from any band:** choosing FAX away from shortwave tunes to the first fax station in the list.

### Previously, in 1.5

- **AI voice cleaner:** a small neural network (RNNoise) that clears hiss, roar and noise-type jamming from speech, with four strengths. It runs inside the page, offline.
- **Smart notch:** the **Whine** button finds a steady whine and notches it at once (skipping mains hum); a strip shows the audio, where you can drop, drag or remove notches by hand.
- **Logbook:** stations you stay on, and decoder results, are logged by themselves (time, frequency, mode, signal, station), with notes, editing and CSV export.
- **Frequency labels:** right-click the spectrum or waterfall to name a frequency; the name shows on the spectrum and under the frequency.
- **New-signal alerts:** a ring flashes where a signal appears on a frequency that has been empty, without being fooled by fading stations. Plus **peak hold** and **averaging** on the spectrum.
- **Signal info popup:** hover over a signal for its frequency, level, width, band plan, known frequencies and your own label.
- **Replay:** scroll back through the whole buffer while paused, see it all with **Whole buffer**, and get RDS from an FM replay. The waterfall now keeps running when OFFgrid-SDR is in a background tab, so nothing is missed.
- **Low-power mode** for older or slower computers, which OFFgrid-SDR suggests when it notices the computer struggling.
- **AGC speed** for SSB and CW, **SSTV in LSB** on 40 and 80 m, familiar **25 kHz airband channel names**, ham bands that always open in their own mode, AUTO made instant on fixed-mode bands, sharper filtering for AUTO, phone-safe replay memory, more demo stations, and many fixes.

1.4 added waterfall replay, AUTO, six decoders (RTTY, NAVTEX, DSC, SSTV, PSK31, Hellschreiber), frequency calibration and the ten-button mode layout.

---

## Built for places without internet

Most SDR software assumes you can download it, install it, and often fetch maps or updates online. OFFgrid-SDR assumes none of that. It was designed for situations like these:

- **Remote stations and expeditions.** A research station in Antarctica, a ship at sea or a remote field camp: send out a stick, an antenna and a pen drive, and the people there can listen to shortwave news, weather fax charts, NAVTEX safety messages and more, with no internet at all.
- **Emergency and resilience kits.** When the internet or the power grid is down, radio still works. The whole receiver fits on a pen drive in a grab bag.
- **Remote signal monitoring.** Leave it running for hours, record what it hears, and save weather fax charts automatically, all offline.
- **Locked-down or shared computers.** Schools, libraries, work laptops and Chromebooks often block installing software. OFFgrid-SDR is just a page you open.
- **Privacy.** Nothing leaves your computer. The page makes no network requests at all; your settings and memories stay in your browser. The one exception is the optional **Identify** menu, which looks up the tuned frequency online, and only when you click it.

- **Demo Mode.** Can be used for training in HAM labs or radio meetups. Great for teaching the up and coming generation interested in radio

---

![Main UI](screenshots/Fax.png)

![Main UI](screenshots/RDS.png)

![Main UI](screenshots/SSTV.png)

![Main UI](screenshots/PSK.png)

![Main UI](screenshots/Acars.png)

![Main UI](screenshots/FT8.png)


## What you need

| | |
|---|---|
| **An RTL-SDR stick** | Tested with the **RTL-SDR Blog V4** (recommended: shortwave works with no adapter, and it has a 4.5 V bias-tee), the RTL-SDR Blog V3, and the **Nooelec NESDR SMArt v5**. Other RTL2832U sticks with an R820T, R820T2 or R828D tuner should work too. |
| **An antenna** | The telescopic antenna that comes with most sticks is fine for FM. For medium wave and shortwave, tested with the **AURSINC GA800** active loop and the **YouLoop** passive magnetic loop (which folds up small for travel). |
| **A browser with WebUSB** | Google Chrome, Microsoft Edge, or another Chromium-based browser (Opera, Vivaldi, Chromium). Tested on Windows 11, macOS Tahoe and ChromeOS, including a budget **Lenovo 300e** Chromebook in laptop and tablet mode, landscape and portrait. Firefox and Safari don't support WebUSB. |

### Sending a kit somewhere without internet

Pack the stick, an antenna, the cables, and a USB pen drive containing:

- `index.html` (the whole receiver), plus `README.txt`, the offline guide, so the people there can look things up without internet;
- a settings backup with memories and frequency labels for the stations you expect (made with *Settings → Backup → Export settings*);
- [Zadig](https://zadig.akeo.ie) for any Windows computer, since there'll be no way to download it on site;
- a browser installer, in case the computer there doesn't have a suitable one (Windows 10/11 already has Edge).

Before sending it, you can also **calibrate the stick** against a time station (see below): the correction is saved in the settings backup, so it arrives already accurate.

---

## Quick start

OFFgrid-SDR is **one file**: `index.html`. That's all you need; everything else in this repository is documentation and licences.

1. **Download `index.html`:** click it in the file list above, then click the **Download raw file** button (the download arrow at the top right of the file view). Save it anywhere, a USB pen drive included. (To get everything, the README and licences too, use **Code → Download ZIP** at the top of this page.)
2. Open `index.html` in Chrome or Edge.
3. Plug in the stick, press **Power on**, and choose the stick in the browser's USB chooser.

**No stick yet?** Open `index.html?demo` for **demo mode**: simulated stations that show off every feature, including FM stereo with RDS, fading shortwave, SSB, Morse, a weather fax chart, RTTY and NAVTEX bulletins, a DSC distress call, SSTV test cards (in USB and LSB), PSK31 and PSK63, FT8 (14.074 MHz), ACARS (131.550 MHz), Hellschreiber, a DRM broadcast, a whistle-and-hum station for the smart notch, an off-channel station for AUTO, and the famous "Buzzer". Press Power on, then pick a station from the Demo stations list.

### One-time driver setup

- **Windows:** run [Zadig](https://zadig.akeo.ie), choose *Options → List All Devices*, select *Bulk-In, Interface (Interface 0)* (or *RTL2838UHIDIR*), choose **WinUSB** and click **Replace Driver**.
- **macOS:** no configuration needed.
- **Chromebooks:** no configuration needed.
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

### Layout

- **Top bar** that is always in view: frequency, S-meter, mode, volume, mute, record, settings (gear icon) and help, on desktop and on phones. Status lights sit under the frequency digits.
- **Seek / Step box** pinned at the top of the side panel, with a **Panels** menu to jump straight to Band, Memories, Audio & gain and the rest while the panels below scroll.
- **Settings dialog** (gear icon) with tabs for Device, Display & tuning, Audio & recording, Decoders, Calibration and Backup.
- **Tall (portrait) view** for Chromebooks and tablets held upright: the page doesn't scroll, so the browser's tab and address bar stay put.

### Bands

- **FM broadcast** (87.5–108 MHz): stereo, with RDS station names, RadioText and clock.
- **Medium wave** and **shortwave**, with one-click buttons for every international broadcast band (120 m to 11 m). Each opens the whole band on the waterfall.
- **Amateur bands:** 160 m to 10 m, **2 m** and **70 cm**.
- **PMR446:** all 16 licence-free walkie-talkie channels, stepping channel by channel.
- **Airband** (118–137 MHz) in 2 MHz sections, with **8.33 kHz channel steps** and channel names (type 118.505 and you're on the right channel). Type a 25 kHz-style name, such as 120.625, and those channels keep the familiar names you'd see on a chart.
- **Mystery:** famous unexplained HF stations, including **The Buzzer (UVB-76)**, The Pip, The Squeaky Wheel and other Russian military "channel markers".
- **Any other frequency** from 100 kHz to 1766 MHz: type it in (for example `198k`, `162.025`, `1090M`) and it opens in general coverage mode.
- Each band opens in its own mode (LSB or USB on the ham bands, FM on 2 m, 70 cm and PMR446, AM on the airband) and remembers your last frequency, tuning step and **RF gain**, so clicks always land on that band's channels. Broadcast bands remember whether you use AM or SAM.

### Modes

The same eight buttons on every band:

**AUTO · FM · AM · SAM · USB · LSB · CW · More ▾**

- **FM** is wideband on the FM broadcast band (stereo, RDS) and narrowband everywhere else (repeaters, PMR446, marine).
- **SAM** is synchronous AM, which stops fading distortion. **SAM-U and SAM-L** (under More) use just one sideband, to dodge a neighbouring station splattering into the other side: a feature usually found only on specialist receivers.
- **More ▾** holds SAM-U and SAM-L, the decoders (RTTY, PSK, NAVTEX, DSC, FT8, ACARS, weather fax, SSTV, Hellschreiber) and explicit Wide or Narrow FM.
- Modes that don't fit where you're tuned are **greyed out**, with the reason in the tooltip, so the row never changes shape.

### AUTO

![Main UI](screenshots/AUTO.png)

Switch **AUTO** on, and every time you tune somewhere new OFFgrid-SDR listens for a couple of seconds, works out what the signal is, switches to the right mode and tunes onto it. A banner at the top of the waterfall shows it listening, then what it found and how sure it is.

| Where | What AUTO recognises |
|---|---|
| **Shortwave** | CW, RTTY, PSK31, NAVTEX, DSC, weather fax, SSTV, Hellschreiber, AM and SSB (it even judges USB or LSB from the voice itself) |
| **VHF / UHF** | Narrowband FM and airband AM |
| **FM broadcast band** | Wideband FM |
| **Anywhere on HF** | **DRM** digital broadcasts, which it tells you about (they can't be decoded in a browser) |

If nothing is clear, it picks the band's usual mode: the ham band's sideband (LSB on 160, 80 and 40 m; USB on 60 m and from 30 m up), AM on broadcast bands and the airband, and narrowband FM elsewhere on VHF/UHF. On the airband, PMR446 and marine VHF it's instant, since those bands always use the same mode. AUTO helps with the signal in front of it: the mode it picks isn't remembered for that band. Choose a mode yourself to switch AUTO off.

### Decoders

- **RDS** on FM: station name, programme type, RadioText and clock, with a status line (*searching*, *no data*, or *locked · 98% good*) so you can tell "no RDS" from "signal too weak for RDS".
- **Morse (CW) decoder:** learns the sending speed by itself (4 to 60 words per minute) and ignores voice and noise. Copy the decoded text with one click.
- **CW tuning help:** click near a Morse signal to tune exactly onto it, or press **Z** to zero-beat a nearby signal onto the tone.
- **RTTY:** radioteletype from weather and news stations and radio amateurs. It finds the shift (170, 425, 450 or 850 Hz) and the speed (45.45, 50 or 75 baud) by itself.
- **NAVTEX:** maritime safety and weather messages on 518 kHz, 490 kHz and 4209.5 kHz, with each message's station, subject and number. Damaged characters are repaired from their second copy.
- **DSC (Digital Selective Calling):** ships' distress, urgency, safety and routine calls on the HF DSC frequencies, listed with who called whom (MMSI numbers). Distress calls are shown in red.
- **FT8:** decodes everyone in the passband every 15 seconds and lists them. It corrects the computer's clock from the stations it hears, so it works offline.
- **ACARS:** aircraft text messages on the airband, decoded and listed.
- **SSTV (slow-scan TV):** pictures in the Martin, Scottie and PD formats, drawn line by line as they arrive and saved as PNG. On shortwave, in USB (14.230 MHz) or LSB on 40 and 80 m (7.171 MHz), chosen by itself, and on VHF (the ISS on 145.800 MHz during its SSTV events).
- **PSK:** keyboard-to-keyboard ham text. Decodes PSK31, PSK63 and PSK125 and finds the speed by itself. Click a signal to snap onto it.
- **Hellschreiber:** the tone paints the letters on a scrolling strip and you read them by eye, just like the original 1930s machines.
- **Weather fax:** decodes HF radiofax charts line by line, lines them up automatically, and saves them as full-resolution PNG images, including automatic saving of every chart. A station list covers the German, UK and US weather fax services. Choosing FAX away from shortwave tunes to the first fax station in the list.

![Main UI](screenshots/RTTY.png)

![Main UI](screenshots/Navtex.png)

### Waterfall replay

![Main UI](screenshots/buffer.png)

Ever heard something interesting a moment too late? Switch on the **waterfall buffer** (15, 30 or 60 seconds), and OFFgrid-SDR keeps the raw radio signal in memory.

1. Press **⏸** on the waterfall to freeze it.
2. Draw a box around any signal from the last few seconds.
3. A **replay window** opens with a zoomed, detailed view of that moment, and plays it on a loop.

In the replay window you can:

- choose its **own mode, filter, SSB shift and noise filters** without touching your main settings;
- **retune** within the box by clicking, or with the arrow keys or mouse wheel;
- **decode Morse** from just that section;
- loop just part of it with **A/B**;
- **Save** it as an MP3 of what you're hearing, plus a **raw IQ file** named so that SDR#, SDR++ and other SDR software open it at the right frequency;
- hear an FM replay's **RDS** (station name and RadioText).

While paused, the **mouse wheel** scrolls back through the whole buffer, not just what fits on screen, and **⇕ Whole buffer** squeezes all of it onto the screen. The waterfall keeps running while OFFgrid-SDR is in a background tab, so when you come back, everything you missed is there to scroll back to and replay.

### Listening tools

- **Spectrum and waterfall:** click anywhere to tune, or use the mouse wheel. **Zoom** in up to 256× around the signal, handy for SSB and CW. The zoom buttons are **−**, **+** and the zoom level (click it for the full view).
- **Panorama:** sweeps the stick across a wider range than it can see at once and stitches the slices together, showing **up to 10 MHz at once**. Choose **Around me** (centred where you're tuned, 2–10 MHz wide) or the HF slices **0.5–10**, **10–20** and **20–28.8 MHz**. Click a signal to tune to it and listen, or click Panorama again to go back to where you were.
- **OVL overload indicator** beside the S-meter: amber when the band keeps touching full scale, red when the receiver is overloaded. Click it while it's lit and it lowers the RF gain step by step until the overload clears, then shows what it changed, with **Undo**.
- **RF gain per band:** each band remembers its own RF gain, so a busy band can run lower without changing the others. Automatic gain stays one setting for all bands.
- **Noise reduction**, a **noise blanker** for clicks from electric fences and car ignition, a **mains-hum filter** (50 or 60 Hz), and an **auto notch** that removes steady whistles from AM and SSB.
- **AI voice cleaner** (Off, Light, Med, Strong, Full): RNNoise, a small neural network trained on speech, clears hiss, roar and noise-type jamming from voices in AM, SAM, SSB and FM voice. Built for speech: the stronger settings quieten music, and Full silences it.
- **Smart notch:** **Whine** finds a steady whine and notches it at once. A strip shows the audio: click to drop a notch, drag it until the whine disappears, scroll to nudge it, right-click to remove it.
- **SSB filter widths** of 1.8 to 2.8 kHz (one click on the filter badge) and a **passband shift** to dodge a neighbouring station.
- **AGC speed** (Slow, Medium, Fast) for SSB and CW.
- **Squelch** based on signal-to-noise ratio: a clean on/off gate, like a real radio, that doesn't need resetting when you change antenna or gain.
- **Seek** to the next signal, variable **filter widths**, and an **S-meter**.
- **Scan** your memories: pick any of them, set the squelch, and Scan hops through them, stopping on any with a signal and carrying on 3 seconds after it ends.
- **Peak hold**, **averaging** and **new-signal alerts** on the spectrum: an alert flashes a ring where a signal appears on a frequency that has been empty for two minutes.
- **Signal info popup** (optional): hover over a signal for its frequency, level, dB over the noise, width, band plan, known frequencies (FT8, WSPR, beacons, time stations and more) and your own label or memory.
- **Frequency calibration** (Settings → Calibration): pick a time station (RWM, WWV/WWVH/BPM or CHU) and press Calibrate. OFFgrid-SDR measures the carrier to a fraction of a hertz and sets the stick's correction for you.
- **Identify** (when online): "What's on this frequency?" searches the web for the tuned frequency, "Ask AI" asks Google's AI Mode what's likely there, given the frequency, mode and time, and "Shortwave radio schedule" (below 30 MHz) shows who is scheduled on that frequency, from [shortwave.live](https://shortwave.live). Nothing is sent until you click.
- **CPU, RAM and FPS** readouts, so you can see how hard the page is working.
- **Low-power mode** for older or slower computers: half the samples and half the drawing. If the computer struggles (audio gaps or a very slow display), OFFgrid-SDR suggests it.
- Keeps playing, and the waterfall keeps running, when you switch to another browser tab.
- **Scrolling status line:** a message too long for its space scrolls instead of being cut off (with "reduce motion" on it's shortened, and the whole message shows on hover).

### Recording, labels, logbook and settings

- **Record** to MP3 or WAV.
- **50 memories**, each remembering frequency, mode and filters, including the SSB width and shift.
- **Frequency labels:** right-click the spectrum or waterfall to name a frequency ("Local repeater", "BBC WS"); labels show on the spectrum and under the frequency, and travel in settings backups.
- **Logbook:** date and time (UTC), frequency, mode, signal (average and peak S/N), station and notes. Stations you stay on for 30 s, and decoder results, are logged by themselves; the station is filled in where OFFgrid-SDR knows it (your labels, RDS, built-in lists, decoders, callsigns in CW, RTTY and PSK). Edit in place, export as CSV, or keep a CSV file up to date automatically.
- **Settings backup:** export everything to a small file and import it on another computer, ideal for preparing a kit before it's sent out.
- **Diagnostics log:** *Settings → Backup → Save diagnostics log* saves the last three minutes of band changes, retunes and stick errors, to help track down a problem. It holds no audio, memories or personal data.

### Staying running

- **USB stick recovery:** if the stick is unplugged or resets, the radio goes back to Off cleanly, and if it was on, it starts again by itself when the stick is plugged back in. You get clear messages for a lost stick, data stopping, samples going missing and the common USB errors (including the WinUSB driver on Windows).
- **Fast band switching:** a watchdog restarts the display if it stops, and resends the frequency if the stick and the display disagree, so a quick change of band never leaves the spectrum frozen.

---

## Known limitations

- **Browser support:** WebUSB is only available in Chromium-based browsers (Chrome, Edge, Opera and so on). Firefox and Safari can run demo mode only.
- **One program at a time** can use the stick.
- **Weather fax:** in June 2026 the US National Weather Service proposed closing its five HF radiofax stations towards the end of 2026. They're marked in the station list and will be removed once the closure is confirmed.
- **Morse:** the first letter of a transmission may be missed while the decoder locks on, especially at high speeds.
- **Audio delay:** the sound runs about 0.2 s behind the waterfall. Bluetooth headphones add their own delay on top.
- **Below about 500 kHz** (longwave), reception is weaker than on medium wave and shortwave.
- **Panorama** looks at one slice at a time, so short bursts elsewhere in the range can be missed. A 10 MHz sweep takes around half a second, depending on the stick, and there's no audio while it sweeps.
- **Waterfall replay** uses memory: 2 bytes per sample, about 123 MB for 30 seconds at 2.048 MS/s (246 MB for 60 seconds), which is why it's off by default. On phones and computers with 4 GB or less, the longer buffers are greyed out. A selection can't cross a retune.
- **Older and slower computers:** a typical laptop or desktop runs everything smoothly. On a budget or older one, use **Low-power mode** (in testing it removed all audio gaps on a computer four times slower than normal). A very old or very cheap machine may struggle even then.
- **AUTO** judges a couple of seconds of signal, so it can be wrong, especially on weak signals and with the SSB sideband. If something sounds wrong, choose the mode yourself.
- **AI voice cleaner:** built for speech, so it quietens or silences music (choose a lighter strength), and it can't separate two voices. It adds about 10 ms of delay.
- **Smart notch:** a long held musical note can look like a whine; right-click its line to remove that notch.
- **DRM** digital broadcasts are recognised but can't be decoded: their audio codecs aren't available in browsers and are tied up in licensing.
- **DSC calls** last only about 6 seconds, so weak or fading ones can be missed. Unreadable digits are shown as ??, never as wrong numbers.
- **Nooelec and other direct-sampling sticks:** on shortwave the signal bypasses the tuner, so the RF gain slider has no effect there (it's greyed out, with an explanation). The RTL-SDR Blog V4 isn't affected.
- **Background tabs:** if the browser's memory saver puts the tab fully to sleep, everything stops, sound included. Tell the browser to keep OFFgrid-SDR active (in Chrome: Settings → Performance → Memory Saver → "Always keep these sites active").

---

![Visit count](https://hits.sh/github.com/diddy-boy/OFFgrid-SDR.svg) visits and counting!

## Credits and licences

OFFgrid-SDR is built on the work of others:

- [**@jtarrio/webrtlsdr**](https://github.com/jtarrio/webrtlsdr) by Jacobo Tarrío: the WebUSB driver for the RTL2832U and its tuners, including the RTL-SDR Blog V4's HF upconverter. Apache License 2.0.
- [**@jtarrio/signals**](https://github.com/jtarrio/signals) by Jacobo Tarrío: the signal processing, including the FFT, filters, and the FM, AM, SAM (with its selectable sidebands), SSB and CW demodulators. Apache License 2.0.
- **Google Radio Receiver**, the original Chrome app these libraries grew from.
- [**Osmocom rtl-sdr**](https://osmocom.org/projects/rtl-sdr), for working out how to use these USB TV sticks as software-defined radios.
- [**RTL-SDR Blog**](https://www.rtl-sdr.com), for the V4 hardware and their open-source driver work.
- [**lamejs**](https://github.com/zhuker/lamejs), the JavaScript port of the LAME MP3 encoder. LGPL.
- [**RNNoise**](https://github.com/xiph/rnnoise) by Jean-Marc Valin (Mozilla and the Xiph.Org Foundation), the neural network behind the AI voice cleaner (BSD licence), in the WebAssembly build [**@jitsi/rnnoise-wasm**](https://github.com/jitsi/rnnoise-wasm) by Jitsi (Apache License 2.0).
- [**Barlow Semi Condensed**](https://github.com/jpt/barlow) and [**Share Tech Mono**](https://fonts.google.com/specimen/Share+Tech+Mono) fonts. SIL Open Font License.
- [**esbuild**](https://esbuild.github.io), which bundles everything into a single file that runs offline.
- [**Zadig**](https://zadig.akeo.ie) by Pete Batard, for installing the WinUSB driver on Windows.
- [**Shortwave.Live**](https://shortwave.live), the schedule database the Identify menu's "Shortwave radio schedule" opens.
- Frequencies for the Mystery stations come from [**Priyom**](https://priyom.org).
- PSK31 and its Varicode alphabet were created by **Peter Martinez, G3PLX**.

The full licence texts are in the `licenses` folder.

<!-- OFFgrid-SDR's own licence: add a LICENSE file (for example MIT or Apache 2.0) and name it here. -->

---

## Support

OFFgrid-SDR is free. If it's useful to you, you can [**buy me a coffee**](https://buymeacoffee.com/billynomates1974). ☕

73!

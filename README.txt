OFFgrid-SDR
===========

Offline RTL-SDR receiver for your browser
Source & downloads: github.com/diddy-boy/OFFgrid-SDR

A self-contained web receiver for RTL-SDR sticks (tested with the RTL-SDR Blog V4), built for listening to FM, medium wave and shortwave broadcasts — anywhere, with or without an internet connection. Everything — radio libraries, DSP, fonts — is inside index.html. Nothing is downloaded when it runs.

DEMONSTRATION VIDEO

HOW TO RUN

1. Put index.html anywhere (a USB pen drive works too). It's the whole receiver: one file, nothing else needed. Grab it from GitHub — open index.html in the repo and click "Download raw file".
2. Open index.html in Google Chrome, Microsoft Edge, or Opera (desktop or Android). Safari and Firefox do not support WebUSB, so the stick cannot be used there.
3. Plug in the stick, press Power on, and pick the stick in the browser's USB chooser.

No stick handy? Try the demo

Open index.html?demo for simulated stations — no hardware required.
(In Chrome: open index.html, add ?demo to the end of the address bar, press Enter.)

A "Demo stations" list appears — press Power on, then click any station:

FM

  - 98.8 — stereo + RDS (name, RadioText, clock) — try Stereo / Wide / Mono
  - 99.3 — weak stereo, RDS comes and goes — try Mono
  - 100.0 — mono talk station, RDS "News"
  - 101.1 — classical, stereo, RDS

Shortwave, 49 m band — one station per filter, all visible on the waterfall at once:

  - 5.950 — clean reference station
  - 5.985 — a whistle from a nearby carrier — click Notch
  - 6.010 — selective fading — switch AM to SAM
  - 6.070 — mains hum — Hum 50 Hz filter
  - 6.120 — electric-fence clicks — Blanker
  - 6.190 — weak and hissy — Noise reduction
  - 6.095 — a DRM digital broadcast (just hiss in AM) — switch AUTO on and it recognises it

Shortwave, 41 m band — SSB, CW and weather fax:

  - 7.210 — SSB voice, LSB (a little noisy) — try the noise filters
  - 7.240 — SSB voice, USB — switch to LSB to hear the difference; try the SSB filter widths
  - 7.275 — CW Morse beacon, 20 WPM — the CW decoder shows its message: "OFFGRID-SDR DESIGNED BY DIDDY"
  - 7.330 — AM broadcaster — compare its loudness with SSB
  - 7.395 — fast CW Morse beacon, 35 WPM — the decoder learns the speed by itself
  - 7.425 — weather fax — the decoder draws a test chart
  - 7.355 — RTTY weather teleprinter, 50 baud, 450 Hz shift
  - 7.312 — ham RTTY, 45.45 baud, 170 Hz shift — a CQ call

20 m ham band — PSK31, Hellschreiber, SSTV:

  - 14.071 — PSK31 — a CQ call and a short message
  - 14.0635 — Hellschreiber — "OFFGRID-SDR HELL DEMO 73" painted on the strip
  - 14.230 — SSTV — a colour test card in Martin M2, about once a minute

Maritime:

  - 518 kHz — NAVTEX — a gale warning, with its header
  - 8414.5 kHz — DSC — a safety call to all ships, then a distress call (sinking)

Time station:

  - 9.996 — a simulated RWM, 1.6 ppm off — try Receiver settings → Frequency calibration

Mystery

  - 4.625 — a simulated Buzzer (UVB-76), with its 25-buzzes-a-minute rhythm

ONE-TIME DRIVER SETUP

The browser must be allowed to talk to the stick directly.

Windows: Run Zadig, go to Options → List All Devices, choose "Bulk-In, Interface (Interface 0)" / RTL2838UHIDIR, select WinUSB, and click Replace Driver.

Linux: four steps, then check.

1. Stop the TV driver loading at boot:
   echo 'blacklist dvb_usb_rtl28xxu' | sudo tee /etc/modprobe.d/rtl-sdr-blacklist.conf
2. Unload it now (the blacklist alone does not unload a driver that is already running — skipping this causes "setRegBuffer failed" errors):
   sudo modprobe -r rtl2832_sdr dvb_usb_rtl28xxu
   (or simply reboot)
3. Give your user access to the stick:
   echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="0bda", ATTRS{idProduct}=="2838", MODE="0666"' | sudo tee /etc/udev/rules.d/20-rtlsdr.rules
   sudo udevadm control --reload-rules && sudo udevadm trigger
4. Unplug the stick and plug it back in.

Check: lsmod | grep -i rtl28 should print nothing.

Snap Chromium (Ubuntu): also run sudo snap connect chromium:raw-usb.

Also stop anything else using the stick (rtl_tcp, rtl_433, gqrx, SDR++).

(OFFgrid-SDR also retries USB commands that Linux reports as "stalled" — up to 5 times, waiting a little longer each time — which otherwise stopped the stick starting up on some Linux systems.)

macOS: No configuration needed

Chromebooks: No configuration needed

Only one program can use the stick at a time — close SDR#, SDR++, etc. first.

SUPPORTED STICKS

Tested by the OFFgrid-SDR author:

  - RTL-SDR Blog V4 (recommended: HF without any adapter, 4.5 V bias-tee). The V3 also works.
  - Nooelec NESDR SMArt v5 (R820T2 tuner) — Amazon UK / Amazon US

Other RTL2832U sticks with an R820T/R820T2/R828D tuner should work too.

BROWSERS

OFFgrid-SDR needs a browser with WebUSB: Google Chrome, Microsoft Edge, or another Chromium-based browser (Opera, Vivaldi, Chromium). Firefox and Safari don't support WebUSB; if you open it in one of those, the page says so, and demo mode (index.html?demo) still works there.

VERSION

The version is shown on the welcome screen and at the top of the ? help panel (e.g. "Version 1.4"), and is saved in settings backups. When reporting a problem, please quote the version.

LISTENING IN A BACKGROUND TAB

OFFgrid-SDR keeps playing when you switch to another tab or window, with a stick and in demo mode. (The waterfall pauses while the tab is hidden, and catches up when you return.)

Browsers can put tabs they think are idle to sleep to save power. While receiving, OFFgrid-SDR tells the browser it's busy, and a tab playing sound is normally left alone. If a browser still pauses it — more likely when the sound is muted or the squelch is closed — tell the browser to keep this page active:

  - Chrome: Settings → Performance → Memory Saver → "Always keep these sites active"
  - Edge: Settings → System and performance → "Never put these sites to sleep"
  - Safari: keep the tab visible (e.g. in its own window)

Laptops on battery may also slow background tabs; plugging in helps.

SUPPORTING OFFGRID-SDR

If OFFgrid-SDR is useful to you, there's a "Buy me a coffee" button in the ? help panel. It opens buymeacoffee.com/billynomates1974 in a new tab (when online).

ANTENNA

Bias-tee: Receiver settings can switch on DC power on the antenna port (4.5 V on the RTL-SDR Blog V3/V4) for an LNA or active antenna. It is off by default; a red BIAS light shows when it's on. Only use it with equipment made to be powered this way — some antennas short DC to ground, and powering them can damage the stick or the antenna. When the stick is running, switching the bias-tee reads the setting back from the stick and reports "confirmed by the stick," so you know the command took effect.

FM works with the supplied telescopic antenna. For MW and shortwave use a long wire (10 m+) or an HF antenna. The V4 switches to its HF input automatically below 28.8 MHz (shown as the HF badge).

Tested with OFFgrid-SDR:

  - AURSINC GA800 active loop shortwave antenna — Amazon UK / Amazon US
  - YouLoop passive magnetic loop antenna — Amazon UK / Amazon US

Recommended for portable kits: the YouLoop works very well on MW and shortwave, needs no power, and folds up small for storage and travel. Being a passive loop, it doesn't need the bias-tee.

Active loops such as the MLA-30+ need power. They are usually supplied with their own small USB power injector (a bias-tee box) that goes between the antenna and the stick. If you use that injector, the loop is powered by it, and the stick's bias-tee setting makes no difference (the injector also blocks the stick's DC). To power the loop from the stick instead, connect it directly and switch the bias-tee on. To check the stick's output, measure between the centre pin and the outer of its antenna socket with nothing connected: about 4.5 V with the bias-tee on, 0 V off.

QUICK GUIDE

Tuning

  - Typing a frequency: click the frequency display (or just type digits), then Enter. Any frequency the stick can reach, 100 kHz to 1766 MHz. 98.8 → FM, 909 → MW kHz, 6070 or 6.07 → opens the whole 49 m band. Add k, M or G to be explicit (e.g. 198k, 162.025M, 1090M, 1.09G). A plain number below 500 is taken as MHz (e.g. 100, 435, 118.505), 500 and above as kHz (e.g. 909, 6070) — so frequencies of 500 MHz and up need the M (1090M). Frequencies in a band go to that band; anything else opens in General coverage, with a moving window and all modes (AM, SAM, USB, LSB, CW, NFM, WFM). It picks AM below 30 MHz and NFM above, with suitable steps. Below about 500 kHz (longwave, e.g. 252k) reception is weaker but often works.
  - Mouse wheel over the waterfall or the frequency readout: wheel up tunes up one step, wheel down tunes down, in whatever mode you're in (works with Windows, Linux, Chromebook and macOS mice). On a Mac, Receiver settings → Reverse wheel direction starts ticked, because macOS "natural scrolling" reverses the wheel; it only affects tuning, so the side panel still scrolls naturally. If the wheel ever tunes the wrong way, change that setting. If the wheel does nothing, your mouse may scroll like a touchpad: choose Scroll tuning → "Mouse wheel + touchpad (normal)" (the page also tells you this if it happens).
  - Waterfall: click anywhere to tune there (click on a signal to tune to it exactly); click close to the tuning line to step one channel. The tuning line is white with a thin dark edge, so it shows over any signal. In band views you can tune anywhere you can see, including just outside the official band edges, where many broadcasters sit. Arrow keys and the mouse wheel stop at the edge of the view.
  - Step badge (top right, e.g. "±5k"): click to cycle through the tuning steps that suit the mode — AM 1/5/10 kHz (MW 1/9/10), SSB and CW 10 Hz–1 kHz, NFM 5/12.5/25 kHz, FM broadcast 50/100/200 kHz. Each band button sets its own mode and step when you click it, and remembers your choices, so clicks always land on that band's channels.
  - Seek stops on the first channel above the squelch level (dB of S/N).
  - The frequency display keeps the resolution of the tuning step: SSB (100 Hz steps) shows 4 decimals, e.g. 6.0700; CW (10 Hz steps) shows 5, e.g. 6.07000.
  - Keys: ← → step, Shift + ← → seek, M mute, + and − zoom.

Bands

  - Broadcast / Ham / Airband / Mystery (under the band buttons) switch the shortwave grid between the broadcast metre bands, the amateur bands, airband and the Mystery stations. Each band opens whole on the waterfall, and every band remembers its last frequency, mode and step.
  - Ham: the HF amateur bands 160, 80, 60, 40, 30, 20, 17, 15, 12 and 10 m start in the usual sideband (LSB below 10 MHz, USB above) with 100 Hz steps. Band edges are the widest ITU allocation — check your own licence for the exact limits where you are.
  - 2 m ham band (Ham → 2 m, 144–146 MHz): opens the whole band on the waterfall in NFM (narrowband FM, for repeaters and simplex) with 12.5 kHz steps; SSB, CW and AM too. The stick switches quickly to 2.4 MS/s on 2 m so all 2 MHz fits, and back to your normal rate when you leave. (Band plan: UK / Region 1. In the Americas 2 m continues to 148 MHz.)
  - 70 cm ham band (Ham → 70 cm, 430–440 MHz): too wide for one view, so it tunes like FM with a moving window; NFM with 12.5 kHz steps, plus SSB, CW and AM.
  - PMR446 (Ham → PMR446): the 16 licence-free channels, 446.00625 to 446.19375 MHz, in NFM, shown whole. Step, the mouse wheel and seek move channel by channel (stopping at 1 and 16); the readout and banner show the channel number, and clicking the waterfall snaps to the nearest channel. Type "pmr 3", "ch 3" or "p3" to jump to channel 3. Switch the squelch on (SQ light) to hear only when someone talks.
  - Airband (Band → SW → Airband): 118–137 MHz in 2 MHz sections (118–120, 120–122...), each shown whole on the waterfall, in AM with 8.33 kHz channel steps (25 kHz on the step badge). The display shows 8.33 kHz channel names, and typing one tunes that channel: 118.505 is the channel on 118.500 MHz, 118.510 the one on 118.5083. Most airband channels are silent between calls, so switch the squelch on (the SQ light).
  - Mystery (Band → SW → Mystery): famous unexplained HF stations, the Russian military "channel markers": The Buzzer (UVB-76, 4625 kHz), The Pip (5448 / 3756 kHz), The Squeaky Wheel (5367 / 3363.5 kHz), The Goose (4310), The Alarm (4770), The Air Horn (4930), and the D and T Markers (5292 / 4325 kHz, Morse). Each opens a narrow view on the station in the right mode. Mostly buzzes and beeps, with rare voice messages; the night frequencies work best after dark. Frequencies from priyom.org (Sept 2026) — they do change. (The famous Russian Woodpecker radar fell silent in 1989.)
  - Band banner (top left of the waterfall): the band you're in, e.g. "49 METRE BAND" (broadcast, amber) or "20 METRE HAM BAND" (amateur, blue).

Panorama

Panorama (next to the zoom buttons, green when on) sweeps the stick across a wider range than it can see at once and stitches the slices together, showing up to 10 MHz at once. Choose:

  - Around me: centred on where you're tuned, 2, 4, 6, 8 or 10 MHz wide
  - 0.5–10, 10–20 or 20–28.8 MHz: whole slices of the HF spectrum (the last stops at 28.8 MHz, so every hop stays on the stick's HF input)

A 10 MHz sweep takes around half a second, depending on the stick, and the audio pauses while it sweeps. Click a signal to tune to it and listen, or click Panorama again to go back to exactly where you were. Short bursts can be missed, since it looks at one slice at a time.

Zoom

Zoom (the half-height buttons under Seek/Step, or the + and − keys): Zoom + narrows the waterfall around the tuned signal, 2x per press, down to about 7 kHz across on a full shortwave view, with finer spectrum detail as you go (down to ~31 Hz). It stays centred on the signal (above the dial in USB, below it in LSB) and follows as you tune. Handy for SSB and CW. Default returns to the full view; the zoom shows in the waterfall title.

Modes and filters

  - Mode buttons: the same ten on every band, in two rows: AUTO · FM · AM · SAM · SAM-U / SAM-L · USB · LSB · CW · More.
    - FM: wideband on the FM broadcast band (with a Stereo / Wide / Mono line under the row), narrowband elsewhere (repeaters, PMR446, marine, business radio).
    - SAM: synchronous AM, which stops fading distortion. SAM-U / SAM-L use one sideband only, to dodge a station splattering from just below / above.
    - USB / LSB for single sideband (100 Hz steps). CW for Morse: the carrier is heard as a 600 Hz tone, 10 Hz steps, and the filter badge picks 100, 250 (default), 500 or 1000 Hz.
    - More: RTTY, PSK31, NAVTEX, DSC, weather fax, SSTV, Hellschreiber, and explicit Wide FM / Narrow FM. Once one is chosen, the More button shows its name.
    - Modes that don't fit where you're tuned are greyed, with the reason in the tooltip (e.g. AM on the FM broadcast band, or weather fax on 2 m).
  - Mode badge (top right, e.g. "AM" or "USB"): click it for a quick menu of the modes for this band — no need to scroll down to the Band section.
  - Filter width badge (top right, between REC and the mode, e.g. "6k"): click it to step through 4, 6, 8, 10 and 15 kHz on AM/SAM. The audio reaches half the width, so 6k gives audio up to 3 kHz and 8k up to 4 kHz — wider sounds brighter on a clean station, narrower keeps a crowded neighbour out. Each shortwave band remembers its own width; bands you haven't changed use 6 kHz. Hidden on FM.
  - RF gain and direct sampling: on HF, sticks without an upconverter (e.g. the Nooelec NESDR SMArt) use direct sampling (the DS light): the signal bypasses the tuner, so the RF gain slider has no effect and is greyed out. Automatic gain (AGC) still works. The RTL-SDR Blog V4 reaches HF through its upconverter, so its RF gain works on HF too.
  - SSB filter: in USB or LSB the same badge cycles 1.8, 2, 2.4 and 2.8 kHz. SSB passband shift (Audio & gain) slides the filter up or down without changing the pitch, to dodge a station just above or below. Both are remembered for each band and saved in memories.
  - Noise filters (MW/SW, in Audio & gain — green buttons when on):
    - Reduction Off/Low/Med/High — steady hiss (higher removes more, can sound watery)
    - Hum 50/60 Hz — mains hum and buzz (50 Hz Europe/Africa/Asia/Oceania, 60 Hz Americas)
    - Blanker — clicks, pops and buzz from electrical interference. It watches both the whole band and the slice around your station, so it still works on crowded medium wave, where strong local stations would otherwise hide the crackle. Try the blanker first on crackly stations.
    - Notch — finds steady whistles (a nearby carrier, a heterodyne) in AM and SSB and removes each with a very narrow notch within about a second, leaving speech untouched. It can also remove long held musical notes, so leave it off for music.

Replay (the waterfall buffer)

  - Waterfall buffer (Receiver settings): Off (the default), 15, 30 or 60 s. While on, the last few seconds of raw signal are kept in memory: 2 bytes per sample, about 123 MB for 30 s at 2.048 MS/s. The setting shows the cost for your sample rate.
  - Pause: press ⏸ at the top left of the waterfall. The waterfall, spectrum and live audio freeze. Time marks down the left show how far back each row is; the dimmed part is older than the buffer, and dashed lines mark retunes.
  - Draw a box around a signal. A popout shows it in detail, redrawn from the stored signal, with Play (loops it, with a moving playhead), Save and Cancel. Replay tunes to the signal in the box; a click in the picture, ← → or the mouse wheel retune it. A box is trimmed to what can be replayed: within the buffer, within one tuning, and within the stick's bandwidth.
  - The replay window has its own Mode, Filter, SSB shift and Noise buttons (Blanker, Notch, Reduction, Hum). They change only the replay; the main controls are left as they were.
  - In CW, the Morse in just that section is decoded and shown under the picture.
  - Click in the picture to tune the replay there. To loop just a part: press A/B, click its start, then its end (the rest is dimmed); press A/B again to clear the loop.
  - Save writes two files: the audio you're hearing (MP3) and the raw signal around the box (IQ WAV, 16-bit stereo, I and Q), named like OFFgrid-SDR_20261005_211210Z_7275200Hz_IQ.wav, so SDR#, SDR++ and others open it at the right frequency. With a loop marked, both files cover just the loop.
  - Keys: Space plays or pauses, Esc cancels.
  - ▶ Live goes back to listening, with your mode and filter settings as they were before you paused. Tuning somewhere new also ends a replay.

Frequency calibration

Receiver settings → Frequency calibration: pick a time station (RWM 4996/9996/14996 kHz, WWV/WWVH/BPM 2.5/5/10/15/20 MHz, CHU 3330/7850/14670 kHz) and press Calibrate. It tunes there, checks there's a carrier, measures it to a fraction of a hertz, sets the frequency correction (ppm), and checks the result. If it can't find or confirm a steady carrier, the correction is left as it was. Best after the stick has been running for 10–15 minutes. The correction can also be typed in steps of 0.1 ppm. Demo mode has a time station on 9.996 MHz that is deliberately 1.6 ppm off.

Squelch, scanning and status

  - Squelch works on signal-to-noise ratio, as a clean on/off gate like a real radio: the audio comes on at the setting and goes off just below it, with a little hysteresis so it doesn't chatter on a signal near the threshold. Plain noise is about 0 dB, so around 5 silences an empty channel; higher settings let through only stronger signals.
  - Scan (Memories, next to Store and Clear): press Scan and tap the memories you want scanned (they glow green), with the squelch set above Open. Scan hops through them and stops on any with a signal, showing "SCAN: HOLDING ON A SIGNAL"; 3 s after the signal ends it carries on. Anything done by hand — tuning, a band button, Store or Clear — ends the scan.
  - Status lights are quick actions: SQ turns the squelch on/off, ST switches FM between stereo and mono, SEEK stops a seek, DS and BIAS open their settings (BIAS is never switched from the light, so a slip can't put power on the antenna).
  - The status line in the readout shows a short version of each message, on one line (so nothing below it moves); hover over it to see the full message.

Decoders

  - CW tuning help: in CW, clicking near a signal on the waterfall tunes exactly onto it (the nearest carrier within ±400 Hz), so it sits on the 600 Hz tone. Z, or the Zero-beat button in the CW box, does the same for a signal within ±500 Hz. If a station pauses, it listens once more before giving up.
  - CW decoder: in CW mode, Morse is turned into text in a four-line box at the bottom left of the waterfall, with the sender's speed in WPM. Each new transmission starts on a new line (after a break of about 1.5 s, longer for slow senders). The text can be selected and copied, and the Copy button copies everything decoded since the last Clear. It learns the speed by itself (4 to 60 WPM, tested with sloppy hand-sent timing) and only prints once the signal really looks like Morse — voice, music and noise stay blank. Best on clean, steady signals such as beacons; it copes down to about 8 dB signal-to-noise. The first letter or so of a transmission may be missed while it locks on. Switch it off in Receiver settings.
  - RDS status: on wideband FM the RDS box is always shown, with a line saying "searching…", "no data (signal may be too weak for RDS)" or "locked · 85% good" (the share of RDS data received cleanly). RDS needs a stronger signal than the audio, so "no data" on a station that sounds fine usually means it's too weak for RDS.
  - RDS on FM: station name, RadioText (song/programme info), programme type, station code, traffic flags and the station's clock appear in a box at the bottom left of the waterfall once decoded (usually within a few seconds on a good signal). On weaker stations the name builds up letter by letter (missing letters show as dots), and if RDS drops out the last name and text stay on screen, dimmed, until you retune. Letters are only shown once they're certain, so noise never shows as wrong text. FM memories and recording filenames pick up the station name. RDS needs a better signal than the audio, so a weak station may play fine but show little or no RDS — that's normal. North American programme-type names (RBDS) and an on/off switch are in Receiver settings.
  - AUTO (the first mode button, on every band) is a switch: lit means on. Press it and it works out what the signal you're tuned near is, and again every time you tune somewhere new (about a second after the tuning settles). On HF: CW (a keyed carrier), RTTY (two alternating tones a standard shift apart), PSK31 (phase reversals), NAVTEX and DSC (on their frequencies), weather fax (on a listed frequency), SSTV (near the SSTV calling frequencies), Hellschreiber (a fast-keyed carrier), AM (a steady carrier with matching sidebands) or SSB (voice without a carrier, sideband judged from the voice). On VHF/UHF: narrowband FM (steady strength, 4-16 kHz wide) and airband AM. On the FM broadcast band: wideband FM. It also recognises DRM digital broadcasts (a flat 10 kHz block) and says so, without changing anything, as they can't be decoded here. A banner at the top of the waterfall shows a progress bar while it listens, then what it found and how sure it is. If nothing is clear it picks the band's usual mode: on ham bands their sideband (LSB on 160, 80 and 40 m; USB on 60 m and from 30 m up), AM on broadcast bands and the airband, narrowband FM elsewhere on VHF/UHF; and stays where you are. Fine-tuning near a signal it found doesn't set it off again. Press AUTO again, or choose a mode yourself, to switch it off. It remembers whether it was on.
  - SSTV (More; any band except FM broadcast): slow-scan TV pictures, drawn in a box bottom left as they arrive. Formats Martin M1/M2, Scottie S1/S2 and PD90/PD120, read from each picture's VIS header (nothing to set). The header shows the format and progress; ◀ ▶ browse the last six pictures; Save PNG saves one at full size, named with the date, frequency and format. Shortwave in USB (14.230, 14.233, 21.340, 28.680 MHz); VHF in FM (the ISS on 145.800 MHz during its SSTV events). Note: on 40 m and 80 m SSTV is sent in LSB, which isn't handled yet. Demo mode has a test card on 14.230 MHz, about once a minute.
  - DSC (More; below 30 MHz): Digital Selective Calling, ships' automated distress, urgency, safety and routine calls on 2187.5, 4207.5, 6312, 8414.5, 12577 and 16804.5 kHz. Each call is listed with the time, its category, who it's to (all ships or an MMSI number) and who it's from; distress calls (with their nature, e.g. sinking) in red. Symbols are sent twice, so damaged ones are repaired; anything still unreadable shows as ??, never as a wrong number. Calls last about 6 seconds, so weak ones can be missed. Copy and Clear. Demo mode: 8414.5 kHz.
  - PSK31 (More; below 30 MHz): keyboard-to-keyboard ham text (around 14.070-14.073, 7.040, 3.580 MHz). Click on a signal (or press Z) to snap onto it; the decoder then follows it within about ±25 Hz. Copy and Clear. Demo mode: 14.071 MHz.
  - Hellschreiber (More; below 30 MHz): the tone paints the letters, column by column, on a strip in a box bottom left; you read them by eye. The strip is shown twice, stacked, so there's always a complete row of letters. Click on the signal to snap onto it. Demo mode: 14.0635 MHz.
  - NAVTEX (More; below 30 MHz): maritime safety and weather messages, on 518 kHz (international, in English), 490 kHz (local languages) and 4209.5 kHz. Decoded in a box bottom left, with each message's header: station, subject (navigational warning, gale warning, weather forecast...) and number. Each character is sent twice, so a damaged one is repaired from the second copy (the box counts them). Tune near the frequency; it finds the tones itself. Copy copies all the messages received. Demo mode has a NAVTEX station on 518 kHz.
  - RTTY (More; shortwave): radioteletype, decoded to text in a box bottom left. Weather and news teleprinter stations (e.g. DWD Germany, 50 baud, 450 Hz shift) and ham RTTY (45.45 baud, 170 Hz). It finds the two tones (170, 425, 450 or 850 Hz apart) and the speed (45.45, 50 or 75 baud) itself, so tune near the signal; the box shows what it found. If the text is gibberish, press Reverse (some stations send mark and space the other way round). Copy and Clear as in the CW box. Demo mode has an RTTY weather station on 7.355 MHz.
  - Weather fax (FAX mode, shortwave): pick a station from the list in the fax box (DWD Germany, Royal Navy Northwood, and the US Coast Guard / NOAA stations), or tune a listed frequency and choose FAX. FAX mode receives in USB 1.9 kHz below the listed frequency, as the stations expect, with a 3 kHz filter. Charts go out at scheduled times: the decoder waits for each chart's start tone, lines the chart up from its phasing signal, builds it line by line (about 10 minutes per chart at 120 lines per minute) and stops at the end tone. "Start now" begins part-way through a chart; then click the chart where its left edge should be. Save PNG saves the full-resolution chart (1809 pixels wide). Demo mode has a fax station on 7.425 MHz that sends a test chart.
    - Charts aren't lost: if the next chart starts (or you retune) before you've saved one, it's kept, and a "Save previous" button appears. To save every chart without being there, tick Receiver settings → Weather fax → "Save each chart automatically": each finished chart goes to your Downloads folder as a PNG (Chrome may ask once to allow several downloads: choose Allow). If a chart's stop tone is lost in a fade, the next chart's start tone still ends it cleanly.
    - Note: in June 2026 the US National Weather Service proposed closing all five US HF fax stations (Boston, New Orleans, Point Reyes, Kodiak, Honolulu) towards the end of 2026. They're marked "proposed to close" in the list and will be removed once confirmed.

Identify (needs internet)

Identify (above the waterfall) opens a new tab with one of three lookups for the frequency you're tuned to:

  - What's on this frequency? — a web search for what is on that frequency.
  - Ask AI — asks Google's AI Mode what is usually there, given the frequency, mode and UTC time. AI answers can be wrong, so check them against the web results or the schedule.
  - Shortwave radio schedule (below 30 MHz) — who is scheduled on that frequency, from the shortwave.live schedule database (times in UTC).

Only the frequency (and, for the AI, the mode and UTC time) is sent, and only when you click. Greyed out offline.

Recording, memories and audio

  - 50 memories. Each stores frequency, mode (AM, SAM, SAM-U, SAM-L, USB, LSB, FM stereo setting), filter (including the SSB width and shift), step and the MW/SW noise filters.
  - REC (red, top right of the display) or the R key records what you hear. Press it again to stop: the file downloads straight away, named with date, time, frequency and mode. MP3 by default (about 29 MB/hour mono, 72 MB/hour FM stereo); WAV is in Receiver settings. Recording ignores the volume and mute, so it's always full level. Switching the radio off also stops and saves a recording.
  - Changing frequency, band or mode mutes the audio for 0.25 s and fades it back in, so there's no burst while the receiver settles (adjustable or off in Receiver settings). A peak limiter also protects your ears and speakers from any sudden full-scale peak. It only acts if what actually comes out of your speakers or headphones would reach full scale, so at normal volume it leaves the programme alone. It can be switched off in Receiver settings. Recordings have their own limiter, so they never clip.
  - CPU and RAM at the bottom of the display are this page's own usage. FPS shows the spectrum's frames per second and WF the waterfall's rows per second; hover over it to see the longest pause between waterfall rows in the last second (a smooth waterfall stays near its normal gap, about 50 ms at the default speed; regular pauses of 150 ms or more show as stop-start movement). Browsers don't let web pages read whole-computer figures. If CPU nears 100%, lower the sample rate.

YOUR SETTINGS AND MEMORIES

These are saved in the browser on this computer, not in this folder. To keep a copy, or move them to another computer: Receiver settings → Settings backup → Export saves everything (all 50 memories, each band's last frequency, mode and step, filters, calibration and other settings) to a small file such as OFFgrid-SDR-settings-2026-09-28.json. Keep it in this folder on the USB stick. Import on any computer restores it all (it checks the file first and asks before replacing anything).

SENDING A KIT SOMEWHERE WITHOUT INTERNET (E.G. A RESEARCH STATION)

Hardware: an antenna, the RTL-SDR stick, the cables, and a USB pen drive. On the pen drive, put:

  - index.html (the whole receiver; nothing else to install), and this README
  - a settings backup file (see above), with memories for the stations you expect
  - Zadig for any Windows computer — it installs the stick's USB driver, and there will be no way to download it on site
  - a browser installer, in case the computer there doesn't have one that supports USB: Windows 10/11 already has Microsoft Edge, which works; Linux may need an offline Chromium package; macOS needs Google Chrome (Safari can't use USB)

Nothing else is needed: no internet, no accounts, no other software. Try index.html?demo on the station computer to check everything works before connecting the stick.

CREDITS AND LICENCES

OFFgrid-SDR is built on the work of Jacobo Tarrío (EA1ITI), whose Radio Receiver and libraries power it. Press the ? button in the app for the full list of thanks.

  - MP3 encoding: LAME (lame.sourceforge.io) via lamejs by Alex Zhukov (github.com/zhuker/lamejs, @breezystack/lamejs fork), LGPL-3.0. It is kept as its own <script> block inside index.html so it can be replaced.
  - Radio libraries: @jtarrio/webrtlsdr and @jtarrio/signals by Jacobo Tarrío Barreiro, Apache License 2.0.
  - Fonts: Barlow Semi Condensed and Share Tech Mono, SIL Open Font License 1.1.
  - Shortwave schedules: the Identify menu's schedule lookup opens shortwave.live.

Full licence texts are in the licenses folder.

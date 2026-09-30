OFFgrid-SDR
===========
Offline RTL-SDR receiver for your browser.
Version 1.1 (2026-09-30)

A self-contained web receiver for RTL-SDR sticks (tested with the RTL-SDR Blog V4),
built for listening to FM, medium wave and shortwave broadcasts - anywhere, with or
without an internet connection. Everything - radio libraries, DSP, fonts - is inside
index.html. Nothing is downloaded when it runs.

HOW TO RUN
  1. Put index.html anywhere (a USB pen drive works too). It's the whole receiver: one
     file, nothing else needed. (From GitHub: open index.html and click "Download raw file".)
  2. Open index.html in Google Chrome, Microsoft Edge or Opera (desktop or Android).
     Safari and Firefox do not support WebUSB, so the stick cannot be used there.
  3. Plug in the stick, press "Power on" and pick the stick in the browser's USB chooser.

  No stick handy?  Open  index.html?demo  for simulated stations.
  (In Chrome: open index.html, then add ?demo to the end of the address and press Enter.)
  A "Demo stations" list appears: press Power on, then click any station.
    FM   98.8   stereo + RDS (name, RadioText, clock)   - try Stereo / Wide / Mono
         99.3   weak stereo, RDS comes and goes         - try Mono
         100.0  mono talk station, RDS "News"
         101.1  classical, stereo, RDS
    Shortwave, 49 m band - one station per filter, all visible on the waterfall at once:
         5.950  clean reference station
         6.010  selective fading                        - switch AM to SAM
         6.070  mains hum                               - Hum 50 Hz
         6.120  electric-fence clicks                   - Noise blanker
         6.190  weak and hissy                          - Noise reduction
    Shortwave, 41 m band - SSB and CW:
         7.210  SSB voice, LSB (a little noisy)          - try the noise filters
         7.240  SSB voice, USB                           - switch to LSB to hear the difference
         7.275  CW Morse beacon, 20 WPM                  - the CW decoder shows its message:
                                                           "OFFGRID-SDR DESIGNED BY DIDDY"
         7.330  AM broadcaster                           - compare its loudness with SSB
         7.395  fast CW Morse beacon, 35 WPM             - the decoder learns the speed by itself

ONE-TIME DRIVER SETUP (the browser must be allowed to talk to the stick)
  Windows : run Zadig (https://zadig.akeo.ie), Options > List All Devices,
            choose "Bulk-In, Interface (Interface 0)" / RTL2838UHIDIR,
            select WinUSB and click Replace Driver.
  Linux   : four steps, then check.
              1. Stop the TV driver loading at boot:
                   echo 'blacklist dvb_usb_rtl28xxu' | sudo tee /etc/modprobe.d/rtl-sdr-blacklist.conf
              2. Unload it now (the blacklist alone does NOT unload a driver that is
                 already running - skipping this causes "setRegBuffer failed" errors):
                   sudo modprobe -r rtl2832_sdr dvb_usb_rtl28xxu
                 (or simply reboot)
              3. Give your user access to the stick:
                   echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="0bda", ATTRS{idProduct}=="2838", MODE="0666"' | sudo tee /etc/udev/rules.d/20-rtlsdr.rules
                   sudo udevadm control --reload-rules && sudo udevadm trigger
              4. Unplug the stick and plug it back in.
            Check: lsmod | grep -i rtl28   should print nothing.
            Snap Chromium (Ubuntu): also run  sudo snap connect chromium:raw-usb
            Also stop anything else using the stick (rtl_tcp, rtl_433, gqrx, SDR++).
            (OFFgrid-SDR also retries USB commands that Linux reports as "stalled" - up to
            5 times, waiting a little longer each time - which otherwise stopped the stick
            starting up on some Linux systems.)
  macOS   : usually nothing to do.
  Only one program can use the stick at a time - close SDR#, SDR++, etc. first.

SUPPORTED STICKS
  Tested by the OFFgrid-SDR author:
    - RTL-SDR Blog V4 (recommended: HF without any adapter, 4.5 V bias-tee). The V3 also works.
    - Nooelec NESDR SMArt v5 (R820T2 tuner)
        Amazon UK: https://www.amazon.co.uk/Nooelec-NESDR-SMArt-SDR-R820T2-Based/dp/B01HA642SW/
        Amazon US: https://www.amazon.com/Nooelec-RTL-SDR-SDR-100kHz-1-75GHz-Enclosure/dp/B01HA642SW/
  Other RTL2832U sticks with an R820T/R820T2/R828D tuner should work too.

BROWSERS
  OFFgrid-SDR needs a browser with WebUSB: Google Chrome, Microsoft Edge, or another
  Chromium-based browser (Opera, Vivaldi, Chromium). Firefox and Safari don't support
  WebUSB; if you open it in one of those, the page says so, and demo mode
  (index.html?demo) still works there.

VERSION
  The version is shown on the welcome screen and at the top of the ? help panel
  (e.g. "Version 1.1"), and is saved in settings backups. When reporting a problem,
  please quote the version.

LISTENING IN A BACKGROUND TAB
  OFFgrid-SDR keeps playing when you switch to another tab or window, with a stick and in
  demo mode. (The waterfall pauses while the tab is hidden, and catches up when you return.)
  Browsers can put tabs they think are idle to sleep to save power. While receiving,
  OFFgrid-SDR tells the browser it's busy, and a tab playing sound is normally left alone.
  If a browser still pauses it - more likely when the sound is muted or the squelch is
  closed - tell the browser to keep this page active:
    - Chrome:  Settings > Performance > Memory Saver > "Always keep these sites active"
    - Edge:    Settings > System and performance > "Never put these sites to sleep"
    - Safari:  keep the tab visible (e.g. in its own window)
  Laptops on battery may also slow background tabs; plugging in helps.

SUPPORTING OFFGRID-SDR
  If OFFgrid-SDR is useful to you, there's a "Buy me a coffee" button in the ? help panel.
  It opens https://buymeacoffee.com/billynomates1974 in a new tab (when online).

ANTENNA
  Bias-tee: Receiver settings can switch on DC power on the antenna port (4.5 V on the
  RTL-SDR Blog V3/V4) for an LNA or active antenna. It is off by default; a red BIAS light
  shows when it's on. Only use it with equipment made to be powered this way - some
  antennas short DC to ground, and powering them can damage the stick or the antenna.
  When the stick is running, switching the bias-tee reads the setting back from the
  stick and reports "confirmed by the stick", so you know the command took effect.

  FM works with the supplied telescopic antenna. For MW and shortwave use a long
  wire (10 m+) or an HF antenna. The V4 switches to its HF input automatically
  below 28.8 MHz (shown as the HF badge).

  Tested with OFFgrid-SDR:
    - AURSINC GA800 active loop shortwave antenna
        Amazon UK: https://www.amazon.co.uk/GA800-AURSINC-Shortwave-10KHz-159MHz-Receiving/dp/B0DLW9MZS1
        Amazon US: https://www.amazon.com/Shortwave-Antenna-10KHz-159MHz-Portable-Receiving/dp/B0CFPWGCVJ/?th=1
    - YouLoop passive magnetic loop antenna
        Amazon UK: https://www.amazon.co.uk/Giilayky-YouLoop-Magnetic-Antenna-Portable-As-shown/dp/B0DDB894LR
        Amazon US: https://www.amazon.com/GOOZEEZOO-Portable-Broadband-10KHz-30MHz-Receiving/dp/B0BR3SJLTG
  Recommended for portable kits: the YouLoop works very well on MW and shortwave, needs
  no power, and folds up small for storage and travel. Being a passive loop, it doesn't
  need the bias-tee.

  Active loops such as the MLA-30+ need power. They are usually supplied with their own
  small USB power injector (a bias-tee box) that goes between the antenna and the stick.
  If you use that injector, the loop is powered by it, and the stick's bias-tee setting
  makes no difference (the injector also blocks the stick's DC). To power the loop from
  the stick instead, connect it directly and switch the bias-tee on. To check the stick's
  output, measure between the centre pin and the outer of its antenna socket with nothing
  connected: about 4.5 V with the bias-tee on, 0 V off.

QUICK GUIDE
  - Click the frequency display (or just type digits) to enter a frequency, then Enter.
    98.8 -> FM, 909 -> MW kHz, 6070 or 6.07 -> opens the whole 49 m band.
  - Mouse wheel over the waterfall or the frequency readout: wheel up tunes up one step,
    wheel down tunes down, in whatever mode you're in (works with Windows, Linux,
    Chromebook and macOS mice). On a Mac, Receiver settings > Reverse wheel direction starts
    ticked, because macOS "natural scrolling" reverses the wheel; it only affects tuning,
    so the side panel still scrolls naturally. If the wheel ever tunes the wrong way, change
    that setting. If
    the wheel does nothing, your mouse may scroll like a touchpad: choose Scroll tuning >
    "Mouse wheel + touchpad (normal)" (the page also tells you this if it happens).
  - Waterfall: click anywhere to tune there (click on a signal to tune to it exactly);
    click close to the tuning line to step one channel. In band views you can tune
    anywhere you can see, including just outside the official band edges, where many
    broadcasters sit. Arrow keys and the mouse wheel stop at the edge of the view.
  - Seek stops on the first channel above the squelch level (dB of S/N).
  - 50 memories. Each stores frequency, mode (AM, SAM, SAM-U, SAM-L, USB, LSB, FM
    stereo setting), filter, step and the MW/SW noise filters.
  - Broadcast / Ham (under the band buttons) switches the shortwave grid between the
    broadcast metre bands and the HF amateur bands: 160, 80, 60, 40, 30, 20, 17, 15, 12
    and 10 m. Each band opens whole on the waterfall. Ham bands start in the usual
    sideband (LSB below 10 MHz, USB above) with 100 Hz steps, and every band remembers its
    last frequency and mode. Band edges are the widest ITU allocation - check your own
    licence for the exact limits where you are.
  - CW decoder: in CW mode, Morse is turned into text in a four-line box at the bottom left
    of the waterfall, with the sender's speed in WPM. Each new transmission starts on a new
    line (after a break of about 1.5 s, longer for slow senders). The text can be selected
    and copied, and the Copy button copies everything decoded since the last Clear. It learns the speed by itself (tested from
    12 to 40 WPM, and with sloppy hand-sent timing) and only prints once the signal really
    looks like Morse - voice, music and noise stay blank. Best on clean, steady signals
    such as beacons; it copes down to about 8 dB signal-to-noise. The first letter or so of
    a transmission may be missed while it locks on. Switch it off in Receiver settings.
  - RDS on FM: station name, RadioText (song/programme info), programme type, station
    code, traffic flags and the station's clock appear in a box at the bottom left of the
    waterfall once decoded (usually within a few seconds on a good signal). On weaker
    stations the name builds up letter by letter (missing letters show as dots), and if
    RDS drops out the last name and text stay on screen, dimmed, until you retune. Letters
    are only shown once they're certain, so noise never shows as wrong text. FM memories
    and recording filenames pick up the station name. RDS needs a better signal than the
    audio, so a weak station may play fine but show little or no RDS - that's normal. North American programme-type names (RBDS) and an
    on/off switch are in Receiver settings.
  - Identify (above the waterfall, needs internet): opens the Signal Identification Wiki
    (sigidwiki.com) in a new tab - either its list of known signals for the band you're
    tuned to (HF, MF, VHF...) with frequency ranges, modes, audio and waterfall samples,
    or its search form, with the tuned frequency copied to the clipboard for pasting.
    Compare its pictures and recordings with what you see and hear. Greyed out offline.
  - Step badge (top right, e.g. "±5k"): click to cycle through the tuning steps that suit
    the mode - AM 1/5/10 kHz (MW 1/9/10), SSB and CW 10 Hz-1 kHz, NFM 5/12.5/25 kHz,
    FM broadcast 50/100/200 kHz.
  - Squelch works on signal-to-noise ratio, as a soft gate: full volume at the setting and
    above, fading to silence 5 dB below it, with smooth opening and closing and a short hold
    so pauses in speech don't chop the signal. Plain noise is about 0 dB, so around 5
    silences an empty channel; higher settings let through only stronger signals.
  - Status lights are quick actions: SQ turns the squelch on/off, ST switches FM between
    stereo and mono, SEEK stops a seek, DS and BIAS open their settings (BIAS is never
    switched from the light, so a slip can't put power on the antenna).
  - Band banner (top left of the waterfall): the band you're in, e.g. "49 METRE BAND"
    (broadcast, amber) or "20 METRE HAM BAND" (amateur, blue).
  - 2 m ham band (Ham > 2 m, 144-146 MHz): opens the whole band on the waterfall in NFM
    (narrowband FM, for repeaters and simplex) with 12.5 kHz steps; SSB, CW and AM too.
    The stick runs at 2.4 MS/s on 2 m so all 2 MHz fits, and returns to your normal rate
    when you leave. (Band plan: UK / Region 1. In the Americas 2 m continues to 148 MHz.)
  - Airband (Band > SW > Airband): 118-137 MHz in 2 MHz sections (118-120, 120-122 ...),
    each shown whole on the waterfall, in AM with 8.33 kHz channel steps (25 kHz on the step
    badge). The display shows 8.33 kHz channel names, and typing one tunes that channel:
    118.505 is the channel on 118.500 MHz, 118.510 the one on 118.5083. Most airband
    channels are silent between calls, so switch the squelch on (the SQ light).
  - PMR446 (Band > SW > Utility > PMR446): the 16 licence-free channels, 446.00625 to
    446.19375 MHz, in NFM, shown whole. Step, the mouse wheel and seek move channel by
    channel (stopping at 1 and 16); the readout and banner show the channel number, and
    clicking the waterfall snaps to the nearest channel. Type "pmr 3", "ch 3" or "p3" to
    jump to channel 3. Switch the squelch on (SQ light) to hear only when someone talks.
  - 70 cm ham band (Ham > 70 cm, 430-440 MHz): too wide for one view, so it tunes like FM
    with a moving window; NFM with 12.5 kHz steps, plus SSB, CW and AM.
  - Mystery (Band > SW > Mystery): famous unexplained HF stations, the Russian military
    "channel markers": The Buzzer (UVB-76, 4625 kHz), The Pip (5448 / 3756 kHz), The
    Squeaky Wheel (5367 / 3363.5 kHz), The Goose (4310), The Alarm (4770), The Air Horn
    (4930), and the D and T Markers (5292 / 4325 kHz, Morse). Each opens a narrow view on
    the station in the right mode. Mostly buzzes and beeps, with rare voice messages; the
    night frequencies work best after dark. Frequencies from priyom.org (Sept 2026) - they
    do change. (The famous Russian Woodpecker radar fell silent in 1989.) Demo mode has a
    simulated Buzzer on 4.625 MHz.
  - PMR446 (Ham > PMR446): the licence-free walkie-talkie band used in the UK and Europe,
    16 NFM channels from 446.00625 to 446.19375 MHz, all shown at once. Step, the mouse
    wheel and Seek move channel by channel; the readout and banner show the channel number.
  - Weather fax (FAX mode, shortwave): pick a station from the list in the fax box (DWD
    Germany, Royal Navy Northwood, and the US Coast Guard / NOAA stations), or tune a listed
    frequency and choose FAX. FAX mode receives in USB 1.9 kHz below the listed frequency,
    as the stations expect, with a 3 kHz filter. Charts go out at scheduled times: the
    decoder waits for each chart's start tone, lines the chart up from its phasing signal,
    builds it line by line (about 10 minutes per chart at 120 lines per minute) and stops
    at the end tone. "Start now" begins part-way through a chart; then click the chart
    where its left edge should be. Save PNG saves the full-resolution chart (1809 pixels
    wide). Demo mode has a fax station on 7.425 MHz that sends a test chart.
    Charts aren't lost: if the next chart starts (or you retune) before you've saved one,
    it's kept, and a "Save previous" button appears. To save every chart without being
    there, tick Receiver settings > Weather fax > "Save each chart automatically": each
    finished chart goes to your Downloads folder as a PNG (Chrome may ask once to allow
    several downloads: choose Allow). If a chart's stop tone is lost in a fade, the next
    chart's start tone still ends it cleanly.
    Note: in June 2026 the US National Weather Service proposed closing all five US HF fax
    stations (Boston, New Orleans, Point Reyes, Kodiak, Honolulu) towards the end of 2026.
    They're marked "proposed to close" in the list and will be removed once confirmed.
  - Typing a frequency: any frequency the stick can reach, 100 kHz to 1766 MHz. Add k, M or
    G to be explicit (e.g. 198k, 162.025M, 1090M, 1.09G). A plain number below 500 is taken
    as MHz (e.g. 100, 435, 118.505), 500 and above as kHz (e.g. 909, 6070) - so frequencies
    of 500 MHz and up need the M (1090M). Frequencies in a band go to that band as before;
    anything else opens in General coverage, with a moving window and all modes (AM, SAM,
    USB, LSB, CW, NFM, WFM). It picks AM below 30 MHz and NFM above, with suitable steps
    (9 kHz below 1.8 MHz, 5 kHz on HF, 12.5 kHz on VHF/UHF); change them as usual. Below
    about 500 kHz (longwave, e.g. 198k) reception is weaker but often works.
  - Zoom (the half-height buttons under Seek/Step, or the + and - keys): Zoom + narrows the
    waterfall around the tuned signal, 2x per press, down to about 7 kHz across on a full
    shortwave view, with finer spectrum detail as you go (down to ~31 Hz). It stays centred
    on the signal (above the dial in USB, below it in LSB) and follows as you tune. Handy
    for SSB and CW. Default returns to the full view; the zoom shows in the waterfall title.
  - The status line in the readout shows a short version of each message, on one line (so
    nothing below it moves); hover over it to see the full message.
  - Mode badge (top right, e.g. "AM" or "USB"): click it for a quick menu of the modes for
    this band (AM, SAM, SAM-U, SAM-L, USB, LSB, CW; or Stereo, Wide, Mono on FM) - no need
    to scroll down to the Band section.
  - The frequency display keeps the resolution of the tuning step: SSB (100 Hz steps) shows
    4 decimals, e.g. 6.0700; CW (10 Hz steps) shows 5, e.g. 6.07000.
  - Filter width badge (top right, between REC and the mode, e.g. "6k"): click it to step
    through 4, 6, 8, 10 and 15 kHz on AM/SAM. The audio reaches half the width, so 6k gives
    audio up to 3 kHz and 8k up to 4 kHz - wider sounds brighter on a clean station,
    narrower keeps a crowded neighbour out. Each shortwave band (broadcast and ham)
    remembers its own width; bands you haven't changed use 6 kHz. Memories store it too.
    SSB shows a fixed 2k. Hidden on FM.
  - Changing frequency, band or mode mutes the audio for 0.25 s and fades it back in, so
    there's no burst while the receiver settles (adjustable or off in Receiver settings).
    A peak limiter also protects your ears and speakers from any sudden full-scale peak.
    It only acts if what actually comes out of your speakers or headphones would reach
    full scale, so at normal volume it leaves the programme alone. It can be switched
    off in Receiver settings. Recordings have their own limiter, so they never clip.
  - REC (red, top right of the display) or the R key records what you hear. Press it
    again to stop: the file downloads straight away, named with date, time, frequency
    and mode. MP3 by default (about 29 MB/hour mono, 72 MB/hour FM stereo); WAV is in
    Receiver settings. Recording ignores the volume and mute, so it's always full level.
    Switching the radio off also stops and saves a recording.
  - Noise filters (MW/SW, in Audio & gain):
      Reduction Off/Low/Med/High - steady hiss (higher removes more, can sound watery)
      Hum 50/60 Hz - mains hum and buzz (50 Hz Europe/Africa/Asia/Oceania, 60 Hz Americas)
      Noise blanker - clicks, pops and buzz from electrical interference. It watches both
        the whole band and the slice around your station, so it still works on crowded
        medium wave, where strong local stations would otherwise hide the crackle.
    Try the blanker first on crackly stations.
  - CPU and RAM at the bottom of the display are this page's own usage. Browsers don't
    let web pages read whole-computer figures. If CPU nears 100%, lower the sample rate.
  - Mode buttons under FM / MW / SW:
      FM: Stereo / Wide / Mono
      MW and SW: AM, SAM (synchronous AM - stops fading distortion), SAM-U / SAM-L (one
      sideband only - dodges a station splattering from just below / above), and
      USB / LSB for single sideband (2 kHz audio, tuning switches to 100 Hz steps), and
      CW for Morse code: the carrier is heard as a 600 Hz tone, tuning switches to 10 Hz
      steps, and the bandwidth badge picks a 100, 250 (default), 500 or 1000 Hz filter.
  - Keys: <- -> step, Shift + <- -> seek, M mute.

YOUR SETTINGS AND MEMORIES
  These are saved in the browser on this computer, not in this folder. To keep a copy,
  or move them to another computer: Receiver settings > Settings backup > Export saves
  everything (all 50 memories, each band's last frequency and mode, filters, calibration
  and other settings) to a small file such as OFFgrid-SDR-settings-2026-09-28.json.
  Keep it in this folder on the USB stick. Import on any computer restores it all (it
  checks the file first and asks before replacing anything).

SENDING A KIT SOMEWHERE WITHOUT INTERNET (e.g. a research station)
  Hardware: an antenna, the RTL-SDR stick, the cables, and a USB pen drive. On the pen
  drive, put:
    - index.html (the whole receiver; nothing else to install), and this README.txt
    - a settings backup file (see above), with memories for the stations you expect
    - Zadig (https://zadig.akeo.ie) for any Windows computer - it installs the stick's
      USB driver, and there will be no way to download it on site
    - a browser installer, in case the computer there doesn't have one that supports
      USB: Windows 10/11 already has Microsoft Edge, which works; Linux may need an
      offline Chromium package; macOS needs Google Chrome (Safari can't use USB)
  Nothing else is needed: no internet, no accounts, no other software. Try
  index.html?demo on the station computer to check everything works before connecting
  the stick.

CREDITS AND LICENCES
  OFFgrid-SDR is built on the work of Jacobo Tarrio (EA1ITI), whose Radio Receiver
  (https://radio.ea1iti.es) and libraries power it. Press the ? button in the app
  for the full list of thanks.
  MP3 encoding: LAME (https://lame.sourceforge.io) via lamejs by Alex Zhukov
  (https://github.com/zhuker/lamejs, @breezystack/lamejs fork), LGPL-3.0. It is kept as
  its own <script> block inside index.html so it can be replaced.
  Radio libraries: @jtarrio/webrtlsdr and @jtarrio/signals by Jacobo Tarrio Barreiro,
  Apache License 2.0. Fonts: Barlow Semi Condensed and Share Tech Mono, SIL Open Font
  License 1.1. Full texts in the licenses folder.

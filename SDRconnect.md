# Using an SDRplay RSP with OFFgrid-SDR (through SDRconnect)

OFFgrid-SDR works with an **RTL-SDR stick** by default. If you own an **SDRplay RSP**, it can use that instead, through SDRplay's own **SDRconnect** software. This guide covers setting up SDRconnect, starting it automatically, and configuring OFFgrid-SDR.

## How it works

OFFgrid-SDR doesn't drive the RSP itself. **SDRconnect** runs on the computer the RSP is plugged into (this one, or another on your network, such as a Raspberry Pi in the shed), and OFFgrid-SDR connects to SDRconnect's **WebSocket API** on **port 5454**. No USB is involved on OFFgrid-SDR's side, so it works in any modern browser, including on an iPad.

**SDRconnect must already be running** on the RSP's computer before you press **Power on** in OFFgrid-SDR. If it isn't, OFFgrid-SDR can't connect, and will keep retrying every few seconds. That's why it's worth starting SDRconnect automatically (see [Starting SDRconnect automatically](#starting-sdrconnect-automatically)).

## Requirements

- **SDRconnect 1.0.6 or later** (the WebSocket API arrived in 1.0.6). Tested with **1.0.9 and 1.0.10**.
- Note that SDRconnect **1.0.10** still reports its WebSocket API as **version 1.0.3**: the API's version number is separate from the program's.
- SDRconnect is 64-bit only: Windows 10 or 11, macOS (Intel 10.15 or later, Apple Silicon 13 or later), 64-bit Linux, and **64-bit Raspberry Pi OS** on a Pi 4B or better. See [SDRplay's SDRconnect page](https://www.sdrplay.com/sdrconnect) for the downloads.
- A network fast enough for the stream: about **8 MB/s** (64 Mbit/s), so a wired connection or good Wi-Fi.

## Installing SDRconnect

**Linux, including a Raspberry Pi** (no screen needed). Install with SDRplay's script. It installs SDRconnect into **`/opt/SDRconnect`**, along with the SDRplay API service the RSP needs:

```
sudo apt update && sudo apt install -y curl
/bin/bash -c "$(curl -fsSL https://www.sdrplay.com/software/install.sh)"
```

> **On a Raspberry Pi with 1 GB of memory, use Raspberry Pi OS *Lite* (no desktop).** With the desktop, the Pi runs short of memory and starts swapping, and SDRconnect then drops samples, which shows up as DAB cutting out. Without the desktop, it runs smoothly.

**Windows and macOS.** Install SDRconnect with SDRplay's installer, from the SDRconnect page.

## Running SDRconnect's server

You can use either of SDRconnect's two programs:

- **The headless server, `SDRconnect_headless`** (no window): best for a computer without a screen, such as a Raspberry Pi. Its WebSocket API is on port 5454 automatically. On Linux:
  ```
  /opt/SDRconnect/SDRconnect_headless
  ```
  On Windows and macOS, it's in SDRconnect's installation folder. (`--websocket_port=<port>` changes the port, if you need to.)
- **The ordinary SDRconnect program** (with its window): switch its **WebSocket server on in its Settings** (it's off by default), and leave SDRconnect running.

Don't use `SDRconnect --server`: that's SDRconnect's own server for its own client (port 50000), not the WebSocket API OFFgrid-SDR uses.

## Starting SDRconnect automatically

So that SDRconnect is always ready when you open OFFgrid-SDR, run the headless server as a **service** that starts at boot.

### Example: a Raspberry Pi (or any Linux with systemd)

Create the service file:

```
sudo nano /etc/systemd/system/sdrconnect.service
```

with this inside (replace `pi` with your own user name):

```
[Unit]
Description=SDRconnect headless (WebSocket API on port 5454)
After=network-online.target
Wants=network-online.target

[Service]
User=pi
ExecStart=/opt/SDRconnect/SDRconnect_headless
Restart=on-failure
RestartSec=5

[Install]
WantedBy=multi-user.target
```

Then switch it on, and check it's running:

```
sudo systemctl daemon-reload
sudo systemctl enable --now sdrconnect
systemctl status sdrconnect
```

Useful afterwards:

| Command | What it does |
|---|---|
| `journalctl -u sdrconnect -f` | shows SDRconnect's messages live |
| `sudo systemctl restart sdrconnect` | restarts it (for example after updating SDRconnect) |
| `sudo systemctl stop sdrconnect` | stops it (for example to use the RSP in another program) |
| `sudo systemctl disable sdrconnect` | stops it starting at boot |

### Other systems

The setup is the same on Windows and macOS: install SDRconnect, then make **`SDRconnect_headless`** start at boot (or at login) with your system's own tool for that, for example **Task Scheduler** on Windows (a task that runs at start-up), or a **launchd** item on macOS. Point it at `SDRconnect_headless` in SDRconnect's installation folder.

## Firewall

On the RSP's computer, allow incoming connections on **port 5454** (TCP). On Linux with `ufw`: `sudo ufw allow 5454/tcp`.

## Configuring OFFgrid-SDR

1. Open **Settings → Device** (or the first-run screen) and choose **SDRconnect**.
2. Enter the RSP computer's **name or IP address** (`127.0.0.1` if SDRconnect runs on the same computer as OFFgrid-SDR). A fixed IP address is the most reliable; names like `shack-pc` (Windows networks) or `shack-pc.local` (most others) usually work too. The last five addresses that worked are offered.
3. Press **Test**: it should name your RSP and the API version.
4. Press **Power on**.

The **NET** badge before the band name shows the connection: **green** when it's keeping up, **amber** when it's connecting or falling behind, **red** when it's lost (OFFgrid-SDR reconnects by itself). Hover over it, or tap it, for the network speed against what's needed, the buffer, the RSP and its settings.

## The RSP models

- **RSP1A and RSP1B:** the simplest: one antenna, nothing else to set up.
- **RSPdx:** its antennas **switch automatically by frequency**. By default, **Antenna A** is used from **30 MHz** up, **Antenna B** below, and **Antenna C** not at all. Each can be changed in **Settings → Device** (the antenna settings appear once the RSP is running), including the **crossover frequency** and **custom ranges** (for example, a medium-wave loop on C from 0.1 to 2 MHz).
- **RSPduo:** OFFgrid-SDR uses **one tuner**.

## Limits worth knowing

- **No bias-tee control:** SDRconnect's WebSocket API has no bias-tee setting, and its headless server no bias-tee option. For a powered antenna (an active loop such as the MLA-30+), use the **antenna's own bias-tee injector**, or SDRconnect's ordinary program with the bias-tee switched on.
- **Panorama** isn't available through SDRconnect: it sweeps the radio faster than a network connection can follow.

## Technical note: how OFFgrid-SDR handles an RSP's gain

An RSP has **two** gain stages:

1. **The LNA state** (the front-end, RF gain): switched attenuation right at the input. **OFFgrid-SDR's RF gain slider sets this.** SDRplay counts it downwards (state 0 is the *most* gain), and the number of states depends on the model and the band, so OFFgrid-SDR reads the range from SDRconnect and maps the slider onto it, with higher on the slider meaning more gain, as usual.
2. **The IF gain:** a second stage that keeps the level right for the RSP's converter. This is left to **SDRconnect's IF AGC**; SDRconnect's API doesn't let OFFgrid-SDR set it.

**Higher isn't always better.** Near full front-end gain, strong signals overload the RSP, raising the noise floor into a mush around them. So the **first 90%** of the slider covers the comfortable part of the range, and only the **last tenth** goes on to full gain. **Auto** picks the **middle LNA state** for each band, the RSP's usual sweet spot. If the floor rises around strong signals, lower the slider until it clears: the **NET** panel shows the LNA state in use.

When you change band, OFFgrid-SDR waits for the new band's gain range from SDRconnect and sets the gain for it before carrying on, so you may see a brief pause rather than a jump.

## Troubleshooting

- **Test says it can't connect:** check SDRconnect is running (`systemctl status sdrconnect` on Linux), the address, and the firewall (port 5454). If SDRconnect is the ordinary program, check its WebSocket server is switched on.
- **It connects, then disconnects at once:** you may be running `SDRconnect --server` (port 50000) rather than the headless server or the WebSocket API on port 5454.
- **The display stutters, and the NET badge turns amber:** the network isn't delivering the 8 MB/s needed. Hover over NET for the figures; a wired connection or 5 GHz Wi-Fi helps.
- **DAB cuts out, but FM and shortwave are fine:** DAB is the most sensitive to samples going missing on the RSP's computer. On a Raspberry Pi, check it isn't swapping (`free -h`), use Pi OS Lite on a 1 GB Pi, and check `vcgencmd get_throttled` shows `throttled=0x0` (anything else means low voltage or overheating).
- **When reporting a problem,** save a **diagnostics log** (Settings → Backup → Save diagnostics log): it records the connection, the RSP's settings and the network figures.

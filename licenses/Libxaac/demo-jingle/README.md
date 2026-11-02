# The demo's xHE-AAC jingle

The demo station "OFFgrid xHE" (11.750 MHz in demo mode) plays OFFgrid-SDR's original jingle in xHE-AAC: 150 frames,
12.8 s, mono, 24 kHz, 2:1 SBR, about 14 kbit/s, sent three times over in a 38.4 s loop. It was encoded once, with
libxaac's encoder from the same commit, changed for DRM (`encoder-for-demo-jingle.diff`, against `encoder/` at
commit 2fbadd5; the encoder is not part of OFFgrid-SDR):

- DRM's low bit rates allowed (that release forced any USAC rate but 64 or 96 kbit/s to 96);
- no audio pre-roll or fill element, and no pre-roll bit in the frames (DRM's configuration describes one audio
  element only; the release's default random-access setting, -1, switched pre-roll on);
- every frame independent, as DRM broadcasters send them.

Command: `xaacenc -ifile:jingle.wav -ofile:jingle.es -aot:42 -ccfl_idx:3 -br:15000 -nf:1`, with the jingle padded to
153 frames of 2048 samples; the first frame (the encoder's start-up) is dropped and the next 150 kept.

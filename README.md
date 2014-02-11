libstand
---

libstand is a framework for vocal synthesis.

modules
---
- core/ - libstand core classes
 - corpus/
   - Phoneme and repository classes for corpus
 - dsp/
   - Basic DSP classes for WORLD implementation
 - synthesis/
   - A framework for Singing synthesis
 - synthesis/world/
   - An implementation for synthesis with WORLD
 - utau/
   - Basic value classes for UTAU voicebank
 - util/
   - Basic utility class for STAND
- test/ - libstand unit tests

License
---

modified BSD

Requirement
---

Qt 5.2.0
MinGW 4.8+
Google mock 1.7.0

Libraries
---

libstand uses libraries below
 - WORLD: voice analysis and synthesis system.
   - http://www.slp.is.ritsumei.ac.jp/~morise/world/
 - FFT SG: FFT library by Ooura
   - http://www.kurims.kyoto-u.ac.jp/~ooura/index.html

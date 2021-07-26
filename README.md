![](Images/Logo.png)

<p align="center"> - The open head tracker - </p>

## What is this?

### This is a Linux port of AITrack
AITrack is a 6-Degree of Freedom headtracker designed to work alongside [Opentrack](https://github.com/opentrack/opentrack) for its use in simulators/games. 

AITrack uses its own tracking pipeline (based on neural networks) to estimate the user's head position with respect to the webcam and then, streams it to Opentrack, which in turn, transmits it to your games.

### Main features

* Hardware (IR LEDs, specific hardware...) free headtracking solution.
* Good performance under poor light conditions.
* Good detection with partial face occlusion (using glasses).
* Reasonable low CPU percentage consumption.
* Remote-running capability. You can use a second PC (for example, a laptop)to stream the tracking data to your main machine.


### Original project [here](https://github.com/AIRLegend/aitrack)

## Installing and running

1. If you're using an Arch derivative, you can install this port via its [PKGBUILD](https://github.com/mdk97/aitrack-linux-pkgbuild)
2. Install the `opentrack` package from the AUR.
3. Run Opentrack and make sure to select Input = **UDP over network**, then, click "Start". Opentrack then will be listening for the data AITrack will send.
5. Run `aitrack` and click "Start tracking". 
6. Look around!

### Video showcasing how the software works (On Windows):
[<img src="http://i3.ytimg.com/vi/1B2dlzTlpus/hqdefault.jpg" width="50%">](https://www.youtube.com/watch?v=1B2dlzTlpus&feature=youtu.be)


### But... I don't have a webcam :(

No problem. This program supports [Droid Cam](https://www.dev47apps.com/), so you're able to use your smartphone as a camera.

### My webcam is too old

Don't worry. AITrack supports low resolutions pretty well. Anything achieving at least 30fps and 480p will do the job fine.

---

**IMPORTANT:**
In case you want to know more, please, head to the [project's wiki](https://github.com/AIRLegend/aitrack/wiki) to find guides about usage. If you can't find there what you're looking for, feel free to post your question on the [issues page](https://github.com/AIRLegend/aitracker/issues).

## Showoff videos
Check out this [wiki page](https://github.com/AIRLegend/aitrack/wiki/Videos) to see how it behaves.

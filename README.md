![](Images/Logo.png)

<p align="center"> - The open head tracker - </p>

## What is this?

### This is a Linux port of AITrack

AITrack is a 6-Degree of Freedom headtracker designed to work alongside [Opentrack](https://github.com/opentrack/opentrack) for its use in simulators/games.

AITrack uses its own tracking pipeline (based on neural networks) to estimate the user's head position with respect to the webcam and then, streams it to Opentrack, which in turn, transmits it to your games.

### Main features

- Hardware (IR LEDs, specific hardware...) free headtracking solution.
- Good performance under poor light conditions.
- Good detection with partial face occlusion (using glasses).
- Reasonable low CPU percentage consumption.
- Remote-running capability. You can use a second PC (for example, a laptop)to stream the tracking data to your main machine.

### Original project [here](https://github.com/AIRLegend/aitrack)

## Dependencies

Here are listed the build and runtime dependencies and their repective versions:

### Dependencies used originally on Artix:

- `qt5-base 5.15.2+kde+r210-1`
- `qt5-x11extras 5.15.2-1`
- `opencv 4.5.3-2`
- `spdlog 1.9.0-1`
- `fmt 8.0.1-1`
- `openmp 12.0.1-1`
- `vtk 8.2.0-20`

#### Full command:

`sudo pacman -S qt5-base qt5-x11extras opencv spdlog fmt openmp vtk`

### List of Ubuntu packages that could potentially resolve them:

- `qtbase5-dev`
- `qtbase5-dev-tools`
- `libqt5x11extras5-dev`
- `libopencv-dev`
- `libspdlog-dev`
- `libfmt-dev`
- `libomp-12-dev`
- `qt5-default`
- `libqt5x11extras5`
- `libspdlog1`
- `libomp5-12`
- `libxsettings-dev`
- `libxsettings-client-dev`

#### Full command:

`sudo apt install qtbase5-dev qtbase5-dev-tools libqt5x11extras5-dev libopencv-dev libspdlog-dev libfmt-dev libomp-12-dev qt5-default libqt5x11extras5 libspdlog1 libomp5-12 libxsettings-dev libxsettings-client-dev`

### List of Fedora packages that resolve them:

- `opencv-devel`
- `qt5-qtbase-devel`
- `spdlog-devel`
- `qt5-qtx11extras-devel`

#### Full command:

`sudo dnf install opencv-devel qt5-qtbase-devel spdlog-devel qt5-qtx11extras-devel`

## Installing and running

### For Arch-based systems:

1. You can install this port via its [PKGBUILD](https://github.com/mdk97/aitrack-linux-pkgbuild)
2. Install the `opentrack` package from the AUR.
3. Run Opentrack and make sure to select Input = **UDP over network**, then, click "Start". Opentrack then will be listening for the data AITrack will send.
4. Run `aitrack` and click "Start tracking".
5. Look around!

### For Ubuntu-based systems:

1. Download onnxruntime: `curl -L https://github.com/microsoft/onnxruntime/releases/download/v1.4.0/onnxruntime-linux-x64-1.4.0.tgz --output onnxruntime-linux-x64-1.4.0.tgz`.
2. Extract the archive: `gunzip onnxruntime-linux-x64-1.4.0.tgz && tar --extract -f onnxruntime-linux-x64-1.4.0.tar`.
3. Generate the Makefile: `qmake -makefile`.
4. Build the project: `make`.
5. Create the directory where the models will be searched: `sudo mkdir /usr/share/aitrack && sudo mkdir /usr/share/aitrack/models`.
6. Copy all the model files into the newly created directory: `sudo cp models/* /usr/share/aitrack/models/`.
7. Copy the shared object file `libonnxruntime.so.1.4.0` into the `/usr/lib/` directory: `sudo cp onnxruntime-linux-x64-1.4.0/lib/libonnxruntime.so.1.4.0 /usr/lib/`.
8. Install OpenTrack the preferred way for your distro.
9. Run Opentrack and make sure to select Input = **UDP over network**, then, click "Start". Opentrack then will be listening for the data AITrack will send.
10. Run `./aitrack` and click "Start tracking".
11. Look around!

### For Fedora-based systems full commands:
```
## Build
git clone git@github.com:mdk97/aitrack-linux.git
cd aitrack-linux
curl -L https://github.com/microsoft/onnxruntime/releases/download/v1.4.0/onnxruntime-linux-x64-1.4.0.tgz -o onnxruntime-linux-x64-1.4.0.tgz
tar -xzvf onnxruntime-linux-x64-1.4.0.tgz
qmake-qt5 -makefile
make

## Install
sudo mkdir /usr/share/aitrack && sudo mkdir /usr/share/aitrack/models
sudo cp models/* /usr/share/aitrack/models/
sudo cp onnxruntime-linux-x64-1.4.0/lib/libonnxruntime.so.1.4.0 /usr/lib64/
sudo cp ./aitrack /usr/bin/

## Runtime Deps (if built in container and don't want to install all devel build packages, else build deps nistalled work for running)
sudo dnf install opencv spdlog qt5-qtbase qt5-qtx11extras
```

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

## Bugs and Contributing

If you encounter any bug/problem or you have some idea, post it on the [issues page](https://github.com/AIRLegend/aitracker/issues) to find help or further discussion. If you decide to fix something or implement a request, feel free to fork this repo, develop your new feature in a separate branch and then, make a PR to review it, here is the [guide to developers](Doc/DEVELOP.md) (also available in the wiki).

Besides, there is a Discord server you can join to be aware of the news of the project, report problems or request features!

<a href="https://discord.gg/3XHY4xSDGv"><img src="https://image.flaticon.com/icons/svg/2111/2111370.svg" width="30px"/></a> Join the server!

Thank you!

## Acknowledgements

- [inspirit](https://github.com/inspirit), for the PS3 C++ camera library which I used during development.
- [emilianavt](https://github.com/emilianavt/), for porting the original Pytorch pretrained landmark model to ONNX format.

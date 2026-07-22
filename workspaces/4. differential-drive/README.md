I needed to migrate to ubuntu 24.04 for this. Also setup ros2 jazzy
https://docs.ros.org/en/jazzy/Installation.html


and gazebo harmonic (refer to this-- https://youtu.be/dY8JxldcuqA?si=90GTBCL2aOSm1AI5)



To make all OPENGL applications to use nvidia, edit bashrc using 
```sudo nano .bashrc```
```
export __NV_PRIME_RENDER_OFFLOAD=1
export __GLX_VENDOR_LIBRARY_NAME=nvidia
```

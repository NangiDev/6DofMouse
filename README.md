# 6DofMouse
A home built 3D Cad mouse based on [this project](https://hackaday.com/2022/12/28/mouse-enjoys-its-freedom/), but with some modifications

## Modifications
The body is the same, but I had to modify the internals a bit, because I only had Micro Pro Atmega32u4's at home. Which does not have enough analog pins.
So I decided to daisy chain together two Micro's.
Calling them HEAD and TAIL.

### Blender add-on
To make it easier and better, in my opinion, I decided to only support Blender. Thus making it depend on a Blender add-on.
[Code located here](https://github.com/NangiDev/Blender6DofMouseAddon)

### Curcuit
The curcuit is something like this:

```
          Joystick1
              | 
Computer <-> HEAD <-> TAIL <-> Joystick3
              |
          Joystick2
```

#### Detailed
##### SOON


## Pictures
### SOON

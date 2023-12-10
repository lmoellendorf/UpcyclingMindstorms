# UpcyclingMindstorms
Use Mindstorms peripherals on Arduino

## API


For a description of the Application Programming Interface, i.e. how to code
with this library, see:

- [Documentation on Gitlab](https://lmoellendorf.gitlab.io/UpcyclingMindstorms) or
- [Documentation on Github](https://lmoellendorf.github.io/UpcyclingMindstorms)

## Mindsensors LineLeader

See the [user guide of Line Follower Sensor for NXT or EV3](http://www.mindsensors.com/pdfs/LineLeader-v2-User-Guide.pdf).

## Sensor Cables

The sensors cables of both vendors provide wires for

- analog input
- ground (GND)
- power supply, aka Voltage common collector (VCC)
- I2C serial communication bus (SCL/SDA)

The table below maps the pinout of LEGO Mindstorms cables to the pinout ouf
Makeblock mBot cables.


| Pin   | Color   | LEGO         | Makeblock      |
|-------|---------|--------------|----------------|
| 1     | white   | analog input | analog input 1 |
| 2     | black   | GND          | analog input 2 |
| 3     | red     | GND          | VCC            |
| 4     | green   | VCC          | GND            |
| 5     | yellow  | SCL          | SDA            |
| 6     | blue    | SDA          | SCL            |

Therefore to use LEGO Mindstorms sensors and motors on Makeblock
mBot we have to produce adapter cables.

We do this by replacing one plug of a LEGO Mindstorms cable by a standard RJ25
plug, using a standard RJ25 crimp tool.
To match the different pinouts we twist each color pair once so the order of
the colors in our standard plug becomes:

| Pin   | Color   |
|-------|---------|
| 1     | black   |
| 2     | white   |
| 3     | green   |
| 4     | red     |
| 5     | blue    |
| 6     | yellow  |

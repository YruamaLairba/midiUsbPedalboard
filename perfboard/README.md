# midiUsbPedalboard - perfboard

The aim of this kicad project is to design a perfboard layout. The pcb layout is infact a representation of a perfboard layout, that why almost everything is aligned on a 2.54mm grid. On the PCB view :
* The green track named "B.Cu" are done by linking pad with tin.
* Tracks named "wire[1-4]" represent interconnection wires.
* "In1.Cu" and "In2.Cu" simulate interconnections inside the Arduino to avoid some DRC errors.
* Edge Cut borders represent the grid size of my perfboard. In practice, you may cut the unused part of the perfboard to make it fit inside the pedalboard enclosure.
* Mounting hole represent 4mm mounting hole for M4 screw that you should drill.

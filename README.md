# MusicBox
MusicBox is an easy to use, robust, and child-friendly music or audio book player.

This repository provides instructions and the necessary code.

## About ##

After seeing the [Toniebox][] in stores and liking the concept, I wanted to create an open version of a robust audio player for my children.

My final product looks like this:

![MusicBox - final product][img1]

My kids are using figurines attached to small NFC tags and place them at the top of the box. The MusicBox then starts playing a pre-loaded audio file that belongs to that NFC tag/figurine. There is no way to pause. To stop the audio playback, it's necessary to pull the plug. The volume is adjusted by a knob (attached to a standard e-guitar potentiometer).

## Parts list ##

You can find everything you need (plus some optional things) in the [parts list document][parts].

## Step by step ##

The step by step guide for building your MusicBox is in [this document][stepbystep].

## Code ##

Here is the code you can put onto your arduino: 

In addition, there is [a script][mp3script] for converting a number of .mp3 files to a single, merged .wav file. That way, you can play something longer (like an audiobook split into many chapters) with just a single NFC chip.


[Toniebox]: https://tonies.de/

[parts]: /instructions/parts_list.md
[stepbystep]: /instructions/stepbystep.md
[mp3script]: /code/mp3towavscript.sh

[img1]: /images/final.jpeg

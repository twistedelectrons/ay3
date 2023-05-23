# AY3

This is the Atmega1284 firmware for the [AY3 Synthesizer](https://www.twistedelectrons.com/ay3).

Find the official releases at [the official product page](https://www.twistedelectrons.com/ay3).

THANKS!

A million thanks to RIO for fixing and opening the code!

![Photo of the AY3](https://static.wixstatic.com/media/b8c32b_3ae5c456c0404cf6802aa7ab9bbe1163~mv2.jpeg)

## Building and flashing the source code:

Install `platformio` and `python2`. (Yes. I am so sorry :(.)

To compile the firmware and to generate the firmware update sysex, run:

```
make firmware.syx
```

Then put the device into bootloader mode by holding down the encoder button while turning it on,
and send the sysex. Note that you need to wait about 200msec between each sysex.

## Contributing

If you want to fix a bug, add a feature or contribute in any other way to the development
of this firmware, we are glad to accept a pull request in this repository! Please make sure
your contribution adheres to the following:

- Please update [CHANGELOG.md](CHANGELOG.md) to contain a brief description of your changes.
- Ensure you do not break loading of old patches.
- Format your code using `make fmt` before submitting.

Thank you, we are looking forward to your contribution! :)

## License

The AY3 firmware under `src/` and `include/` is free software. It is released under the terms of
the [ISC License](LICENSE.md). The libraries and tools distributed in the `3rdparty/` and `lib/`
directories have their own copyright and license notes.


## Switch-SwShBoxReleaser

![Screenshot of Auto Releasing](https://i.imgur.com/KxVQF5z.png)

Modified from the Proof-of-Concept Fightstick for the Nintendo Switch by [progmem](https://github.com/progmem/Switch-Fightstick), Splatoon printer by [shinyquagsire23](https://github.com/shinyquagsire23/Switch-Fightstick), and Pokemon Auto Breeder by [patina27](https://github.com/patina27/Switch-PokemonAutoBreeder).

Uses the LUFA library and reverse-engineering of the Pokken Tournament Pro Pad for the Wii U to enable custom fightsticks on the Switch System.

This script releases a specified amount of boxes of Pokemon. This script can release boxes even if there are gaps in the boxes, but the first row MUST be filled. It has only been tested on Arduino UNO R3 in the English versions of Pokémon Sword & Shield.

Be sure to correctly define the `settings.h` file (explained below), and follow the prerequisites prior to beginning the process.
 
### Before Flashing

Before flashing to the Arduino, you will need to check two files: `makefile` and `settings.h`. 

#### Edit `makefile`
Follow the instructions from [shinyquagsire23's Splatoon printer](https://github.com/shinyquagsire23/Switch-Fightstick) for the `makefile`. 

A quick recap: 

- Inside the `makefile`, make sure the `LUFA_PATH` points to the `LUFA` subdirectory inside your `LUFA` directory. 

- Edit the setting `MCU = atmega16u2` if necessary.

#### Edit `settings.h` 

- Define `number_of_boxes` for how many boxes of Pokemon you want to release.

### Before Starting the Bot

There is some small setup in game that must be done prior to starting the box.

In the Pokémon menu, make sure:

- The top row of every box you want to release is full. The script will still work if there are gaps in rows 2 to 5.
- You are in the leftmost box of Pokemon you want to release.
- The cursor is in `Select` mode (red).
- The cursor is starting on the top left Pokemon in the box.

Also ensure that: 

- You save prior to running the script, just in case you accidentally release an important Pokemon.

### You're done!

After you've compiled and flashed the script and ensured the proper settings listed above, you may plug it into the Nintendo Switch and the bot will start to run automatically. Good luck!

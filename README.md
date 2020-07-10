## Switch-SwShEggCollectorHatcher

![Screenshot of Auto Hatching](https://i.imgur.com/aUhhTv3.png)

Modified from the Proof-of-Concept Fightstick for the Nintendo Switch by [progmem](https://github.com/progmem/Switch-Fightstick), Splatoon printer by [shinyquagsire23](https://github.com/shinyquagsire23/Switch-Fightstick), and Pokemon Auto Breeder by [patina27](https://github.com/patina27/Switch-PokemonAutoBreeder).

Uses the LUFA library and reverse-engineering of the Pokken Tournament Pro Pad for the Wii U to enable custom fightsticks on the Switch System.

This script gathers eggs from the nursery on Route 5 and hatches them one box at a time. It has only been tested on Arduino UNO R3 in the English/Japanese/Korean versions of Pokémon Sword & Shield.

Be sure to correctly define the `settings.h` file (explained below), and follow the prerequisites prior to beginning the process.
 
### Before Flashing

Before flashing to the Arduino, you will need to check two files: `makefile` and `settings.h`. 

#### Edit `makefile`
Follow the instructions from [shinyquagsire23's Splatoon printer](https://github.com/shinyquagsire23/Switch-Fightstick) for the `makefile`. 

A quick recap: 

- Inside the `makefile`, make sure the `LUFA_PATH` points to the `LUFA` subdirectory inside your `LUFA` directory. 

- Edit the setting `MCU = atmega16u2` if necessary.

#### Edit `settings.h` 

- Define `nat_dex_number` using the National Pokédex number of the Pokémon species you are hatching. The script will look up the dex value to provide the correct egg cycles and hatching time (e.g. a value of `810` for Grookey).

- Define `number_of_boxes` for how many boxes of eggs you want to hatch. Note that there will likely be a difference of eggs due to the RNG nature of egg collection. 

- Define `save` if you would like the script to save for you. Use this at your own risk.
	- `0` = Don't save at all
	- `1` = Save after every box
	- `2` = Save at end of all boxes

- Define `flame_body` for whether or not your starting Pokémon in your party will shorten the hatch time:
	- `1` = Pokémon with Flame Body, Steam Engine, or Magma Armor ability in the first slot
	- `0` = Different Pokémon in the first slot

- The `intial_egg_check` is for how many attempts the script will do to collect for the first round of hatching. The rate at which the two Pokémon create eggs is RNG based on a few different factors which you can read about [here](https://bulbapedia.bulbagarden.net/wiki/Oval_Charm). Assuming about 80% chance for most use cases (Oval Charm, different species/OT), `46` attempts has a roughly 99.4% chance of obtaining 30+ eggs. The script will still most likely work even if it gets less than 30 eggs.

- The `subsequent_egg_check` is similar to the `initial_egg_check` but for subsequent rounds of egg collecting. Assuming the initial round created some overflow of eggs, this # can stand to be lower. `38` attempts has a roughly 65.5% chance of obtaining 30+ eggs.

### Before Starting the Bot

There is some small setup in game that must be done prior to starting the box.

Confirm in Options you have the following settings:

- Text Speed: Fast
- Send to Boxes: Automatic
- Give Nicknames: Don't give

In the Pokémon menu, make sure:

- Your party is completely full.
- You have the required # of empty boxes going left to right.
- Your last box used is the first empty box where you want your eggs (so collected eggs will default to this box first).
- The rightmost column in the previous box (before the first empty box) is completely empty. Your first party members will get put here once egg hatching begins.

Also ensure that: 

- When you open up the main Menu by pressing [X], the cursor should hover over Pokémon.
- You dropped off the parent species Pokémon at the Route 5 nursery, not the Wild Area one.
- You have some excess box storage for any overflow of eggs.


### You're done!

After you've compiled and flashed the script and ensured the proper settings listed above, you may plug it into the Nintendo Switch and the bot will start to run automatically. Good luck!

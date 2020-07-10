#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#define nat_dex_number 810
    // National Pokedex Number of what you're hatching
    // Determines the egg cycles and hatching time
#define number_of_boxes 1
    // How many boxes of eggs to hatch
#define save 0
    // 0 = Don't save at all
    // 1 = Save after every box
    // 2 = Save at end of all boxes
#define flame_body 1
    // 1 = Pokemon with Flame Body, Steam Engine, or Magma Armor ability in first slot
    // 0 = Different Pokemon in first slot
#define initial_egg_checks 46
    // How many attempts to collect 30 eggs for the first round
    // The bot will still work even if it gets less than 30 eggs
#define subsequent_egg_checks 38
    // How many atempts to collect 30 eggs in subsequent rounds
    // Additional eggs from previous rounds should make up for the loss

#endif

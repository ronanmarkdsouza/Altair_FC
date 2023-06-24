/**
 * @file    kadar_rec.cpp
 * @brief   Code for Recovery alert
 * @author  Ronan Mark D'souza
 * @date    23.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

const int NOTE_A4 = 1000;
const int NOTE_A4_SHARP = 1060;
const int NOTE_B4 = 1120;
const int NOTE_C5 = 1180;
const int NOTE_C5_SHARP = 1250;
const int NOTE_D5 = 1320;
const int NOTE_E5_FLAT = 1400;
const int NOTE_E5 = 1480;
const int NOTE_F5 = 1570;
const int NOTE_F5_SHARP = 1670;
const int NOTE_G5 = 1770;
const int NOTE_G5_SHARP = 1870;
const int NOTE_A5 = 1980;
const int NOTE_A5_SHARP = 2100;

// Define the Star Wars theme melody using the note frequencies
const int starWarsThemeMelody[] = {
  NOTE_G5, NOTE_G5, NOTE_G5_SHARP, NOTE_G5, NOTE_E5_FLAT, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4_SHARP, NOTE_A4, NOTE_A4_SHARP,
  NOTE_B4, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4,
  NOTE_G5, NOTE_G5, NOTE_G5_SHARP, NOTE_G5, NOTE_E5_FLAT, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4_SHARP, NOTE_A4, NOTE_A4_SHARP,
  NOTE_B4, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4,
  NOTE_G5, NOTE_G5, NOTE_G5_SHARP, NOTE_G5, NOTE_E5_FLAT, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4_SHARP, NOTE_A4, NOTE_A4_SHARP,
  NOTE_B4, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4,
  NOTE_A4, NOTE_A4, NOTE_A4_SHARP, NOTE_A4, NOTE_A4_SHARP,
  NOTE_B4, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4
};

// Define the duration of each note (in milliseconds)
const int starWarsThemeNoteDurations[] = {
  200, 200, 200, 200, 150, 150,
  400, 200, 200, 200, 200, 200,
  400, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 150, 150,
  400, 200, 200, 200, 200, 200,
  400, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 150, 150,
  400, 200, 200, 200, 200, 200,
  400, 200, 200, 200, 200, 200,
  400, 200, 200, 200, 200,
  400, 200, 200, 200, 200, 200
};

// Play the Star Wars theme
void playStarWarsTheme() {
  for (int i = 0; i < sizeof(starWarsThemeMelody) / sizeof(starWarsThemeMelody[0]); i++) {
    int noteDuration = starWarsThemeNoteDurations[i];

    // Play the note
    tone(BUZZER, starWarsThemeMelody[i], noteDuration);

    // Delay for the note duration
    delay(noteDuration);

    // Stop playing the note
    noTone(BUZZER);

    // Add a small pause between notes
    delay(50);
  }
}

void kadar_rec(void*){
  while(true){
    playStarWarsTheme();
  // Delay before playing again
  delay(2000);
  }
}
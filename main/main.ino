#include <Keyboard.h> // Essential for Bad USB/HID emulation

// Define the pins for clarity
const int button9Pin = 9; // DP9
const int button10Pin = 10; // DP10

void setup() {
  // Initialize the button pins as inputs with a pull-up resistor
  // The pull-up keeps the pin HIGH until the button is pressed (connecting it to GND), so the state is LOW when pressed
  pinMode(button9Pin, INPUT_PULLUP);
  pinMode(button10Pin, INPUT_PULLUP);
  
  // Begin USB communication (required for Keyboard library)
  Keyboard.begin(); 
}

// Function to type a string character by character with a delay
void type_slowly(const char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    Keyboard.write(str[i]);
    // A 30ms delay between EACH character
    delay(30); 
  }
}

void payload1() {
  // A simple example payload: Opens the Run dialog (Windows Key + R), types "notepad.exe", enter, then types "Roadbobek was here <3"
  Keyboard.press(KEY_LEFT_GUI); // Press the Windows/GUI key
  Keyboard.press('r'); // Press 'r'
  Keyboard.releaseAll(); // Release all keys
  delay(500); // Wait for the dialog to open
  Keyboard.print("notepad.exe");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(1000); // Wait for Notepad to open
  type_slowly("Roadbobek was here <3 ");
}

void payload2() {
  // A simple example payload: Opens the Run dialog (Windows Key + R), then goes to "https://github.com/roadbobek"
  Keyboard.press(KEY_LEFT_GUI); // Press the Windows/GUI key
  Keyboard.press('r'); // Press 'r'
  Keyboard.releaseAll(); // Release all keys
  delay(500); // Wait for the dialog to open
  Keyboard.print("https://github.com/roadbobek");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}

void loop() {
  // Check if DP9 is pressed (LOW state due to INPUT_PULLUP)
  if (digitalRead(button9Pin) == LOW) {
    // Execute payload 1
    payload1();
    // Debounce: Wait a moment to prevent multiple accidental presses
    delay(200); 
  }

  // Check if DP10 is pressed (LOW state due to INPUT_PULLUP)
  if (digitalRead(button10Pin) == LOW) {
    // Execute payload 2
    payload2();
    // Debounce: Wait a moment
    delay(200); 
  }
}
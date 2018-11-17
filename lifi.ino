/*         Project Lite-Fi
 *       By Nima Behmanesh, Joe Janson
 *          Version 1.0.4
 *         Senior Poject 2018
 *       Casa Roble Highschool
 *
 */

// These includes necessary libraries that contain functions needed for this program.
#include <stdio.h>
#include <string.h>

// intializes led pins.
int led = 9;  int led2 = 8; int led3 = 7;
int led4 = 6; int led5 = 5; int led6 = 4;
int led7 = 3; int led8 = 2;

// Ignore these for now
int photo, photo2;


char binary_list[25][8]; // This is the array where the byte (8 bit) arrays are stored.

int mew = 55; // delay time

class Laser { // Creates the class laser. This contains all the functions of a laser.
  public:

  int lednum; // This the actual LED pin number.

  // The on function to turn on a laser of lednum pin
  void on(int delay_set = 0, int delay_set2 = 0) { // Can set before and after delays.
    delay(delay_set); // This will take the first delay_set as the number to delay.
    digitalWrite(lednum, HIGH);
    delay(delay_set2); // This will take the second delay_set2,
  }

  // The off function to turn off a laser of lednum pin
  void off(int delay_set = 0, int delay_set2 = 0) { // Turns off lasers.
    delay(delay_set);
    digitalWrite(lednum, LOW);
    delay(delay_set2);
  }

  // This simply interates through the lights and turns them all off.
  void alloff(int led = 10) {
    for (lednum = 9; lednum > 0; lednum--) {
      if (lednum == led){
        continue;
      }
      else {
        digitalWrite(lednum, LOW);
      }
    }
  }

  // This will turn them all on using the same method as the alloff method.
  void allon() {
    for (int lednum = 9; lednum > 0; lednum--) {
      digitalWrite(lednum, HIGH);
    }
  }

  // These next two functions are kinda fishy for some reason.
  // This allows you to turn off any laser as long as any Laser object is initialized.
  // This means the lednum could be different than the one a user turns of using these functions.
  // I MIGHT DELETE THIS FUNCTIONS IF I DEEM THEM UNNECESSARY IN THE FUTURE!!!
  void sigon(int ledcustom) {
    digitalWrite(ledcustom, HIGH);
  }


  void sigoff(int ledcustom) {
    digitalWrite(ledcustom, LOW);
  }
};


void text_to_binary(const char* input) {
  int ascii; // Used to store the ASCII number of a character
  int length = strlen(input); // Find the length of the user's input
  for (int x = 0; x < length; x++) { // Repeat until user's input have all been read
    // x < length because the last character is "\0"
    ascii = input[x]; // Store a character in its ASCII number
    char* binary_reverse = new char[9]; // Dynamic memory allocation
    char* binary = new char[9];
    int y = 0; // Counter used for arrays

    while (ascii != 1) { // Continue until ASCII == 1
      if (ascii % 2 == 0) { // if ASCII is divisible by 2
        binary_reverse[y] = '0'; // Then put a zero
        }
      else if (ascii % 2 == 1) { // If not divisible by 2
        binary_reverse[y] = '1'; // Then put a 1
        }
      ascii /= 2; // Find quotient of ASCII / 2
      y++; // add 1 to y for next loop
      }
    if (ascii == 1) { // When ASCII is 1, we have to add 1 to the beginning
      binary_reverse[y] = '1';
      y++;
    }
    if (y < 7) { // Add zeros to the end of string if not 8 characters (1 byte)
      for (; y < 8; y++) { // Add until binary_reverse[7] (8th element)
        binary_reverse[y] = 0;
      }
    }
    for (int z = 0; z < 8; z++) { // Our array is reversed, put the number in the right order.
      binary[z] = binary_reverse[7 - z];
    }
    for (int i = 0; i < 8; i++) { // This will store each 8 bits in an array within the binary list.
      // This will store the 8 bits in row x and column i.
      // x is the same value as that characters position in the input char array.
      // So, if a is the second letter in the input, x = 2, and i = 0, 1, 2, 3, 4, 5, 6, 7
      binary_list[x][i] = binary[i]; // This will store the 8 bits in row x and column i.
      binary_list[x][0] = '0'; // This guarantees that the start of a new character will start with 0.
      }
    delete[] binary_reverse; // Frees data for next iteration
    delete[] binary; // Frees data for next iteration. This is important.
    }
}

void setup() {
  // This declares all the pinoutputs.
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);

  Serial.begin(9600); // Starts serial monitor
  while (!Serial);
  Serial.println("----------------------------------");
  Serial.println("   Welcome to Lite-Fi v. 1.0");
  Serial.println("Lite-Fi:  Type !help for commands.");
  Serial.println("----------------------------------");
}

void loop() {
  if (Serial.available()) { // reads input.
    char ch = Serial.read(); // reads prefix for commands or word sending.
    if (ch == '!') { // checks if command.
      String command = Serial.readString();

      // This isn't totally functional yet. This will be apart of the reciever.
      // This code won't actually be apart of this file in the final product.
      if (command == "read") {
        Serial.println(analogRead(photo));
        Serial.println("-");
        Serial.println(analogRead(photo2));
      }

      // This initializes an object laser of class Laser.
      // This allows me to get quicker access to certain functions like
      // turning the laser on and off.
      Laser laser;

      // Runs through each laser once.
      if (command == "test") {
        for (int i = 9; i > 0; i--) {
          laser.lednum = i;
          laser.on(0, 35);
          laser.off();
        }
      }

      // Turns all lasers on.
      if (command == "on") {
        laser.allon();
      }
      // Turns all lasers off.
      if (command == "off") {
        laser.alloff();
      }

      // This actually doesn't do anything other than make you feel better.
      if (command == "clear") {
        Serial.println("--------------------------");
        Serial.println("Lite-Fi: Cleared");
        Serial.println("--------------------------");
      }

      // This is your generic help command. Although as of 1.0 it isn't updated.
      if (command == "help") {
        Serial.println("--------------------------");
        Serial.println("Lite-Fi: ![command]");
        Serial.println("  !off - turns off laser.");
        Serial.println("  !on - turns laser on.");
        Serial.println("  !clear - clears last command.");
        Serial.println("  !test - will test resistor input.");
        Serial.println("  !read - will give current raw resistor value.");
        Serial.println("  To transmit words, @[sentence]");
        Serial.println("---------------------------");
      }
    }

    // This is the prefix and command structure to send out messages.
    else if (ch == '@') {
      // Again intializes object laser of class Laser.
      Laser laser;
      // Stores the users input as a string "letter."
      String letter = Serial.readString(); // takes string.

      /*  NOTE: THIS IS A SENIOR PROJECT NOTE NOT A PROGRAMMERS NOTE
       * This part is important. C++ doesn't actually have a "String" type.
       * So to iterating through a string to get certain characters is a weird process.
       * These next two lines of code allow me to store the string as an array of characters.
       * The drawback to this is that the message can only be 25 characters long before it overflows.
       */

      char char_array[25]; // creates an array to store characters of string.
      letter.toCharArray(char_array, 25); // converts string to character array.

      // This converts the "letter" to binary to be represented by the lasers.
      text_to_binary(char_array);

      // This will iterate through the array and check for 1's and 0's according to each laser.
      // This is what the reciever will see.
      // This might need to be optimized, and I also haven't checked for any special cases.
      // Hopefiully this will work out lol.
      for (unsigned int i = 0; i < strlen(char_array); i++) {

        laser.sigon(5); // This will keep the last laser constantly on.

        if (binary_list[i][0] == '0'){
          laser.lednum = 9;
          laser.off();
        }
        else if (binary_list[i][0]) {
          laser.lednum = 9;
          laser.on();

        }
        if (binary_list[i][1] == '0'){
          laser.lednum = 8;
          laser.off();
        }
        else if (binary_list[i][1]) {
          laser.lednum = 8;
          laser.on();

        }
        if (binary_list[i][2] == '0'){
          laser.lednum = 7;
          laser.off();
        }
        else if (binary_list[i][2]) {
          laser.lednum = 7;
          laser.on();

        }
        if (binary_list[i][3] == '0'){
          laser.lednum = 6;
          laser.off();
        }
        else if (binary_list[i][3]) {
          laser.lednum = 6;
          laser.on();
        }

        delay(mew);
        laser.alloff(5); // This will reset the lasers back to 1.
        delay(mew);

        if (binary_list[i][4] == '0'){
          laser.lednum = 9;
          laser.off();
        }
        else if (binary_list[i][4]) {
          laser.lednum = 9;
          laser.on();

        }
        if (binary_list[i][5] == '0'){
          laser.lednum = 8;
          laser.off();
        }
        else if (binary_list[i][5]) {
          laser.lednum = 8;
          laser.on();
        }
        if (binary_list[i][6] == '0'){
          laser.lednum = 7;
          laser.off();
        }
        else if (binary_list[i][6]) {
          laser.lednum = 7;
          laser.on();

        }
        if (binary_list[i][7] == '0') {
          laser.lednum = 6;
          laser.off();
        }
        else if (binary_list[i][7]) {
          laser.lednum = 6;
          laser.on();
        }

        // These delays will eventually be adjusted for the future.
        // It all depends on the photodiodes speed.
        delay(mew);
        laser.alloff(5);
        digitalWrite(led5, LOW);
        delay(mew);
      }
      
    }


    // This is a test environment. Things that may become functions start up here.
    // This area should be ignored for the most part.
    else if (ch == '$') {
      Laser laser;
      Serial.println("Welcome to the testing environment");
      String letter = Serial.readString() + '!'; // takes string.
      char char_array[25]; // creates an array to store characters of string.
      letter.toCharArray(char_array, 25); // converts string to character array.
      if ((char_array[0] == 'o') and (char_array[1] == 'n')) {
        for (int i = 2; i < 25; i++) {
          // I really don't know why this works
          if (char_array[i] == '!') {
            break;
          }
          char lednumber = char_array[i];
          switch (lednumber) {
          case '1':
            laser.lednum = 9;
            laser.on();
            break;
          case '2':
            laser.lednum = 8;
            laser.on();
            break;
          case '3':
            laser.lednum = 7;
            laser.on();
            break;
          case '4':
            laser.lednum = 6;
            laser.on();
            break;
          case '5':
            laser.lednum = 5;
            laser.on();
            break;
          case '6':
            laser.lednum = 4;
            laser.on();
            break;
          case '7':
            laser.lednum = 3;
            laser.on();
            break;
          case '8':
            laser.lednum = 2;
            laser.on();
            break;
          }
        }
      }

      if ((char_array[0] == 'o') and ((char_array[1] == 'f') and char_array[2] == 'f')) {
        for (int i = 2; i < 25; i++) {
          char lednumber = char_array[i];
          switch (lednumber) {
          case '1':
            laser.lednum = 9;
            laser.off();
            break;
          case '2':
            laser.lednum = 8;
            laser.off();
            break;
          case '3':
            laser.lednum = 7;
            laser.off();
            break;
          case '4':
            laser.lednum = 6;
            laser.off();
            break;
          }
        }
      }
    }
  }
}

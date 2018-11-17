const int pN = 0; // null
const int p0 = 2; // 1st
const int p1 = 3; // 2nd
const int p2 = 4; // 3d
const int p3 = 5; // 4th
const int mew = 55; // delay on transmittor
const int minlit = 180;

int dakdec = 0; // Defines the integer containing the decimal value of the current letter iteration
int dakpow = 0; // Defines the integer containing the value of the power for converting from binary to decimal value
int data[30][8];
int it = 0;
char letter_list[30];
char binary_list[30][30];
int dec_list[30];

void setup()
{
  Serial.begin(9600);
  Serial.println("----------------------------------");
  Serial.println("   Welcome to Fi-Li v. 1.0");
  Serial.println("  Enter any key to view data");
  Serial.println("----------------------------------");  
  Serial.println();  
}

void loop()
{
  int rN = analogRead(pN);
  
  if (rN > minlit)
  {
    // defines & updates resistor inputs through iterations
    int r0 = analogRead(p0);
    int r1 = analogRead(p1);
    int r2 = analogRead(p2);
    int r3 = analogRead(p3);

    // iterates twice through lights
    for (int n=0; n<2; n++)
    {
      data[it][3 + 4*n] = analogRead(p0);
      data[it][2 + 4*n] = analogRead(p1);
      data[it][1 + 4*n] = analogRead(p2);
      data[it][0 + 4*n] = analogRead(p3);
      delay(2*mew);
    }
    it++;
  
  }


  
if (Serial.available() > 0)
{
for (int i = 0; i < 24; i++)
  {
    for (int j = 0; j < 8; j++)  // Since each byte array is only 8 bits long
    {

    if (data[i][j] > minlit){
      binary_list[i][j] = 1;
    }
    if (binary_list[i][j] == 1)
      {
        if (j < 3){
        dakpow = 7 - j; // Defines the current exponential power as 7-j to reverse the order of the binary array
        dakdec = 1 + dakdec + pow (2, dakpow); // Completes the math of adding each binary value's decimal value
        }
        else {
        dakpow = 7 - j; // Defines the current exponential power as 7-j to reverse the order of the binary array
        dakdec = dakdec + pow (2, dakpow); // Completes the math of adding each binary value's decimal value
        }
       }
      }
      dec_list[i] = dakdec;
      letter_list[i] = dec_list[i];
      Serial.println(letter_list[i]);
      delay(200);
      dakdec = 0;
      if (letter_list[i] < 1)
      {
        exit(0);
      }
  }

  exit(0); 

  }
}


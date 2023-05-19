// MAY 2023

#include <TimerOneThree.h>
#include <MIDI.h>
#include <EEPROM.h>

unsigned long resetCounter; // RIO: type fixed
bool voicePressed;

int lastEnvSpeed;
byte masterChannel; // located at 3802

byte ay3Reg1[18];
byte ay3Reg2[18];
byte ay3Reg1Last[18];
byte ay3Reg2Last[18];

byte key = 0;
int bender = 64;
int clockSpeeds[] = {0, 6, 8, 12, 16, 24, 32, 40};

const int tp[] = {
    // Frequencies related to MIDI note numbers
    15289, 14431, 13621, 12856, 12135, 11454, 10811, 10204, // 0-o7
    9631, 9091, 8581, 8099, 7645, 7215, 6810, 6428,         // 8-15
    6067, 5727, 5405, 5102, 4816, 4545, 4290, 4050,         // 16-23
    3822, 3608, 3405, 3214, 3034, 2863, 2703, 2551,         // 24-31
    2408, 2273, 2145, 2025, 1911, 1804, 1703, 1607,         // 32-39
    1517, 1432, 1351, 1276, 1204, 1136, 1073, 1012,         // 40-47
    956, 902, 851, 804, 758, 716, 676, 638,                 // 48-55
    602, 568, 536, 506, 478, 451, 426, 402,                 // 56-63
    379, 358, 338, 319, 301, 284, 268, 253,                 // 64-71
    239, 225, 213, 201, 190, 179, 169, 159,                 // 72-79
    150, 142, 134, 127, 119, 113, 106, 100,                 // 80-87
    95, 89, 84, 80, 75, 71, 67, 63,                         // 88-95
    60, 56, 53, 50, 47, 45, 42, 40,                         // 96-103
    38, 36, 34, 32, 30, 28, 27, 25,                         // 104-111
    24, 22, 21, 20, 19, 18, 17, 16,                         // 112-119
    15, 14, 13, 13, 12, 11, 11, 10,                         // 120-127
    0                                                       // off
};

bool writeChannel = false;
byte seqNoise1;
byte seqNoise2;
byte seqVoice1;
byte seqVoice2;

boolean seqNoise[16];
boolean seqVoice[16];

int staggered[] = {0, 1, 4, 2, 5, 3, 6};

// the timer object
int memPointer;

int preset = 0;
int bank = 0;
int selectedStep = 0;
byte oldMatrix[7]; // RIO: Length extended, because loop cursor runs behind oldMatrix (length 6), but entry[0] is wasted
int seqDisplayCounter = 20000;
boolean seqPressed;
byte potJob = 0;
byte voiceMode = 1;
int glider;
byte envSpd;
byte tune[7];
byte presetTune[7];
byte countDown = 9;
byte numberOld;

byte chord = 1;
byte chordLast = 0;

byte arpOct = 0;
byte arpOct1 = 0;
byte arpOct2 = 0;
byte arpOct3 = 0;
byte arpOct4 = 0;
byte arpOct5 = 0;
byte arpOct6 = 0;

byte detune = 1;
int held = 0;

int held1 = 0;
int held2 = 0;
int held3 = 0;
int held4 = 0;
int held5 = 0;
int held6 = 0;

byte arpStep = 1;
byte arpStep1 = 1;
byte arpStep2 = 1;
byte arpStep3 = 1;
byte arpStep4 = 1;
byte arpStep5 = 1;
byte arpStep6 = 1;
byte arpRange = 1;

int sync = 0;
int encTimer = 0;

// Preset Values
int noiseFreq1 = 16;
int noiseFreq2 = 16;
int vol[7] = {6, 6, 6, 6, 6, 6, 6};

int envNumber1 = 1;
int envNumber2 = 1;

byte seqNote[] = {0, 4, 7, 4, 0, 4, 7, 4, 0, 4, 7, 4, 0, 4, 7, 4, 0, 4, 7, 4, 0, 4, 7, 4, 0, 4, 7, 4, 0, 4, 7, 4, 0, 7, 8, 3, 1, 6, 2, 4, 6, 7, 4, 2, 6, 7, 0};

int seqSpeed;
float lfoSpeed = 1;
int seqSetup = 1;
int lfoShape = 1;
byte lfoDepth = 1;
byte ledMatrix[7];    // RIO: Length extended, because loop cursor runs behind ledMatrix (length 6), but entry[0] is wasted
byte ledMatrixPic[7]; // RIO: Length extended, because loop cursor runs behind ledMatrixPic (length 6), but entry[0] is wasted
byte glide = 1;
int arpSpeed = 1;

bool selectedChip;
int slots[7];

int destiPitch[7];
boolean savePressed = 0;

boolean retrig = 1;
boolean seqLoop = 1; // RIO: never changed
int seq = 0;

byte envShape1;
byte envShape2;

int base[7];
int potLast[5];
int offsetFreq[7];
int offsetNote[7];

int seqCounter = 0;
int seqMax = 1400; // RIO: unused
int seqStep = 0;

float lfoPhase = 0;
int lfoMax = 2000;
float lfo = 0;

byte noteMem[20];
byte noteMem1[20];
byte noteMem2[20];
byte noteMem3[20];
byte noteMem4[20];
byte noteMem5[20];
byte noteMem6[20];

int pitch[7];
int bend[7];
int pitchLast[7];

int arpCounter;

byte data7ALast = B11111111;
byte data7BLast = B11111111;

int mainCounter = 0;
int buttCounter = 0;
int buttCounter2 = 0;
boolean butt[20];
boolean buttLast[20];

int pressedRow = 0;

int ledNumber;
int number;
int pressedCol = 9;
int temp;

byte data7A = B11111111;
byte data7B = B11111111;

int counter = 0;
int job = 1;

byte mode = 1;

int lastStateCLK = -1; // initial -1, ignore first poll

#define ENCPINA 11  // CLK
#define ENCPINB 10  // DATA
#define INTERRUPT 0 // that is, pin 2

// 2mz clock pin
// const int freqOutputPin = 15;   // OC2A output pin for ATmega328 boards

const int ocr2aval = 16;

// RIO: unused freq calculation:
// const int prescale = 1;
// const float period = 2.0 * prescale * (ocr2aval+1) / (F_CPU/1.0e6);
// const float freq = 1.0e6 / period;

// AY3 STOFF
const int envTp[] = {
    3822, 3608, 3405, 3214, 3034, 2863, 2703, 2551,
    2408, 2273, 2145, 2025, 1911, 1804, 1703, 1607,
    1517, 1432, 1351, 1276, 1204, 1136, 1073, 1012,
    956, 902, 851, 804, 758, 716, 676, 638,
    602, 568, 536, 506, 478, 451, 426, 402,
    379, 358, 338, 319, 301, 284, 268, 253,
    239, 225, 213, 201, 190, 179, 169, 159,
    150, 142, 134, 127, 119, 113, 106, 100,
    95, 89, 84, 80, 75, 71, 67, 63,
    60, 56, 53, 50, 47, 45, 42, 40,
    38, 36, 34, 32, 30, 28, 27, 25,
    24, 22, 21, 20, 19, 18, 17, 16,
    15, 14, 13, 13, 12, 11, 11, 10,
    9, 9, 8, 8, 7, 7, 7, 6,
    6, 6, 5, 5, 5, 4, 4, 4,
    4, 4, 3, 3, 3, 3, 3, 2};

int analogCounter = 0;

// A IN
// Knob A0 = env/seq speed
// Knob A7 = glide
// Knob A6 = detune chord
// Knob A5 = lfo depth
// Knob A4 = lfo speed

int analogTemp;

byte chipDelay = 1;

// the setup routine runs once when you press reset:
void setup()
{

    Timer1.initialize(10000);        //
    Timer1.attachInterrupt(seqTick); // attach the service routine here

    preset = EEPROM.read(3800);
    bank = EEPROM.read(3801);
    masterChannel = EEPROM.read(3802);

    if (masterChannel == 0 || masterChannel > 16)
        masterChannel = 1;

    potLast[0] = potLast[1] = potLast[2] = potLast[3] = potLast[4] = -1;

    ledMatrix[1] = ledMatrix[2] = ledMatrix[3] = ledMatrix[4] = ledMatrix[5] = 255;

    base[1] = 0;
    base[2] = 0;
    base[3] = 0;
    base[4] = 0;
    base[5] = 0;
    base[6] = 0;

    slots[1] = 0;
    slots[2] = 0;
    slots[3] = 0;
    slots[4] = 0;
    slots[5] = 0;
    slots[6] = 0;

    tune[1] = 100;
    tune[2] = 100;
    tune[3] = 100;
    tune[4] = 100;
    tune[5] = 100;
    tune[6] = 100;

    pinMode(15, OUTPUT);
    DDRD = B11111100;

    // AY3
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(14, OUTPUT);

    digitalWrite(ENCPINA, HIGH); // enable pull-ups
    digitalWrite(ENCPINB, HIGH);

    // Matrix -
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);

    // Matrix +
    pinMode(16, OUTPUT);
    pinMode(17, OUTPUT);
    pinMode(18, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(20, OUTPUT);
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
    pinMode(5, INPUT);
    digitalWrite(5, HIGH);
    pinMode(6, INPUT);
    digitalWrite(6, HIGH);
    pinMode(7, INPUT);
    digitalWrite(7, HIGH);
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);

    // A1 - butt reads
    // A2 - butt reads
    // A3 - butt reads
    // 12 - butt read

    init2MhzClock();
    PORTC = 0;

    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(14, LOW);

    pinMode(9, OUTPUT);

    digitalWrite(9, LOW);

    pitch[1] = 0;
    pitch[2] = 0;
    pitch[3] = 0;
    pitch[4] = 0;
    pitch[5] = 0;
    pitch[6] = 0;

    set_chA_amplitude(0, false);
    set_chB_amplitude(0, false);
    set_chC_amplitude(0, false);
    set_chD_amplitude(0, false);
    set_chE_amplitude(0, false);
    set_chF_amplitude(0, false);

    // pressedRow=0;
    // voiceMode=0;
    // mode=2;
    // encoderMoved(0);

    Serial.begin(31250);

    // Check for held buttons
    PORTA |= _BV(1);  // digitalWrite (A1-25, HIGH);
    PORTA &= ~_BV(2); // digitalWrite (A2-26, LOW);
    PORTA |= _BV(3);  // digitalWrite (A3-27, HIGH);
    PORTC |= _BV(0);  // digitalWrite (16, HIGH);
    delay(1);

    if (!digitalRead(5))
    {
        writeChannel = true;
        seqSetup = 0;
        selectedStep = masterChannel - 1;
    }

    PORTA |= _BV(1);  // digitalWrite (A1-25, HIGH);
    PORTA |= _BV(2);  // digitalWrite (A2-26, HIGH);
    PORTA &= ~_BV(3); // digitalWrite (A3-27, LOW);
    PORTC |= _BV(0);  // digitalWrite (16, HIGH);
    delay(1);

    // sysex receive
    if (!digitalRead(5))
        receiveDump();
    if (!digitalRead(6))
    {
    } // vol

    PORTA |= _BV(1);  // digitalWrite (A1-25, HIGH);
    PORTA |= _BV(2);  // digitalWrite (A2-26, HIGH);
    PORTA |= _BV(3);  // digitalWrite (A3-27, HIGH);
    PORTC &= ~_BV(0); // digitalWrite (16, LOW);
    delay(1);

    if (!digitalRead(5))
    {
    } // noise
}

int notey;

// PINS

// OUT
// PORTB = LED ROWS ( o=on)    XXX54312
// PORTC = LED COLLUMS (1=on)  XX654321

// DIN
// D5 - butt grounds
// D6 - butt grounds
// D7 - butt grounds

// A1 - butt reads
// A2 - butt reads
// A3 - butt reads
// 12 - butt read

// implementation

// noise(0-31) = Noise Period

byte incoming;

int flag;
int data1;

void loop()
{
    readMidi();

    updateAy3();

    tick();

    if (seqCounter > seqSpeed)
        doSeq();
}

void miniDelay()
{
    // Make a really short delay in software to allow for settling
    // time on the bus. The loop needs the NOP command because the
    // compiler optimisations will detect nothing is happening
    // witout it and consequently not put in a loop at all.

    unsigned char i;
    for (i = 0; i < 64; i++)
        __asm("nop\n\t");

    PORTC = 0;
}

void isort(byte *a, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int j = a[i];
        int k;
        for (k = i - 1; (k >= 0) && (j > a[k]); k--)
        {
            a[k + 1] = a[k];
        }
        a[k + 1] = j;
    }
}

void triggerEnv()
{
    AY3(13, envShape1);
    ay3Reg1Last[13] = envShape1 + 1;

    AY32(13, envShape2);
    ay3Reg2Last[13] = envShape2 + 1;
}

void updatePitch()
{
    if (bitRead(ledMatrix[5], 0))
        if (held > 0)
            base[1] = seq + (key - 60);

    if (base[1] != 0)
    {
        temp = base[1] + (100 - tune[1]) + offsetNote[1];

        // in range
        if (temp > 127)
            temp = 127;
        else if (temp < 0)
            temp = 0;

        destiPitch[1] = tp[temp] + (lfo * bitRead(ledMatrix[2], 0)) + offsetFreq[1];
    }
    else
        pitch[1] = 0;

    if (bitRead(ledMatrix[5], 1))
        if (held > 0)
            base[2] = seq + (key - 60);

    if (base[2] != 0)
    {
        temp = base[2] + (100 - tune[2]) + offsetNote[2];

        // in range
        if (temp > 127)
            temp = 127;
        else if (temp < 0)
            temp = 0;

        destiPitch[2] = tp[temp] + (lfo * bitRead(ledMatrix[2], 1)) + offsetFreq[2];
    }
    else
        pitch[2] = 0;

    if (bitRead(ledMatrix[5], 2))
        if (held > 0)
            base[3] = seq + (key - 60);

    if (base[3] != 0)
    {
        temp = base[3] + (100 - tune[3]) + offsetNote[3];

        // in range
        if (temp > 127)
            temp = 127;
        else if (temp < 0)
            temp = 0;

        destiPitch[3] = tp[temp] + (lfo * bitRead(ledMatrix[2], 2)) + offsetFreq[3];
    }
    else
        pitch[3] = 0;

    if (bitRead(ledMatrix[5], 3))
        if (held > 0)
            base[4] = seq + (key - 60);

    if (base[4] != 0)
    {
        temp = base[4] + (100 - tune[4]) + offsetNote[4];

        // in range
        if (temp > 127)
            temp = 127;
        else if (temp < 0)
            temp = 0;

        destiPitch[4] = tp[temp] + (lfo * bitRead(ledMatrix[2], 3)) + offsetFreq[4];
    }
    else
        pitch[4] = 0;

    if (bitRead(ledMatrix[5], 4))
        if (held > 0)
            base[5] = seq + (key - 60);

    if (base[5] != 0)
    {
        temp = base[5] + (100 - tune[5]) + offsetNote[5];

        // in range
        if (temp > 127)
            temp = 127;
        else if (temp < 0)
            temp = 0;

        destiPitch[5] = tp[temp] + (lfo * bitRead(ledMatrix[2], 4)) + offsetFreq[5];
    }
    else
        pitch[5] = 0;

    if (bitRead(ledMatrix[5], 5))
        if (held > 0)
            base[6] = seq + (key - 60);

    if (base[6] != 0)
    {
        temp = base[6] + (100 - tune[6]) + offsetNote[6];

        // in range
        if (temp > 127)
            temp = 127;
        else if (temp < 0)
            temp = 0;

        destiPitch[6] = tp[temp] + (lfo * bitRead(ledMatrix[2], 5)) + offsetFreq[6];
    }
    else
        pitch[6] = 0;
}
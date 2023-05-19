#if 0

/*TODO:
pitch bend 2 semi each way
voice reset
poly mode keep all voices active and tuned together

program chance >preset
faster arp when sync
sysex for seq?
mute before patch change
*/

// --- PIN MODE: OUTPUT  --- 

DDRB |= _BV (0); // pinMode (0, OUTPUT);
DDRB |= _BV (1); // pinMode (1, OUTPUT);
DDRB |= _BV (2); // pinMode (2, OUTPUT);
DDRB |= _BV (3); // pinMode (3, OUTPUT);
DDRB |= _BV (4); // pinMode (4, OUTPUT);
DDRB |= _BV (5); // pinMode (5, OUTPUT);
DDRB |= _BV (6); // pinMode (6, OUTPUT);
DDRB |= _BV (7); // pinMode (7, OUTPUT);
DDRD |= _BV (0); // pinMode (8, OUTPUT);
DDRD |= _BV (1); // pinMode (9, OUTPUT);
DDRD |= _BV (2); // pinMode (10, OUTPUT);
DDRD |= _BV (3); // pinMode (11, OUTPUT);
DDRD |= _BV (4); // pinMode (12, OUTPUT);
DDRD |= _BV (5); // pinMode (13, OUTPUT);
DDRD |= _BV (6); // pinMode (14, OUTPUT);
DDRD |= _BV (7); // pinMode (15, OUTPUT);
DDRC |= _BV (0); // pinMode (16, OUTPUT);
DDRC |= _BV (1); // pinMode (17, OUTPUT);
DDRC |= _BV (2); // pinMode (18, OUTPUT);
DDRC |= _BV (3); // pinMode (18, OUTPUT);
DDRC |= _BV (4); // pinMode (20, OUTPUT);
DDRC |= _BV (5); // pinMode (21, OUTPUT);
DDRC |= _BV (6); // pinMode (22, OUTPUT);
DDRC |= _BV (7); // pinMode (23, OUTPUT);
DDRA |= _BV (0); // pinMode (A0, OUTPUT);
DDRA |= _BV (1); // pinMode (A1, OUTPUT);
DDRA |= _BV (2); // pinMode (A2, OUTPUT);
DDRA |= _BV (3); // pinMode (A3, OUTPUT);
DDRA |= _BV (4); // pinMode (A4, OUTPUT);
DDRA |= _BV (5); // pinMode (A5, OUTPUT);
DDRA |= _BV (6); // pinMode (A6, OUTPUT);
DDRA |= _BV (7); // pinMode (A7, OUTPUT);

// --- PIN MODE: INPUT  --- 

DDRB &= ~_BV (0); // pinMode (0, INPUT);
DDRB &= ~_BV (1); // pinMode (1, INPUT);
DDRB &= ~_BV (2); // pinMode (2, INPUT);
DDRB &= ~_BV (3); // pinMode (3, INPUT);
DDRB &= ~_BV (4); // pinMode (4, INPUT);
DDRB &= ~_BV (5); // pinMode (5, INPUT);
DDRB &= ~_BV (6); // pinMode (6, INPUT);
DDRB &= ~_BV (7); // pinMode (7, INPUT);
DDRD &= ~_BV (0); // pinMode (8, INPUT);
DDRD &= ~_BV (1); // pinMode (9, INPUT);
DDRD &= ~_BV (2); // pinMode (10, INPUT);
DDRD &= ~_BV (3); // pinMode (11, INPUT);
DDRD &= ~_BV (4); // pinMode (12, INPUT);
DDRD &= ~_BV (5); // pinMode (13, INPUT);
DDRD &= ~_BV (6); // pinMode (14, INPUT);
DDRD &= ~_BV (7); // pinMode (15, INPUT);
DDRC &= ~_BV (0); // pinMode (16, INPUT);
DDRC &= ~_BV (1); // pinMode (17, INPUT);
DDRC &= ~_BV (2); // pinMode (18, INPUT);
DDRC &= ~_BV (3); // pinMode (18, INPUT);
DDRC &= ~_BV (4); // pinMode (20, INPUT);
DDRC &= ~_BV (5); // pinMode (21, INPUT);
DDRC &= ~_BV (6); // pinMode (22, INPUT);
DDRC &= ~_BV (7); // pinMode (23, INPUT);
DDRA &= ~_BV (0); // pinMode (A0, INPUT);
DDRA &= ~_BV (1); // pinMode (A1, INPUT);
DDRA &= ~_BV (2); // pinMode (A2, INPUT);
DDRA &= ~_BV (3); // pinMode (A3, INPUT);
DDRA &= ~_BV (4); // pinMode (A4, INPUT);
DDRA &= ~_BV (5); // pinMode (A5, INPUT);
DDRA &= ~_BV (6); // pinMode (A6, INPUT);
DDRA &= ~_BV (7); // pinMode (A7, INPUT);

// --- DIGITAL WRITE: HIGH  --- 

PORTB |= _BV (0); // digitalWrite (0, HIGH);
PORTB |= _BV (1); // digitalWrite (1, HIGH);
PORTB |= _BV (2); // digitalWrite (2, HIGH);
PORTB |= _BV (3); // digitalWrite (3, HIGH);
PORTB |= _BV (4); // digitalWrite (4, HIGH);
PORTB |= _BV (5); // digitalWrite (5, HIGH);
PORTB |= _BV (6); // digitalWrite (6, HIGH);
PORTB |= _BV (7); // digitalWrite (7, HIGH);
PORTD |= _BV (0); // digitalWrite (8, HIGH);
PORTD |= _BV (1); // digitalWrite (9, HIGH);
PORTD |= _BV (2); // digitalWrite (10, HIGH);
PORTD |= _BV (3); // digitalWrite (11, HIGH);
PORTD |= _BV (4); // digitalWrite (12, HIGH);
PORTD |= _BV (5); // digitalWrite (13, HIGH);
PORTD |= _BV (6); // digitalWrite (14, HIGH);
PORTD |= _BV (7); // digitalWrite (15, HIGH);
PORTC |= _BV (0); // digitalWrite (16, HIGH);
PORTC |= _BV (1); // digitalWrite (17, HIGH);
PORTC |= _BV (2); // digitalWrite (18, HIGH);
PORTC |= _BV (3); // digitalWrite (18, HIGH);
PORTC |= _BV (4); // digitalWrite (20, HIGH);
PORTC |= _BV (5); // digitalWrite (21, HIGH);
PORTC |= _BV (6); // digitalWrite (22, HIGH);
PORTC |= _BV (7); // digitalWrite (23, HIGH);
PORTA |= _BV (0); // digitalWrite (A0, HIGH);
PORTA |= _BV (1); // digitalWrite (A1, HIGH);
PORTA |= _BV (2); // digitalWrite (A2, HIGH);
PORTA |= _BV (3); // digitalWrite (A3, HIGH);
PORTA |= _BV (4); // digitalWrite (A4, HIGH);
PORTA |= _BV (5); // digitalWrite (A5, HIGH);
PORTA |= _BV (6); // digitalWrite (A6, HIGH);
PORTA |= _BV (7); // digitalWrite (A7, HIGH);

// --- DIGITAL WRITE: LOW  --- 

PORTB &= ~_BV (0); // digitalWrite (0, LOW);
PORTB &= ~_BV (1); // digitalWrite (1, LOW);
PORTB &= ~_BV (2); // digitalWrite (2, LOW);
PORTB &= ~_BV (3); // digitalWrite (3, LOW);
PORTB &= ~_BV (4); // digitalWrite (4, LOW);
PORTB &= ~_BV (5); // digitalWrite (5, LOW);
PORTB &= ~_BV (6); // digitalWrite (6, LOW);
PORTB &= ~_BV (7); // digitalWrite (7, LOW);
PORTD &= ~_BV (0); // digitalWrite (8, LOW);
PORTD &= ~_BV (1); // digitalWrite (9, LOW);
PORTD &= ~_BV (2); // digitalWrite (10, LOW);
PORTD &= ~_BV (3); // digitalWrite (11, LOW);
PORTD &= ~_BV (4); // digitalWrite (12, LOW);
PORTD &= ~_BV (5); // digitalWrite (13, LOW);
PORTD &= ~_BV (6); // digitalWrite (14, LOW);
PORTD &= ~_BV (7); // digitalWrite (15, LOW);
PORTC &= ~_BV (0); // digitalWrite (16, LOW);
PORTC &= ~_BV (1); // digitalWrite (17, LOW);
PORTC &= ~_BV (2); // digitalWrite (18, LOW);
PORTC &= ~_BV (3); // digitalWrite (18, LOW);
PORTC &= ~_BV (4); // digitalWrite (20, LOW);
PORTC &= ~_BV (5); /0/ digitalWrite (21, LOW);
PORTC &= ~_BV (6); // digitalWrite (22, LOW);
PORTC &= ~_BV (7); // digitalWrite (23, LOW);
PORTA &= ~_BV (0); // digitalWrite (A0, LOW);
PORTA &= ~_BV (1); // digitalWrite (A1, LOW);
PORTA &= ~_BV (2); // digitalWrite (A2, LOW);
PORTA &= ~_BV (3); // digitalWrite (A3, LOW);
PORTA &= ~_BV (4); // digitalWrite (A4, LOW);
PORTA &= ~_BV (5); // digitalWrite (A5, LOW);
PORTA &= ~_BV (6); // digitalWrite (A6, LOW);
PORTA &= ~_BV (7); // digitalWrite (A7, LOW);

// --- DIGITAL READ  --- 

x = (PINB & _BV (0)) == 0; // digitalRead (0);
x = (PINB & _BV (1)) == 0; // digitalRead (1);
x = (PINB & _BV (2)) == 0; // digitalRead (2);
x = (PINB & _BV (3)) == 0; // digitalRead (3);
x = (PINB & _BV (4)) == 0; // digitalRead (4);
x = (PINB & _BV (5)) == 0; // digitalRead (5);
x = (PINB & _BV (6)) == 0; // digitalRead (6);
x = (PINB & _BV (7)) == 0; // digitalRead (7);
x = (PIND & _BV (0)) == 0; // digitalRead (8);
x = (PIND & _BV (1)) == 0; // digitalRead (9);
x = (PIND & _BV (2)) == 0; // digitalRead (10);
x = (PIND & _BV (3)) == 0; // digitalRead (11);
x = (PIND & _BV (4)) == 0; // digitalRead (12);
x = (PIND & _BV (5)) == 0; // digitalRead (13);
x = (PIND & _BV (6)) == 0; // digitalRead (14);
x = (PIND & _BV (7)) == 0; // digitalRead (15);
x = (PINC & _BV (0)) == 0; // digitalRead (16);
x = (PINC & _BV (1)) == 0; // digitalRead (17);
x = (PINC & _BV (2)) == 0; // digitalRead (18);
x = (PINC & _BV (3)) == 0; // digitalRead (19);
x = (PINC & _BV (4)) == 0; // digitalRead (20);
x = (PINC & _BV (5)) == 0; // digitalRead (21);
x = (PINC & _BV (6)) == 0; // digitalRead (22);
x = (PINC & _BV (7)) == 0; // digitalRead (23);
x = (PINA & _BV (0)) == 0; // digitalRead (A0);
x = (PINA & _BV (1)) == 0; // digitalRead (A1);
x = (PINA & _BV (2)) == 0; // digitalRead (A2);
x = (PINA & _BV (3)) == 0; // digitalRead (A3);
x = (PINA & _BV (4)) == 0; // digitalRead (A4);
x = (PINA & _BV (5)) == 0; // digitalRead (A5);
x = (PINA & _BV (6)) == 0; // digitalRead (A6);
x = (PINA & _BV (7)) == 0; // digitalRead (A7);
  
#endif

//define pins
int Button =2;
int LDRSensor=A0;
int POTSensor=A1;



#define DATAOUT     11   //mosi
#define DATAIN  12   //miso
#define SPICLOCK    13   //sck
#define SLAVESELECT 10   //ss

//opcodes
#define PU      0x01
#define STOP    0x02
#define RESET  0x03
#define CLR_INT     0x04
#define RD_STATUS   0x05
#define RD_PLAY_PTR 0x06
#define PD      0x07
#define RD_REC_PTR  0x08
#define DEVID  0x09
#define PLAY    0x40
#define REC    0x41
#define REC_LED    0x51//record with LED on
#define ERASE  0x42
#define G_ERASE     0x43
#define RD_APC  0x44
#define WR_APC1     0x45
#define WR_APC2     0x65
#define WR_NVCFG    0x46
#define LD_NVCFG    0x47
#define FWD    0x48
#define CHK_MEM     0x49
#define EXTCLK  0x4A
#define SET_PLAY    0x80
#define SET_REC     0x81
#define SET_REC_LED    0x91//set record with LED on
#define SET_ERASE   0x82

#define WAIT_TIME 10//waiting time (ms) after SS=LOW at least 500ns
#define WAIT_TIME2 100

int start_adress = 0x00;//test address to record
int end_adress = 0x050;//20unit

void setup() 
{  
  Serial.begin(9600);
   
  pinMode(Button,INPUT);

  pinMode(DATAOUT, OUTPUT);
  pinMode(SPICLOCK, OUTPUT);
  pinMode(SLAVESELECT, OUTPUT);
  pinMode(DATAIN, INPUT);

  initialize();
}

void initialize()
{
  byte clr;
   
 digitalWrite(SLAVESELECT, HIGH); //disable device
 digitalWrite(SPICLOCK, HIGH); //SCLK
 digitalWrite(DATAOUT, LOW); //MOSI
 
 SPCR = B01111111; //data lsb, clock high when idle, samples on falling
 clr = SPSR;
 clr = SPDR;
 delay(10);

 //start serial
 Serial.println("Sketch is starting up");

 pu();
 clear_int();
}

void loop() 
{
   char c=0;
   boolean f;
   boolean rec_fg = false;
   boolean play_fg = false;
   
   int Val1 = analogRead(LDRSensor);
   int Val2 = analogRead(POTSensor);
   int Val3 = digitalRead(Button);
   
   Serial.print("LDR: ");    
   Serial.print(Val1);
   Serial.print(" Pot: ");
   Serial.print(Val2);
   Serial.print(" Button Status: ");
   Serial.print(Val3);
   
   if (Val1 > 800 )//1
   {
    c='3';
   }
   else if (Val2 > 600 )//2
   {
    c='2';
   }

   else if ( Val3==1)//3
   {
    c='1';
   }
   else //4
   {
    Serial.println(" Do nothing!!");   
   }
  
   delay(100);

     switch(c)
     {
        case '1':
          set_play(0x00, 0x025);//Be careful
          play_fg = true;
          break;
        case '2':
          set_play(0x040, 0x060);//You are Out of your Path
          play_fg = true;
          break;
        case '3':
          set_play(0x025, 0x040);//Wet Surface
          play_fg = true;
          break;

     }
  delay(800);
}

void pu()//power up
{
 digitalWrite(SLAVESELECT, LOW);
 delay(WAIT_TIME);
 spi_transfer(PU); // power up
 spi_transfer(0x00); // data byte
 digitalWrite(SLAVESELECT, HIGH);
 delay(WAIT_TIME2);
 
 Serial.println("power up end");
}

void clear_int()// clear interupt
{
  digitalWrite(SLAVESELECT, LOW);
  delay(WAIT_TIME);
  spi_transfer(CLR_INT); // clear interupt and eom bit
  spi_transfer(0x00); // data byte
  digitalWrite(SLAVESELECT, HIGH);
  delay(WAIT_TIME2);
  Serial.println("clear int end");
}

void set_play(int starta, int enda)
{
 digitalWrite(SLAVESELECT, LOW);
 delay(WAIT_TIME);
 spi_transfer(SET_PLAY); // clear interupt and eom bit
 spi_transfer(0); // data byte

 spi_transfer(starta & 255); // data byte start
 spi_transfer(starta >> 8); // data byte last 3 bits
 spi_transfer(enda & 255); // data byte stop
 spi_transfer(enda >> 8); // data byte last 3 bits
 spi_transfer(0); // data byte blank
 digitalWrite(SLAVESELECT, HIGH);  
 delay(WAIT_TIME2);
 
 Serial.println("set play end");
}


char spi_transfer(volatile char data)
{
  SPDR = data;           // Start the transmission
  while (!(SPSR & (1 << SPIF)))     // Wait for the end of the transmission
  {
  };
  return SPDR;           // return the received byte
} 


uint16_t read_apc()
{
  uint16_t apc;
  uint8_t data[4] = {0xFF,0xFF,0xFF,0xFF};
  
  digitalWrite(SLAVESELECT, LOW);
  delay(WAIT_TIME);
  data[0] = spi_transfer(RD_APC); // read apc register
  data[1] = spi_transfer(0);
  data[2] = spi_transfer(0);
  data[3] = spi_transfer(0);
  digitalWrite(SLAVESELECT, HIGH);
  
  delay(WAIT_TIME2);
  
  apc = word(data[3], data[2]);
  
  Serial.println("read apc end");
  
  return apc;
}
  
uint16_t read_status(void)
{
  uint16_t sr1;
  uint8_t data[3] = {0xFF,0xFF,0xFF};
  
  digitalWrite(SLAVESELECT, LOW);
  delay(WAIT_TIME);
  data[0] = spi_transfer(RD_STATUS); // read status register
  data[1] = spi_transfer(0);
  data[2] = spi_transfer(0);
  digitalWrite(SLAVESELECT, HIGH);
  
  delay(WAIT_TIME2);
  
  sr1 = word(data[2], 0xFF);
  return sr1;
}

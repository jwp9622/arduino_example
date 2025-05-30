//

//음극배열
int num_array[10][7]={
  //A B C D E F G DP
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,0,0,1,1}  //9
};

int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;

void Num_Write(int number, int dig){
	int pin = 2;
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(dig, LOW);
  
  for(int j=0;j<7;j++){
    digitalWrite(pin, num_array[number][j]);
    pin++;
  }     
  delay(2);
}

void setup()
{

  pinMode(2, OUTPUT); //a
  pinMode(3, OUTPUT);  //b
  pinMode(4, OUTPUT); //c
  pinMode(5, OUTPUT); //d
  pinMode(6, OUTPUT); //e
  pinMode(7, OUTPUT); //f
  pinMode(8, OUTPUT); //g
  pinMode(9, OUTPUT); //d1
  pinMode(10, OUTPUT); //d2
  pinMode(11, OUTPUT); //d3
  pinMode(12, OUTPUT); //d4
  
  for(int j=2;j<=8;j++){
    digitalWrite(j, LOW);
  }
  
  for(int j=9;j<=12;j++){
    digitalWrite(j, HIGH);
  }
  
}

void loop(){

  static int i=0, counter=0;
  Num_Write(2, D1);
  Num_Write(0, D2);
  Num_Write(2, D3);
  Num_Write(5, D4);  
}



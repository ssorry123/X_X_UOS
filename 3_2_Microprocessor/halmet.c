  
#include <avr/io.h> //AVR 입출력 헤더파일을 포함합니다.
#include <util/delay.h> //delay 지연용 헤더파일을 포함합니다.
#include <avr/interrupt.h> //인터럽트 관련 헤더파일을 포함합니다.
 
#define F_CPU 16000000UL //사용중인 크리스털 값을 상수로 설정줍니다. (16MHz)
 
volatile int count; //4바이트의 전역 변수 count를 선언합니다. 
volatile int count1;
volatile int count2;


ISR(TIMER1_OVF_vect) //TCNT1 값이 넘치면 (오버플로우가 발생하면) 이 서브 루틴으로 점프합니다.
{
	TCNT1=-2000;
	// 1ms에 하나씩 올려준다.
    count++;
	count1++;
	count2++;     
}
void timer2(){
	TCCR1B=((0<<CS12) | (1<<CS11) | (0<<CS10));
	TCNT1=-2000;
	TIMSK=((1<<TOIE1));
}


int led=0;
int LED[8]={0b11100000,01110000,00111000,00011100,00001110,00000111,10000011,11000001};
void onLED(){DDRA=0xff;
	led=(led+1)%8; 
	//PORTA=LED[led];
	PORTA=0b11111111;
}
void offLED(){DDRA=0xff;
	led=(led+1)%8; 
	//PORTA=LED[led];
	PORTA=0;
}


void show_FND(int n){
unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67};
unsigned char fnd_sel[4] = {0x08, 0x04, 0x02, 0x01};
	unsigned char fnd[4];
	int i = 0;
	DDRC=0xff;
	DDRG=0x0f;
	if(n<=0)
		n=0;
	if(n>=10000){
		n=9999;
	}

	fnd[0] = (n/1000)%10;
	fnd[1] = (n/100)%10;
	fnd[2] = (n/10)%10;
	fnd[3] = n%10;
		
	// 조금만 표시한다.
	int a;
	for(a=0;a<100;a++)
		for(i=2;i<4;i++){
			PORTC = digit[fnd[i]];
			PORTG = fnd_sel[i];
			_delay_ms(1);
		}	
	
	PORTG=0;	//FND끊다.
}


// 왼쪽
void trig(){
	DDRE=0b00000001;
	PORTE = 0x01;
	count=0;
	while(count<=10);
	PORTE = 0x00;
}

// 오른쪽
void trig1(){
	DDRD=0b00000001;
	PORTD = 0x01;
	count1=0;
	while(count1<=10);
	PORTD = 0x00;
}

// 뒤
void trig2(){
	DDRG=0b00000001;
	PORTG = 0x01;
	count2=0;
	while(count2<=10);
	PORTG = 0x00;
}

//왼
int echo(){
	int b;

	while(!(PINE & 0x02));
	count=0;	//High
	while(PINE & 0x02);//Low
	b=count;	//High->Low까지 시간

	if(b<0)
		b=-b;

	return b;
}

// 오
int echo1(){
	int b;

	while(!(PIND & 0x02));
	count1=0;	//High
	while(PIND & 0x02);	//Low
	b=count1;	//High->Low 시간


	if(b<0)
		b=-b;
	return b;
}

// 뒤
int echo2(){
	int b;

	while(!(PING & 0x02));
	count2=0;

	while(PING & 0x02);
	b=count2;


	if(b<0)
		b=-b;
	return b;
}



// 현재 항상 켜져있기
void dotMatrix(){
	unsigned char i;

	char COLS[]={
		0b10000000,
		0b11000000,
		0b11100000,
		0b11110000,
		0b11111000,
		0b11111100,
		0b11111110,
		0b11111111
	};

	DDRA=0xff;
	DDRC=0xff;
	
	
	for(i=0;i<10;i++){
		PORTC=0b00111111;
		PORTA=COLS[7];
		_delay_ms(10);
	}	
	return;
}

// 꺼지기
void dotMatrix1(){
	unsigned char i;

	char COLS[]={
		0b10000000,
		0b11000000,
		0b11100000,
		0b11110000,
		0b11111000,
		0b11111100,
		0b11111110,
		0b11111111
	};

	DDRA=0xff;
	DDRC=0xff;
	
	for(i=0;i<10;i++){
		PORTC=0b11111111;	// 이부분이 다름
		PORTA=COLS[7];
		_delay_ms(10);
	}	
	return;
}

//8*8 깜박깜박
void flash(){
	int i = 0;
	for(i=0;i<5;i++){
	dotMatrix();
	dotMatrix1();
	}
}

// 기본부저
void buzzer(int time){
	int i = 0;
	for(i=0;i<time;i++){
	PORTB=0x10;
	_delay_ms(10);
	PORTB=0x00;
	_delay_ms(10);
	}
}

// 두개의 부저 컨트롤
// 수정해보자.
void sound2(int time){
	DDRB=0xff;
	int i = 0;
	for(i=0;i<time;i++){
		PORTB=0b00000010;
		_delay_ms(10);
		PORTB=0x00;
		_delay_ms(10);
	}
}

void sound1(int time){
	DDRB=0xff;
	int i = 0;
	for(i=0;i<time;i++){
		PORTB=0b00001000;
		_delay_ms(10);
		PORTB=0x00;
		_delay_ms(10);
	}
}

void sound(int time){
	DDRB=0xff;
	int i = 0;
	for(i=0;i<time;i++){
		PORTB=0xff;
		_delay_ms(10);
		PORTB=0x00;
		_delay_ms(10);
	}
}

int main()
{

	int distance;

	timer2();
	sei();
	
	//while(1){sound2(200);}

	int n;

	while(1){
	
		dotMatrix();	// 항상 켜져있기
		//onLED();

		// 1번째 초음파 작동
		count=0;
		trig();
		n=distance=echo();
	
		if(n<=0) n=0;
		//show_FND(distance);	
	
		if(n==2){
			//buzzer(200);
			flash();
			sound2(200);
		}
		else if(n==1 || n==0){
			//buzzer(50);
			flash();
			sound2(50);
		}
	
		// 두번째 초음파 작동
		count1=0;
		trig1();
		n=distance=echo1();
	
		if(n<=0) n=0;
		//show_FND(distance);
	
		if(n==2){
			//buzzer(200);
			flash();
			sound1(200);
		}
		else if(n==1 || n==0){
			//buzzer(50);
			flash();
			sound1(50);
		}
	
		// 세번째 초음파 작동
		count2=0;
		trig2();
		n=distance=echo2();
	
		if(n<=0) n=0;
		//show_FND(distance);
			
		if(n==2){
			//buzzer(200);
			flash();
			sound(200);
		}
		else if(n==1 || n==0){
			//buzzer(50);
			flash();
			sound(50);
		}

	_delay_ms(1000);
	}

}
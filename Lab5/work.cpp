#include<stdio.h>
#include<Windows.h>
#include<conio.h>
void draw_ship(int,int);
void gotoxy(int,int);
void erase_ship(int,int);
void setcursor(bool);
void setcolor(int, int);
void draw_shot(int, int);
void erase_shot(int, int);
//ยาว 80 สูง 20
int main() {
	int x = 38, y = 20, position_x[5],position_y[5],shot[5],num=0;
	char ch = ' ';
	setcursor(0);

	draw_ship(x, y); 
	for (int i = 0; i < 5; i++) {
		shot[i] = 0;		//กำหนดค่าของกระสุนไว้ ไม่ให้เป็นค่าขยะเฉยๆ	
	}


	do {
		if (_kbhit()) {
			ch = _getch();
				if (ch == 'a' ) {    
					num = 1;		
			}
   //เป็นการรับค่าเข้าาเฉยๆเพื่อจะได้รู้ว่าไปซ้ายไปขวาคือตัวเลขอะไรแล้วไปเช็ตเงื่อนไขการเคลื่อนที่ข้างล่าง

				if (ch == 'd' ) {
					num = 2;
			}

		
				if (ch == 's') {   // วิ่งซ้ายขวาเรื่อยๆ จนกว่าจะชนหรือกด s
					num = 3; 
			} 
		
						
			if (ch == ' ') {   // กด spacbar เพิ้อ ยิงกระสุน

				for (int i = 0;i<5;i++) { //แค่ทำให้ครบรอบเฉยๆ แต่จริงๆไม่ต้องวนลูปก็ได้
					if(shot[i]==0){			 
				
						shot[i] = 1;		//เซ้ทค่าเพื่อเอาไปใช้ให้มันขยับ ใน for ข้างล่าง 
						position_x[i] = x;  // ใช้ค่าตน.ของยานมาให้เท่ากับ ตัวแปร position 
						position_y[i] = y - 2;
						draw_shot(position_x[i], position_y[i] ); // ใช้ค่า x เป็นค่าของยาน เลยเป็นยานออกมา
						break;
						
					} 
				}
			}

			fflush(stdin);
		}  // จบif ใหญ่

		//เงื่อนไขในการเช็คว่าไปซ้ายไปขวา
		if (num == 1 && x > 0)    //ไปทางซ้าย
		{
			erase_ship(x, y); draw_ship(--x, y);
		}
		if (num == 2 && x < 73)	 //ไปทางขวา
		{
			erase_ship(x, y); draw_ship(++x, y);
		}  // ถ้าให้มันหยุดคือกด s ถ้ากด s ค่ามันคือ 3 มันจะไม่เข้าเงื่อไขไหนเลยมันก็จะหยุด
		

		for (int i = 0; i < 5; i++) {
			if (shot[i] == 1)    //ค่าที่รับจากลูปด้านบน เปิดค่าให้มันยิงมา
			{

				erase_shot(position_x[i], position_y[i]);
				position_y[i] = position_y[i] - 1;
				if (position_y[i] > 0) {     //เป็นการฟิคขอบเขตของความสูงของจอภาพ
					draw_shot(position_x[i], position_y[i]);
				}				
				else
				{
					shot[i] = 0;
				}
			}
		}

		Sleep(100);		

	} while (ch != 'x');  setcolor(7, 0);


	return 0;
}



void gotoxy(int x, int y) {    // ตน. ของยาน
	COORD c = { x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x,int y) {
	setcursor(0);
	gotoxy(x, y);
	setcolor(2, 4);  // เปลี่ยนสีก่อนเริ่มเดิน
	printf("<-0->"); 
	
}

void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf("      ");
}

void setcursor(bool visible) {
	
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void erase_shot(int x, int y) {		//ลบรูปกระสุน
	gotoxy(x, y);
	setcolor(0, 0);
	printf("      ");

}

void draw_shot(int x, int y) {		//วาดรูปกระสุน
	gotoxy(x,y);
	setcolor(7, 0);
	printf("  A ");
}





/*


#include<stdio.h>
#include<Windows.h>
#include<conio.h>
void draw_ship(int,int);
void gotoxy(int,int);
void erase_ship(int,int);
void setcursor(bool);
void setcolor(int, int);
void erase_space(int, int);

int main() {

	char ch = ' ';
	int x = 38, y = 20;
	draw_ship(x, y);
	setcursor(0);
	setcolor(0, 0);  //(สีตัวอักษร,สีพื้นหลัง)
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x > 0) {
				draw_ship(--x, y); //ให้ขยับไปทางซ้าย
				erase_space(0, 0);
			}
			if (ch == 'd' && x < 73) {
				erase_ship(x, y);	//ให้ขยับไปทางขวา
				draw_ship(++x, y);
				erase_space(0, 0);
			}
			if (ch == 'w'&& y>0) {
				erase_ship(x, y);	//ให้ขยับขึ้นบน
				draw_ship(x, --y);
				erase_space(0, 0);
			}
			if (ch == 's'&& y<24) {
				erase_ship(x, y);	//ให้ขยับลงล่าง
				draw_ship(x, ++y);
				erase_space(0, 0);
			}

			fflush(stdin);
		}
		Sleep(100);

	} while (ch != 'x');  setcolor(7, 0);


	return 0;
}



void gotoxy(int x, int y) {
	COORD c = { x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x,int y) {
	gotoxy(x, y);
	setcolor(2, 4);  // เปลี่ยนสีก่อนเริ่มเดิน
	printf("<-0-> ");

}

void erase_ship(int x, int y) {
	gotoxy(x, y);
	printf("      ");
}

void erase_space(int x, int y) {
	setcolor(x, y);   // ทำให้ข้ความ return0 หาย
	printf("      ");
}


void setcursor(bool visible) {

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}



*/